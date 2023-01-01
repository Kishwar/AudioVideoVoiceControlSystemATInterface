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
  assert(xTaskCreate(
              uartThread,              /* Function that implements the task. */
              "SerialThread",          /* Text name for the task. */
              4096,                    /* Stack size in words, not bytes. */
              NULL,                    /* Parameter passed into the task. */
              tskIDLE_PRIORITY,        /* Priority at which the task is created. */
              NULL) == pdPASS && "initUartThread failed.");
}

void Uart::uartThread(void *pvParam) {
 while(true)
  {
    delay(1000);
  }
}