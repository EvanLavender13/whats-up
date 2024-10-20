#include <functional>
#include <iostream>
#include <map>
#include <string>
#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "declarative.h"
#include "goal.h"
#include "metaprocess.h"
#include "procedural.h"

int main() {
  LOG(INFO) << __FUNCTION__ << "[Start]";

  // double delta_time_s = 1.0 / 60.0;
  double delta_time = 0.25;
  std::chrono::milliseconds sleep_duration_ms(100);

  //
  wu::actr::EventQueue event_queue;

  //
  wu::actr::goal::Module goal_module(&event_queue);

  //
  wu::actr::declarative::Module declarative_module(&event_queue);

  //
  wu::actr::procedural::Module procedural_module(
      &event_queue, {{"goal", goal_module.buffer()},
                     {"retrieval", declarative_module.buffer()}});

  // `production-1`
  {
    wu::actr::Conditions conditions = {
        {"goal", wu::actr::buffer::Query({{"goal", "goal-1"}})}};
    wu::actr::Actions actions = {
        {"goal", wu::actr::buffer::Modify({{"goal", "goal-2"}})}};
    procedural_module.Add({"production-1", conditions, actions});
  }

  // `production-2`
  {
    wu::actr::Conditions conditions = {
        {"goal", wu::actr::buffer::Query({{"goal", "goal-2"}})}};
    wu::actr::Actions actions = {
        {"goal", wu::actr::buffer::Modify({{"goal", "goal-3"}})},
        {"retrieval", wu::actr::buffer::Request({{"slot-1", "value-1"}})}};
    procedural_module.Add({"production-2", conditions, actions});
  }

  //
  goal_module.Focus({"goal-chunk", {{"goal", "goal-1"}}});

  //
  procedural_module.ScheduleConflictResolution(0.0);
  wu::actr::Process metaprocess(&event_queue);
  while (metaprocess.Run(delta_time)) {
    std::this_thread::sleep_for(sleep_duration_ms);
  }

  LOG(INFO) << __FUNCTION__ << "[Exit]";
  return 0;
}