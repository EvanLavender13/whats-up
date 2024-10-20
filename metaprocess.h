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
  Process(EventQueue *event_queue) : event_queue_(event_queue) {}

  //
  bool Run(double delta_time);

 private:
  //
  EventQueue *event_queue_;

  //
  double time_{0.0};
};

}  // namespace wu::actr

#endif