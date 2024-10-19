#ifndef WHATS_UP_CHUNK_H_
#define WHATS_UP_CHUNK_H_

#include <iostream>
#include <map>
#include <string>

namespace wu::actr {

//
using Slots = std::map<std::string, std::string>;

//
class Chunk {
 public:
  //
  Chunk(std::string name, Slots slots) : name_(name), slots_(slots) {}

  //
  std::string Modify(Slots slots);

  //
  bool SlotEquals(Slots slots);

  //
  std::string name() { return name_; }

  //
  Slots slots() { return slots_; }

  //
  friend std::ostream& operator<<(std::ostream& stream, const Chunk& chunk) {
    stream << "[" << chunk.name_ << " slots=[";
    for (auto& slot : chunk.slots_) {
      stream << slot.first << " " << slot.second;
    }
    stream << "]]";

    return stream;
  }

 private:
  //
  std::string name_;

  //
  Slots slots_;
};

}  // namespace wu::actr

#endif