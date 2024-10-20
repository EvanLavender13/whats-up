#ifndef WHATS_UP_PROCEDURAL_H_
#define WHATS_UP_PROCEDURAL_H_

#include <map>
#include <vector>

#include "buffer.h"
#include "module.h"
#include "production.h"

//
namespace wu::actr {

using Buffers = std::map<std::string, Buffer *>;

}  // namespace wu::actr

//
namespace wu::actr::procedural {

class Module : public actr::Module {
 public:
  //
  Module(event::Queue *event_queue, Buffers buffers)
      : actr::Module("production", event_queue), buffers_(buffers) {
    event_queue_->AddSignal("conflict-resolution", [this](double time) {
      ScheduleConflictResolution(time);
    });
  }

  //
  void Request(Slots &slots) override {}

  //
  void Add(Production production);

  //
  bool ResolveConflicts(double time);

  //
  void ScheduleConflictResolution(double time);

 private:
  //
  std::vector<Production> productions_;

  //
  Buffers buffers_;
};

}  // namespace wu::actr::procedural

#endif
