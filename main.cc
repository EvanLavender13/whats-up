#include <functional>
#include <iostream>
#include <map>
#include <string>
#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "agent.h"
#include "chunk.h"

int main() {
  LOG(INFO) << __FUNCTION__ << "[Start]";

  // double delta_time_s = 1.0 / 60.0;
  double delta_time = 0.25;
  std::chrono::milliseconds sleep_duration_ms(100);

  //
  wu::actr::Agent agent;

  // `production-1`
  {
    // TODO: Creating these is tedious... think of something better
    auto query_slots(wu::actr::SlotsType({{"goal", "goal-1"}}));
    auto mod_slots(wu::actr::SlotsType({{"goal", "goal-2"}}));

    wu::actr::Conditions conditions = {
        {"goal", wu::actr::buffer::Query(query_slots)}};
    wu::actr::Actions actions = {{"goal", wu::actr::buffer::Modify(mod_slots)}};
    agent.AddProcedure({"production-1", conditions, actions});
  }

  //// `production-2`
  //{
  //  wu::actr::Conditions conditions = {
  //      {"goal", wu::actr::buffer::Query({{"goal", "goal-2"}})}};
  //  wu::actr::Actions actions = {
  //      {"goal", wu::actr::buffer::Modify({{"goal", "goal-3"}})},
  //      {"retrieval", wu::actr::retrieval::Start({{"slot-1", "value-1"}})}};
  //  agent.AddProcedure({"production-2", conditions, actions});
  //}

  //// `production-3`
  //{
  //  wu::actr::Conditions conditions = {
  //      {"retrieval", wu::actr::buffer::Query({{"slot-1", "value-1"}})}};
  //  wu::actr::Actions actions = {
  //      {"goal", wu::actr::buffer::Modify({{"goal", "goal-3"}})},
  //      {"retrieval", wu::actr::buffer::Clear()}};
  //  agent.AddProcedure({"production-3", conditions, actions});
  //}

  //
  auto goal_slots(wu::actr::SlotsType({{"goal", "goal-1"}}));
  agent.Focus({"goal-chunk", goal_slots, 0.0});

  //
  auto chunk_slots(wu::actr::SlotsType({{"slot-1", "value-1"}}));
  agent.Add({"chunk-1", chunk_slots, 0.0});

  //
  while (agent.Step(delta_time)) {
    std::this_thread::sleep_for(sleep_duration_ms);
  }

  LOG(INFO) << __FUNCTION__ << "[Exit]";
  return 0;
}