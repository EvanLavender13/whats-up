#ifndef WHATS_UP_DECLARATIVE_H_
#define WHATS_UP_DECLARATIVE_H_

#include <map>

#include "buffer.h"
#include "module.h"

namespace wu::actr::declarative {

//
class Module : actr::Module {
 public:
  //
  Module(EventQueue *event_queue)
      : actr::Module("retrieval", event_queue), buffer_(this) {}

  //
  bool Request(Slots &slots) override;

  //
  bool Retrieve(Slots &slots);

  //
  bool Add(Chunk chunk) {
    chunks_.emplace(chunk.name(), chunk);
    return true;
  }

  //
  Buffer *buffer() { return &buffer_; }

 private:
  //
  Buffer buffer_;

  //
  std::map<std::string, Chunk> chunks_;
};

}  // namespace wu::actr::declarative

#endif
