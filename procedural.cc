#include "procedural.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr::procedural {

void Module::Add(Production production) {
  LOG(INFO) << __FUNCTION__ << "[production=" << production << "]";

  productions_.emplace_back(production);
}

bool Module::ResolveConflicts(double time) {
  LOG(INFO) << __FUNCTION__ << "[Starting]";

  bool any_match = false;

  for (Production &production : productions_) {
    LOG(INFO) << __FUNCTION__ << "[production=" << production << "]";

    bool match = true;

    Conditions conditions = production.conditions();
    for (auto &[buffer_name, condition] : conditions) {
      match &= condition(buffers_[buffer_name]);
    }

    if (match) {
      //
      any_match = true;

      //
      Actions actions = production.actions();

      //
      double event_time = time + 0.5;

      LOG(INFO) << __FUNCTION__
                << "[Production "
                   "matched; scheduling action(s) at event_time="
                << event_time << "]";

      //
      for (auto &[module_name, action_pair] : actions) {
        auto &[action, priority] = action_pair;

        Event event("procedural", production.name(), event_time, priority,
                    [this, action, module_name, event_time]() {
                      action(buffers_[module_name]);

                      ScheduleConflictResolution(event_time);
                      return true;
                    });

        event_queue_->emplace(event);
      }
    }
  }

  LOG(INFO) << __FUNCTION__
            << "[Finished any_match=" << (any_match ? "true" : "false") << "]";
  return any_match;
}

void Module::ScheduleConflictResolution(double time) {
  LOG(INFO) << __FUNCTION__ << "[time=" << time << "]";

  Event event("procedural", "conflict-resolution", time, -1,
              [this, time]() { return ResolveConflicts(time); });

  event_queue_->emplace(event);
}

}  // namespace wu::actr::procedural