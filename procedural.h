#ifndef WHATS_UP_PROCEDURAL_H_
#define WHATS_UP_PROCEDURAL_H_

#include <map>
#include <vector>

#include "buffer.h"
#include "event.h"
#include "production.h"

namespace wu::actr {

using Buffers = std::map<std::string, Buffer *>;

}  // namespace wu::actr

namespace wu::actr::procedural {

class Module {
 public:
  //
  Module(EventQueue *event_queue, Buffers buffers)
      : event_queue_(event_queue), buffers_(buffers) {}

  //
  void Add(Production production);

  //
  bool ResolveConflicts(double time);

  //
  void ScheduleConflictResolution(double time);

 private:
  //
  EventQueue *event_queue_;

  //
  std::vector<Production> productions_;

  //
  Buffers buffers_;
};

}  // namespace wu::actr::procedural

#endif
