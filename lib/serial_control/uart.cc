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

Uart* Uart::getInstance(void) {

  static Uart *instance = nullptr;

  if(instance == nullptr) {
    instance = new Uart();
    initUartThread();
  }

  return instance;
}

void Uart::setBaud(uint32_t baud) {
  m_Baud = baud;
  Serial.flush();
  Serial.end();
  Serial.begin(m_Baud);
}

void Uart::initUartThread(void) {
  try {
    CreateTask(uartThread, "SerialThread");
  }
  catch(std::runtime_error& e) {
    std::string err = std::string("Terminating system, UART exception: ") + std::string(e.what());
    Serial.println(err.c_str());
    std::terminate();
  }
  catch(...) {
    Serial.println("Unknown exception caught. Serial port not available");
    Serial.flush();
    Serial.end();
  }
}

void Uart::uartThread(void *pvParam) {
 while(true)
  {
    delay(1000);
  }
}