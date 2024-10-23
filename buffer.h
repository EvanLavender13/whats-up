#ifndef WHATS_UP_BUFFER_H_
#define WHATS_UP_BUFFER_H_

#include <functional>
#include <optional>
#include <string>

#include "chunk.h"
#include "module.h"

//
namespace wu::actr::buffer {

//
class ClearListener {
 public:
  //
  virtual void OnBufferClear(std::string chunk_name) = 0;

 private:
};

}  // namespace wu::actr::buffer

namespace wu::actr {

//
class Buffer {
 public:
  //
  Buffer(std::string name, Module *module) : name_(name), module_(module) {}

  //
  Buffer(std::string name, Module *module,
         buffer::ClearListener *clear_listener)
      : name_(name), module_(module), clear_listener_(clear_listener) {}

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
  void Modify(Slots slots);

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
  std::string name_;

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
  std::optional<buffer::ClearListener *> clear_listener_{std::nullopt};
};

}  // namespace wu::actr

//
namespace wu::actr::buffer {

//
using Test = std::pair<std::string, std::function<bool(Buffer *)>>;

//
using Action =
    std::tuple<std::string, std::string, std::function<void(Buffer *)>, int>;

//
static Test Query(std::string buffer_name, Slots slots) {
  return {buffer_name,
          [slots](Buffer *buffer) { return buffer->Query(slots); }};
}

//
static Test Empty(std::string buffer_name) {
  return {buffer_name, [](Buffer *buffer) { return buffer->Empty(); }};
}

//
static Test Full(std::string buffer_name) {
  return {buffer_name, [](Buffer *buffer) { return buffer->Full(); }};
}

//
static Test Free(std::string buffer_name) {
  return {buffer_name, [](Buffer *buffer) { return buffer->Free(); }};
}

//
static Test Busy(std::string buffer_name) {
  return {buffer_name, [](Buffer *buffer) { return buffer->Busy(); }};
}

//
static Test Error(std::string buffer_name) {
  return {buffer_name, [](Buffer *buffer) { return buffer->Error(); }};
}

//
static Action Clear(std::string buffer_name) {
  return {buffer_name, "clear", [](Buffer *buffer) { buffer->Clear(); }, 10};
}

//
static Action Set(std::string buffer_name, Chunk chunk) {
  return {buffer_name, "set", [chunk](Buffer *buffer) { buffer->Set(chunk); },
          100};
}

//
static Action Modify(std::string buffer_name, Slots slots) {
  return {buffer_name, "modify",
          [slots](Buffer *buffer) { buffer->Modify(slots); }, 100};
}

//
// static Action Overwrite(Slots slots) {
//  return [slots](Buffer *buffer) { buffer->Overwrite(slots); };
//}

//
static Action Request(std::string buffer_name, Slots slots) {
  return {buffer_name, "request",
          [slots](Buffer *buffer) { buffer->Request(slots); }, 50};
}

}  // namespace wu::actr::buffer

//
namespace wu::actr::goal {

static buffer::Action Focus(Chunk chunk) { return buffer::Set("goal", chunk); }

static buffer::Action Modify(Slots slots) {
  return buffer::Modify("goal", slots);
}

}  // namespace wu::actr::goal

//
namespace wu::actr::retrieval {

static buffer::Action Start(Slots slots) {
  return buffer::Request("retrieval", slots);
}

}  // namespace wu::actr::retrieval

#endif