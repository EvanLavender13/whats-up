#include "actr/procedural.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr::procedural {

void Module::Add(Production production) {
  LOG(INFO) << __FUNCTION__ << "[production=" << production << "]";

  productions_.emplace_back(production);
}

bool Module::ResolveConflicts() {
  //
  if (state_ == module::kBusy) {
    LOG(INFO) << __FUNCTION__ << "[Busy]";

    return false;
  }

  LOG(INFO) << __FUNCTION__ << "[Starting]";

  bool any_match = false;

  //
  for (Production &production : productions_) {
    LOG(INFO) << __FUNCTION__ << "[production=" << production << "]";

    bool match = true;

    //
    Conditions conditions = production.conditions();
    for (auto &[buffer_name, condition] : conditions) {
      match &= condition(buffers_[buffer_name]);
    }

    if (match) {
      //
      state(module::kBusy);

      //
      any_match = true;

      //
      Actions actions = production.actions();

      //
      double event_time = time_ + 0.5;

      //
      for (auto &action_data : actions) {
        auto &[buffer_name, name, action, priority] = action_data;

        Event event(buffer_name, name, event_time, priority,
                    [this, action, buffer_name, event_time]() {
                      action(buffers_[buffer_name]);
                    });

        LOG(INFO) << __FUNCTION__ << "[Scheduling event=" << event << "]";

        event_queue_->Add(event);
      }

      //
      Event event(name_, "buffer-free", event_time, -1,
                  [this]() { state(module::kFree); });

      LOG(INFO) << __FUNCTION__ << "[Scheduling event=" << event << "]";

      //
      event_queue_->Add(event);

      //
      event_queue_->Signal("conflict-resolution", event_time);
    }
  }

  LOG(INFO) << __FUNCTION__
            << "[Finished any_match=" << (any_match ? "true" : "false") << "]";
  return any_match;
}

void Module::ScheduleConflictResolution(double time) {
  LOG(INFO) << __FUNCTION__ << "[time=" << time << "]";

  Event event("procedural", "conflict-resolution", time, -1000,
              [this, time]() { ResolveConflicts(); });

  event_queue_->Add(event);
}

}  // namespace wu::actr::procedural