//
//
//

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "at_list.h"
#include "uart.h"

#include <memory>
#include <mutex>

std::mutex g_i_mutex;

class Entity {
  int m_Size;
public:
  Entity(int size = 0) : m_Size {size} {
    Serial.println("Entity Constructor");
  }

  ~Entity() {
    Serial.println("Entity Destructor");
  }
};

/* Task to be created. */
void vTaskCode1(void *pvParameters)
{
  int counter = 0;
  while(true)
  {
    g_i_mutex.lock();
    std::string str = "TASK: " + std::to_string((uint32_t) pvParameters) + " COUNTER: " + std::to_string(counter++);
    Serial.println(str.c_str());
    g_i_mutex.unlock();
    delay(1000);
  }
}

void vTaskCode2(void *pvParameters)
{
  int counter = 0;
  while(true)
  {
    g_i_mutex.lock();
    std::string str = "TASK: " + std::to_string((uint32_t) pvParameters) + " COUNTER: " + std::to_string(counter++);
    Serial.println(str.c_str());
    g_i_mutex.unlock();
    delay(1000);
  }
}

void vTaskCode3(void *pvParameters)
{
  int counter = 0;
  while(true)
  {
    g_i_mutex.lock();
    std::string str = "TASK: " + std::to_string((uint32_t) pvParameters) + " COUNTER: " + std::to_string(counter++);
    Serial.println(str.c_str());
    g_i_mutex.unlock();
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Uart* inst1 = Uart::getInstance();

  {
    std::unique_ptr<Entity> unique =  std::make_unique<Entity>();
  }

  /* Create the task, storing the handle. */
  xTaskCreate(
              vTaskCode1,       /* Function that implements the task. */
              "NAME1",          /* Text name for the task. */
              4096,      /* Stack size in words, not bytes. */
              (void *)1,    /* Parameter passed into the task. */
              tskIDLE_PRIORITY,/* Priority at which the task is created. */
              NULL);      /* Used to pass out the created task's handle. */

    /* Create the task, storing the handle. */
    xTaskCreate(
                vTaskCode2,       /* Function that implements the task. */
                "NAME2",          /* Text name for the task. */
                4096,      /* Stack size in words, not bytes. */
                (void *)2,    /* Parameter passed into the task. */
                tskIDLE_PRIORITY,/* Priority at which the task is created. */
                NULL);      /* Used to pass out the created task's handle. */

    /* Create the task, storing the handle. */
    xTaskCreate(
                vTaskCode3,       /* Function that implements the task. */
                "NAME3",          /* Text name for the task. */
                4096,      /* Stack size in words, not bytes. */
                (void *)3,    /* Parameter passed into the task. */
                tskIDLE_PRIORITY,/* Priority at which the task is created. */
                NULL);      /* Used to pass out the created task's handle. */
}

void loop() {
  // put your main code here, to run repeatedly:
}