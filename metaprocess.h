#ifndef WHATS_UP_PROCESS_H_
#define WHATS_UP_PROCESS_H_

#include <functional>
#include <iostream>

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "chunk.h"
#include "declarative.h"
#include "event.h"
#include "goal.h"
#include "procedural.h"
#include "production.h"

namespace wu::actr {

//
class Process {
 public:
  //
  Process(EventQueue *event_queue, goal::Module *goal_module,
          procedural::Module *procedural_module)
      : event_queue_(event_queue),
        goal_module_(goal_module),
        procedural_module_(procedural_module) {
    LOG(INFO) << "wu::actr::Process[Creating]";
    procedural_module_->ScheduleConflictResolution(time_);
  }

  //
  bool Run(double delta_time);

 private:
  //
  EventQueue *event_queue_;

  //
  double time_{0.0};

  //
  goal::Module *goal_module_;

  //
  procedural::Module *procedural_module_;
};

}  // namespace wu::actr

#endif