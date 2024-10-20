#ifndef WHATS_UP_BUFFER_H_
#define WHATS_UP_BUFFER_H_

#include <functional>
#include <optional>
#include <string>

#include "chunk.h"
#include "module.h"

namespace wu::actr {

//
class Buffer {
 public:
  //
  Buffer(Module *module) : module_(module) {}

  //
  std::string Read() {
    return chunk_.has_value() ? chunk_.value().name() : "nil";
  }

  //
  bool Query(Slots slots);

  //
  std::string Clear();

  //
  std::string Set(Chunk chunk, bool requested = true, bool clear = true);

  //
  // std::string Overwrite(Chunk chunk);

  //
  std::string Modify(Slots slots);

  //
  bool Request(Slots slots);

  //
  bool Empty() { return !chunk_.has_value() && !failure_; }

  //
  bool Full() { return !Empty(); }

  //
  bool Failure() { return failure_ && !chunk_.has_value(); }

  //
  bool Requested();

  //
  bool Unrequested();

 private:
  //
  Module *module_;

  //
  std::optional<Chunk> chunk_{std::nullopt};

  //
  bool failure_{false};

  //
  bool requested_{false};
};

}  // namespace wu::actr

namespace wu::actr::buffer {

//
using Test = std::function<bool(Buffer *)>;

//
using Action = std::function<void(Buffer *)>;

//
static Test Query(Slots slots) {
  return [slots](Buffer *buffer) { return buffer->Query(slots); };
}

//
static Test Empty() {
  return [](Buffer *buffer) { return buffer->Empty(); };
}

//
static Test Full() {
  return [](Buffer *buffer) { return buffer->Full(); };
}

//
static Action Clear() {
  return [](Buffer *buffer) { buffer->Clear(); };
}

//
static Action Modify(Slots slots) {
  return [slots](Buffer *buffer) { buffer->Modify(slots); };
}

//
// static Action Overwrite(Slots slots) {
//  return [slots](Buffer *buffer) { buffer->Overwrite(slots); };
//}

//
static Action Request(Slots slots) {
  return [slots](Buffer *buffer) { buffer->Request(slots); };
}

}  // namespace wu::actr::buffer

#endif