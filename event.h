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
  Event(std::string module, std::string name, double time,
        std::function<bool()> action)
      : module_(module), name_(name), time_(time), action_(action) {}

  //
  bool Exec() { return action_(); }

  //
  std::string module() { return module_; }

  //
  double time() const { return time_; }

  //
  friend std::ostream& operator<<(std::ostream& stream, const Event& event) {
    stream << "[" << event.module_ << " " << event.name_ << "]";
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
  std::function<bool()> action_;
};

class CompareEvents {
 public:
  bool operator()(Event a, Event b) { return a.time() < b.time(); }
};

using EventQueue =
    std::priority_queue<Event, std::vector<Event>, CompareEvents>;

}  // namespace wu::actr

#endif
