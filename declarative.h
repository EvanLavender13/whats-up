#ifndef WHATS_UP_DECLARATIVE_H_
#define WHATS_UP_DECLARATIVE_H_

#include <map>

#include "buffer.h"
#include "event.h"
#include "module.h"

namespace wu::actr::declarative {

//
class Module : public actr::Module, public ClearListener {
 public:
  //
  Module(event::Queue *event_queue)
      : actr::Module("retrieval", event_queue), buffer_(this, this) {}

  //
  void Request(Slots &slots) override;

  //
  void OnClear(Chunk chunk) override;

  //
  void Retrieve(Slots &slots);

  //
  bool Add(Chunk chunk) {
    chunks_.emplace(chunk.name(), chunk);
    return true;
  }

  //
  Buffer *buffer() { return &buffer_; }

 private:
  //
  double BaseLevelActivation(Chunk &chunk);

  //
  Buffer buffer_;

  //
  std::map<std::string, Chunk> chunks_;

  //
  double decay_{0.5};

  //
  double latency_{1.0};

  //
  double latency_exp_{1.0};

  //
  double threshold_{0.0};
};

}  // namespace wu::actr::declarative

#endif
