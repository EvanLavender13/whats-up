#ifndef WHATS_UP_GOAL_H_
#define WHATS_UP_GOAL_H_

#include "buffer.h"
#include "module.h"
#include "production.h"

namespace wu::actr::goal {

//
class Module : actr::Module {
 public:
  //
  Module(EventQueue* event_queue)
      : actr::Module("goal", event_queue), buffer_(this) {}

  //
  bool Request(Slots &slots) override { return true; };

  //
  void Focus(Chunk chunk);

  //
  Buffer* buffer() { return &buffer_; }

 private:
  //
  Buffer buffer_;
};

}  // namespace wu::actr::goal

#endif
