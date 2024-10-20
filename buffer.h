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
  bool Full() { return chunk_.has_value(); }

  //
  bool Failure() { return failure_ && !chunk_.has_value(); }

  //
  bool Requested() { return chunk_.has_value() && requested_; }

  //
  bool Unrequested() { return chunk_.has_value() && !requested_; }

  //
  bool Free() { return module_->state() == module::kFree; }

  //
  bool Busy() { return module_->state() == module::kBusy; }

  //
  bool Error() { return module_->state() == module::kError; }

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

//
namespace wu::actr::buffer {

//
using Test = std::function<bool(Buffer *)>;

//
using Action = std::pair<std::function<void(Buffer *)>, int>;

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
static Test Free() {
  return [](Buffer *buffer) { return buffer->Free(); };
}

//
static Test Busy() {
  return [](Buffer *buffer) { return buffer->Busy(); };
}

//
static Test Error() {
  return [](Buffer *buffer) { return buffer->Error(); };
}

//
static Action Clear() {
  return {[](Buffer *buffer) { buffer->Clear(); }, 10};
}

//
static Action Modify(Slots slots) {
  return {[slots](Buffer *buffer) { buffer->Modify(slots); }, 100};
}

//
// static Action Overwrite(Slots slots) {
//  return [slots](Buffer *buffer) { buffer->Overwrite(slots); };
//}

//
static Action Request(Slots slots) {
  return {[slots](Buffer *buffer) { buffer->Request(slots); }, 50};
}

}  // namespace wu::actr::buffer

#endif