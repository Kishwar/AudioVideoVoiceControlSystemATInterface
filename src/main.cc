/**
 * @file Main.cc
 *
 * @brief Main file to start the project
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include <Arduino.h>
#include <soc/rtc_wdt.h>

#include "uart.h"
#include "fs.h"

void setup() {

  rtc_wdt_protect_off();
  rtc_wdt_disable();

  // trigger run UART
  Uart::getInstance().run();

  // trigger run filesystem
  FileSystem::getInstance().run();

}

void loop() {
  // put your main code here, to run repeatedly:
}