#ifndef WHATS_UP_MODULE_H_
#define WHATS_UP_MODULE_H_

#include "chunk.h"
#include "event.h"

namespace wu::actr {

class Module {
 public:
  //
  virtual bool Request(Slots &slots) = 0;

  //
  std::string name() { return name_; }

 protected:
  //
  Module(std::string name, EventQueue *event_queue)
      : name_(name), event_queue_(event_queue) {}

  //
  std::string name_;

  //
  EventQueue *event_queue_;

 private:
};

}  // namespace wu::actr

#endif