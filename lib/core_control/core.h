/**
 * @file core.h
 *
 * @brief responsible for creating core service using RTOS
 *
 * @ingroup core_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include <stdint.h>
#include <string>

#include "freertos/FreeRTOS.h"

void CreateTask(const TaskFunction_t &func, std::string&&, uint32_t stack = 4096);

void CreateTaskCore(const TaskFunction_t &func, std::string&&, uint8_t core, uint32_t stack = 4096);