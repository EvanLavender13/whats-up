#ifndef WHATS_UP_EVENT_H_
#define WHATS_UP_EVENT_H_

#include <functional>
#include <iostream>
#include <map>
#include <queue>

namespace wu::actr {

class Event {
 public:
  //
  Event(std::string module, std::string name, double time, int priority,
        std::function<void()> action)
      : module_(module),
        name_(name),
        time_(time),
        priority_(priority),
        action_(action) {}

  //
  void Exec() { action_(); }

  //
  std::string module() { return module_; }

  //
  double time() { return time_; }

  //
  int priority() { return priority_; }

  //
  friend std::ostream& operator<<(std::ostream& stream, const Event& event) {
    stream << "[module=" << event.module_ << " name=" << event.name_
           << " time=" << event.time_ << " priority=" << event.priority_ << "]";
    // for (auto& slot : chunk.slots_) {
    //   stream << slot.first << ", " << slot.second;
    // }
    // stream << "]";

    return stream;
  }

 private:
  //
  std::string module_{"default-module"};

  //
  std::string name_{"default-event"};

  //
  double time_{0.0};

  //
  int priority_{0};

  //
  std::function<void()> action_;
};

}  // namespace wu::actr

//
namespace wu::actr::event {

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
using QueueType = std::priority_queue<Event, std::vector<Event>, CompareEvents>;

//
class Queue {
 public:
  //
  void Add(Event event) { queue_.emplace(event); }

  //
  Event Next() const { return queue_.top(); }

  //
  void Pop() { queue_.pop(); }

  //
  bool Empty() { return queue_.empty(); }

  //
  int Size() { return queue_.size(); }

  //
  void AddSignal(std::string name, std::function<void(double)> signal) {
    signals_.emplace(name, signal);
  }

  //
  void Signal(std::string name, double time) { signals_[name](time); }

 private:
  //
  QueueType queue_;

  //
  std::map<std::string, std::function<void(double)>> signals_;
};

}  // namespace wu::actr::event

#endif
