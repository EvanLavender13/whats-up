#include <functional>
#include <iostream>
#include <map>
#include <string>
#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "metaprocess.h"

int main() {
  LOG(INFO) << "main[Start]";

  // double delta_time_s = 1.0 / 60.0;
  double delta_time_s = 0.1;
  std::chrono::milliseconds sleep_duration_ms(100);

  wu::actr::EventQueue event_queue;

  //
  wu::actr::goal::Module goal_module;
  wu::actr::Buffer *goal_buffer = goal_module.buffer();

  //
  wu::actr::declarative::Module declarative_module;
  wu::actr::Buffer *retrieval_buffer = declarative_module.buffer();

  //
  wu::actr::procedural::Module procedural_module(
      &event_queue, {{"goal", goal_buffer}, {"retrieval", retrieval_buffer}});

  //
  wu::actr::Slots goal_slots = {{"task", "test-task"}};
  wu::actr::Slots next_slots = {{"task", "test-sub-task"}};
  wu::actr::Chunk goal_chunk("test-goal", goal_slots);
  goal_buffer->Set(goal_chunk, false);

  //
  wu::actr::Conditions conditions = {
      {"goal", wu::actr::buffer::Query(goal_slots)}};
  wu::actr::Actions actions = {{"goal", wu::actr::buffer::Modify(next_slots)}};
  procedural_module.Add({"test-production", conditions, actions});

  //
  wu::actr::Process metaprocess(&event_queue, &goal_module, &procedural_module);
  while (metaprocess.Run(delta_time_s)) {
    std::this_thread::sleep_for(sleep_duration_ms);
  }

  LOG(INFO) << "main[Exit]";
  return 0;
}