#ifndef WHATS_UP_AGENT_H_
#define WHATS_UP_AGENT_H_

#include "declarative.h"
#include "goal.h"
#include "metaprocess.h"
#include "procedural.h"

namespace wu::actr {

class Agent {
 public:
  //
  Agent()
      : goal_module_(&event_queue_),
        declarative_module_(&event_queue_),
        procedural_module_(&event_queue_,
                           {{"goal", goal_module_.buffer()},
                            {"retrieval", declarative_module_.buffer()}}),
        metaprocess_(&event_queue_, {&goal_module_, &declarative_module_,
                                     &procedural_module_}) {}

  //
  bool Step(double delta_time) {
    LOG(INFO) << __FUNCTION__ << "[delta_time=" << delta_time << "]";

    return metaprocess_.Run(delta_time);
  }

  //
  void Add(Chunk chunk) { declarative_module_.Add(chunk); }

  //
  void AddProcedure(Production production) {
    procedural_module_.Add(production);
  }

  //
  void Focus(Chunk chunk) { goal_module_.Focus(chunk); }

 private:
  //
  event::Queue event_queue_;

  //
  goal::Module goal_module_;

  //
  declarative::Module declarative_module_;

  //
  procedural::Module procedural_module_;

  //
  Process metaprocess_;
};

}  // namespace wu::actr

#endif
