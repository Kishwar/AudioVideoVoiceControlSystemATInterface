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

public:
  static Uart& getInstance(void);
  static QueueHandle_t& getQueueHandle(void);
  void setBaud(uint32_t baud);
  void run(void);

  Uart(const Uart&) = delete;     // copy constructor deleted
  Uart(const Uart&&) = delete;    // move constructor deleted

private:
	static void initUartThread(void) noexcept;
	static void uartThread(void *pvParam) noexcept;
  Uart(uint32_t baud = 115200) : m_Baud{baud} {
    Serial.begin(m_Baud);
  }
  ~Uart() {
    Serial.flush();
    Serial.end();
  }
};
