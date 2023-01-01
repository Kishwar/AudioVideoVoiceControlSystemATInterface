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

#include "freertos/FreeRTOS.h"

Uart* Uart::getInstance(void) {

  if(m_Instance == nullptr) {
    m_Instance = new Uart();
    initUartThread();
  }

  return m_Instance;
}

void Uart::setBaud(uint32_t baud) {
  m_Baud = baud;
}

void Uart::initUartThread(void) {

}

void Uart::uartThread(void *pvParam) {
  
}