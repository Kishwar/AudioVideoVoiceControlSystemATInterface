/**
 * @file uart.h
 *
 * @brief class responsible for uart port operations
 *
 * @ingroup serial_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include <stdint.h>
#include <Arduino.h>

class Uart {
  uint32_t m_Baud;
  Uart* m_Instance = nullptr;

public:
  Uart* getInstance(void);
  void setBaud(uint32_t baud);

private:
	void initUartThread(void);
	void uartThread(void *pvParam);
  Uart(uint32_t baud = 115200) : m_Baud{baud} {
    Serial.begin(m_Baud);
  }
  ~Uart() {
		Serial.flush();
		Serial.end();
    delete m_Instance; 
	}
};