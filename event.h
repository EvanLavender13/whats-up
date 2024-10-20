#ifndef WHATS_UP_EVENT_H_
#define WHATS_UP_EVENT_H_

#include <chrono>
#include <functional>
#include <iostream>
#include <queue>

namespace wu::actr {

class Event {
 public:
  //
  Event(std::string module, std::string name, double time, int priority,
        std::function<bool()> action)
      : module_(module),
        name_(name),
        time_(time),
        priority_(priority),
        action_(action) {}

  //
  // Event(std::string module, std::string name, double time, int priority,
  //      buffer::Action action)
  //    : Event(module, name, time, 0, action.second) {}

  //
  bool Exec() { return action_(); }

  //
  std::string module() { return module_; }

  //
  double time() { return time_; }

  //
  int priority() { return priority_; }

  //
  friend std::ostream& operator<<(std::ostream& stream, const Event& event) {
    stream << "[module_=" << event.module_ << " name_=" << event.name_
           << " time_=" << event.time_ << " priority_=" << event.priority_
           << "]";
    // for (auto& slot : chunk.slots_) {
    //   stream << slot.first << ", " << slot.second;
    // }
    // stream << "]";

    return stream;
  }

 private:
  //
  std::string module_;

  //
  std::string name_;

  //
  double time_;

  //
  int priority_{0};

  //
  std::function<bool()> action_;
};

//
class CompareEvents {
 public:
  bool operator()(Event a, Event b) {
    if (a.time() == b.time()) {
      return a.priority() < b.priority();
    }

    return a.time() > b.time();
  }
};

//
using EventQueue =
    std::priority_queue<Event, std::vector<Event>, CompareEvents>;

}  // namespace wu::actr

#endif
