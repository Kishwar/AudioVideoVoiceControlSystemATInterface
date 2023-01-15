/**
 * @file core.cc
 *
 * @brief responsible for creating core service using RTOS
 *
 * @ingroup core_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include "core.h"

#include <freertos/task.h>
#include <stdexcept>

void CreateTask(const TaskFunction_t &func, std::string&& name, void *param, uint32_t stack) {
  if(xTaskCreate(
              func,                       /* Function that implements the task.     */
              name.c_str(),               /* Text name for the task.                */
              stack,                      /* Stack size in words, not bytes.        */
              param,                       /* Parameter passed into the task.       */
              tskIDLE_PRIORITY,           /* Priority at which the task is created. */
              NULL) != pdPASS)
  {
    throw std::runtime_error("Unable to create Task thread");
  }
}

void CreateTaskCore(const TaskFunction_t &func, std::string&& name, void *param, uint8_t core, uint32_t stack) {
  if(xTaskCreatePinnedToCore(
              func,                       /* Function that implements the task.     */
              name.c_str(),               /* Text name for the task.                */
              stack,                      /* Stack size in words, not bytes.        */
              param,                       /* Parameter passed into the task.       */
              tskIDLE_PRIORITY,           /* Priority at which the task is created. */
              NULL, core) != pdPASS)
  {
    throw std::runtime_error("Unable to create Task thread");
  }
}

void CreateQueue(QueueHandle_t& queue, uint32_t length, uint32_t size) {
  if(length == 0 || size == 0 || (queue = xQueueCreate(length, size)) == NULL) {
    throw std::runtime_error("Unable to create queue");
  }
}