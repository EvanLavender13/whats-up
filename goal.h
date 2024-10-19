#ifndef WHATS_UP_GOAL_H_
#define WHATS_UP_GOAL_H_

#include "buffer.h"
#include "production.h"

namespace wu::actr::goal {

//
class Module {
 public:
  //
  Module() : buffer_("goal") {}

  //
  Buffer* buffer() { return &buffer_; }

 private:
  //
  Buffer buffer_;
};

}  // namespace wu::actr::goal

#endif
