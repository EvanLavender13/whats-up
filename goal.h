#ifndef WHATS_UP_GOAL_H_
#define WHATS_UP_GOAL_H_

#include "buffer.h"
#include "module.h"
#include "production.h"

namespace wu::actr::goal {

//
class Module : public actr::Module {
 public:
  //
  Module(event::Queue* event_queue)
      : actr::Module("goal", event_queue), buffer_(this) {}

  //
  void Request(Slots& slots) override {}

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
