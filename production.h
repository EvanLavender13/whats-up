#ifndef WHATS_UP_PRODUCTION_H_
#define WHATS_UP_PRODUCTION_H_

#include "buffer.h"

namespace wu::actr {

using Conditions = std::map<std::string, buffer::Test>;
using Actions = std::map<std::string, buffer::Action>;

//
class Production {
 public:
  //
  Production(std::string name, Conditions conditions, Actions actions)
      : name_(name), conditions_(conditions), actions_(actions) {}

  //
  std::string name() { return name_; }

  //
  Conditions conditions() { return conditions_; }

  //
  Actions actions() { return actions_; }

  //
  friend std::ostream& operator<<(std::ostream& stream,
                                  const Production& production) {
    stream << "[" << production.name_ << " condition-buffers=[";

    for (auto& condition : production.conditions_) {
      stream << condition.first << " ";
    }

    stream << "\b]"
           << " action-buffers=[";
    for (auto& action : production.actions_) {
      stream << action.first << " ";
    }
    stream << "\b]";

    return stream;
  }

 private:
  //
  std::string name_;

  //
  Conditions conditions_;

  //
  Actions actions_;
};

}  // namespace wu::actr

#endif
