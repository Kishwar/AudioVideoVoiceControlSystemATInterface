/**
 * @file at_msg.h
 *
 * @brief AT Command Message
 *
 * @ingroup msg_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include <string>
#include <stdint.h>

class atCommandReq {
  std::string *ptr;
public:
  atCommandReq(std::string *p) : ptr{p} {
    Serial.println("atCommandReq()");
  }
  std::string *getPayLoad(void) {
    return ptr;
  }
  ~atCommandReq() {
    delete ptr;
    ptr = nullptr;
    Serial.println("~atCommandReq()");
  }
};


class atCommandRsp {
  char *ptr;
  uint32_t len;
  uint32_t rspCode;
public:
  atCommandRsp(char *p, uint32_t l, uint32_t c) : ptr{p}, len{l}, rspCode{c} {}
  ~atCommandRsp() {
    delete ptr;
    len = 0;
    rspCode = 0;
  }
};