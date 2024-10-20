#ifndef WHATS_UP_MODULE_H_
#define WHATS_UP_MODULE_H_

#include "chunk.h"
#include "event.h"

namespace wu::actr::module {

enum State { kFree, kBusy, kError };

}

namespace wu::actr {

class Module {
 public:
  //
  virtual void Request(Slots &slots) = 0;

  //
  std::string name() { return name_; }

  //
  void state(module::State state) { state_ = state; }

  //
  module::State state() const { return state_; }

  //
  void time(double time) { time_ = time; }

 protected:
  //
  Module(std::string name, event::Queue *event_queue)
      : name_(name), event_queue_(event_queue) {}

  //
  std::string name_;

  //
  event::Queue *event_queue_;

  //
  module::State state_{module::kFree};

  //
  double time_{0.0};

 private:
};

}  // namespace wu::actr

#endif