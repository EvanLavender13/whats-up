#ifndef WHATS_UP_BUFFER_H_
#define WHATS_UP_BUFFER_H_

#include <functional>
#include <optional>
#include <string>

#include "chunk.h"
#include "module.h"

namespace wu::actr {

//
class ClearListener {
 public:
  //
  virtual void OnClear(Chunk chunk) = 0;

 private:
};

//
class Buffer {
 public:
  //
  Buffer(Module *module) : module_(module) {}

  //
  Buffer(Module *module, ClearListener *clear_listener)
      : module_(module), clear_listener_(clear_listener) {}

  //
  std::string Read() {
    return chunk_.has_value() ? chunk_.value().name() : "nil";
  }

  //
  bool Query(Slots slots);

  //
  void Clear();

  //
  void Set(Chunk chunk, bool requested = true, bool clear = true);

  //
  void Overwrite(Chunk chunk, bool requested = true);

  //
  std::string Modify(Slots slots);

  //
  void Request(Slots slots);

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

  //
  void failure(bool failure) { failure_ = failure; }

 private:
  //
  Module *module_;

  //
  std::optional<Chunk> chunk_{std::nullopt};

  //
  bool failure_{false};

  //
  bool requested_{false};

  //
  bool harvest_{false};

  //
  std::optional<ClearListener *> clear_listener_{std::nullopt};
};

}  // namespace wu::actr

//
namespace wu::actr::buffer {

//
using Test = std::function<bool(Buffer *)>;

//
using Action = std::tuple<std::string, std::function<void(Buffer *)>, int>;

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
  return {"buffer-clear", [](Buffer *buffer) { buffer->Clear(); }, 10};
}

//
static Action Set(Chunk chunk) {
  return {"buffer-set", [chunk](Buffer *buffer) { buffer->Set(chunk); }, 100};
}

//
static Action Modify(Slots slots) {
  return {"buffer-modify", [slots](Buffer *buffer) { buffer->Modify(slots); },
          100};
}

//
// static Action Overwrite(Slots slots) {
//  return [slots](Buffer *buffer) { buffer->Overwrite(slots); };
//}

//
static Action Request(Slots slots) {
  return {"buffer-request", [slots](Buffer *buffer) { buffer->Request(slots); },
          50};
}

}  // namespace wu::actr::buffer

//
namespace wu::actr::retrieval {

static buffer::Action Start(Slots slots) {
  return {"start-retrieval",
          [slots](Buffer *buffer) { buffer->Request(slots); }, 50};
}

}  // namespace wu::actr::retrieval

#endif