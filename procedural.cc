#include "procedural.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr::procedural {

void Module::Add(Production production) {
  LOG(INFO) << "wu::actr::procedural::Module::Add[production=" << production
            << "]";

  productions_.emplace_back(production);
}

bool Module::ResolveConflicts(double time) {
  LOG(INFO) << "wu::actr::procedural::Module::ResolveConflicts[Starting]";

  bool any_match = false;

  for (Production &production : productions_) {
    LOG(INFO) << "wu::actr::procedural::Module::ResolveConflicts[production="
              << production << "]";

    bool match = true;

    Conditions conditions = production.conditions();
    for (auto &condition_entry : conditions) {
      std::string module_name = condition_entry.first;
      buffer::Test condition_check = condition_entry.second;
      match &= condition_check(buffers_[module_name]);
    }

    if (match) {
      //
      any_match = true;

      //
      Actions actions = production.actions();

      //
      double event_time = time + 0.5;

      LOG(INFO) << "wu::actr::procedural::Module::ResolveConflicts[Production "
                   "matched; scheduling action at event_time="
                << event_time << "]";

      //
      Event event("procedural", "production-exec", event_time,
                  [this, actions]() {
                    for (auto &action_entry : actions) {
                      std::string module_name = action_entry.first;
                      buffer::Action action = action_entry.second;
                      action(buffers_[module_name]);
                    }

                    return true;
                  });

      //
      event_queue_->emplace(event);
    }
  }

  LOG(INFO)
      << "wu::actr::procedural::Module::ResolveConflicts[Finished any_match="
      << any_match << "]";
  return any_match;
}

void Module::ScheduleConflictResolution(double time) {
  LOG(INFO) << "wu::actr::Module::ScheduleConflictResolution[time=" << time
            << "]";

  Event event("procedural", "conflict-resolution", time,
              [this, time]() { return ResolveConflicts(time); });

  event_queue_->emplace(event);
}

}  // namespace wu::actr::procedural