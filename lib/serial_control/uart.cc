/**
 * @file Uart.cc
 *
 * @brief class responsible for Uart port operations
 *
 * @ingroup Uart_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include "core.h"
#include "uart.h"
#include "at_msg.h"

#include <stdexcept>
#include <string>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <esp_task_wdt.h>

static QueueHandle_t *qHandle = nullptr;
static Uart *instance = nullptr;
std::condition_variable condVariable;
std::mutex mutexUart;
bool active = false;

Uart& Uart::getInstance(void) {
  if(instance == nullptr) {
    instance = new Uart();
  }

  return *instance;
}

void Uart::run(void) {
  initUartThread();

  Serial.println("^SYSSTART\n");
}

void Uart::setBaud(uint32_t baud) {
  m_Baud = baud;
  Serial.flush();
  Serial.end();
  Serial.begin(m_Baud);
  Serial.setTimeout(20000);
}

void Uart::initUartThread(void) noexcept {
  try {
    CreateTask(uartThreadSend, "uartThreadSend", NULL);                 // Create UART task
    CreateTask(uartThreadRecv, "uartThreadRecv", NULL);                 // Create UART task
    CreateQueue(getQueueHandle(), 1, sizeof(atCommandReq));             // Create UART queue
  }
  catch(std::runtime_error& e) {
    std::string err = std::string("Terminating system, UART exception: ") + std::string(e.what());
    Serial.println(err.c_str());
    std::terminate();
  }
  catch(std::exception& e) {
    std::string err = std::string("Unknown exception caught. \
                            Serial port not available, UART exception: ") + std::string(e.what());
    Serial.println(err.c_str());
    Serial.flush();
    Serial.end();
  }
}

QueueHandle_t& Uart::getQueueHandle(void) {
  if(qHandle == nullptr) {
    qHandle = new QueueHandle_t();
  }
  return *qHandle;
}

void Uart::uartThreadRecv(void *pvParam) noexcept {
  // receive data from serial and send it to the queue
  // block receiving more data once valid AT command received
  while(true)
  {
    esp_task_wdt_init(20, false);
    if (Serial.available() > 0) {
      std::unique_lock lock(mutexUart);
      String atCommand = Serial.readStringUntil('\r');

      if(atCommand.length() < 2) {
        Serial.flush();
        continue;
      }

      String prefix = atCommand.substring(0, 2);
      prefix.toUpperCase();

      if(prefix != "AT") {
        Serial.println("\nError");
        Serial.flush();
        continue;
      }

      //1. Flush serial data
      Serial.flush();

      if(atCommand.length() == 2) {
        // no need to send to any queue, just return OK and wait for another AT command
        Serial.println("\nOK");
        Serial.flush();
        continue;
      }

      //2. We need to clip AT prefix and convert remaining text to lower case.
      auto atCommandPtr = new std::string(atCommand.c_str() + 2);

      //3. Create a message and tranport it to the AT parser queue
      atCommandReq *req = new atCommandReq(std::move(atCommandPtr));
      atCommandPtr = nullptr;

      if(qHandle != nullptr && *qHandle != 0 && req != nullptr) {
        xQueueSend(*qHandle, (void *)&req, (TickType_t)10);
      } else {
        delete req;
      }

      //4. TODO: start 20 second timer to clear queue if there is no handler
      
      active = true;
    }
    condVariable.notify_one();
    sleep(1);
  }
}

void Uart::uartThreadSend(void *pvParam) noexcept {
  // unblock serial port and get ready for serial data send / receive
  // send data output on the terminal
  while(true) 
  {
    std::unique_lock lock(mutexUart);
    condVariable.wait(lock, [] {
                                  return active;
                                });

    if(qHandle != nullptr && *qHandle != 0) {
      atCommandReq *rsp;
      xQueueReceive(*qHandle, &rsp, portMAX_DELAY);

      Serial.println(rsp->getPayLoad()->c_str());
      delete rsp;
    }
    
    Serial.println("\nOK");
    active = false;
  }  
}
