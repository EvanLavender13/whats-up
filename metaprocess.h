#ifndef WHATS_UP_PROCESS_H_
#define WHATS_UP_PROCESS_H_

#include <functional>
#include <iostream>

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "event.h"
#include "production.h"

namespace wu::actr {

//
class Process {
 public:
  //
  Process(event::Queue *event_queue, std::vector<Module *> modules)
      : event_queue_(event_queue), modules_(modules) {
    LOG(INFO) << __FUNCTION__ << "[Created]";

    //
    event_queue_->Signal("conflict-resolution", time_);
  }

  //
  bool Run(double delta_time);

  //
  double time() const { return time_; }

 private:
  //
  event::Queue *event_queue_;

  //
  double time_{0.0};

  //
  int step_{1};

  //
  std::vector<Module *> modules_;
};

}  // namespace wu::actr

#endif