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

#include <stdexcept>
#include <string>

static QueueHandle_t *qHandle = nullptr;
static Uart *instance = nullptr;

Uart& Uart::getInstance(void) {
  if(instance == nullptr) {
    instance = new Uart();
  }

  return *instance;
}

void Uart::run(void) {
  initUartThread();
}

void Uart::setBaud(uint32_t baud) {
  m_Baud = baud;
  Serial.flush();
  Serial.end();
  Serial.begin(m_Baud);
}

void Uart::initUartThread(void) noexcept {
  try {
    
    CreateTask(uartThread, "SerialThread");     // Create UART task
    CreateQueue(getQueueHandle(), 1, 1);        // Create UART queue
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

void Uart::uartThread(void *pvParam) noexcept {
 while(true)
  {
    delay(10);
    Serial.println("Waiting for AT command..");
  }
}
