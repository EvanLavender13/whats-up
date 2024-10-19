#ifndef WHATS_UP_DECLARATIVE_H_
#define WHATS_UP_DECLARATIVE_H_

#include "buffer.h"

namespace wu::actr::declarative {

//
class Module {
 public:
  //
  Module() : buffer_("retrieval") {}

  //
  Buffer* buffer() { return &buffer_; }

 private:
  //
  Buffer buffer_;
};

}  // namespace wu::actr::declarative

#endif
