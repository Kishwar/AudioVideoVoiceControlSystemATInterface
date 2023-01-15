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

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <stdint.h>
#include <string>

/**
 * Creates a freeRTOS task assigned to any core
 * 
 * func:    callback function
 * name:    name of the function
 * stack:   stack size. default: 4096
 * 
 * exception: throws runtime_error exception
*/
void CreateTask(const TaskFunction_t& func, std::string&& name, void *param, uint32_t stack = 4096);

/**
 * Creates a freeRTOS task assigned to defined core
 * 
 * func:    callback function
 * name:    name of the function
 * core:    core id number
 * stack:   stack size. default: 4096
 * 
 * exception: throws runtime_error exception
*/
void CreateTaskCore(const TaskFunction_t& func, std::string&& name, void *param, uint8_t core, uint32_t stack = 4096);

/**
 * Creates a freeRTOS queue
 * 
 * queue:   queue handle identifier
 * length:  number of elements in the queue
 * size:    size of each element in the queue
 * 
 * exception: throws runtime_error exception
*/
void CreateQueue(QueueHandle_t& queue, uint32_t length, uint32_t size);