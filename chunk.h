#ifndef WHATS_UP_CHUNK_H_
#define WHATS_UP_CHUNK_H_

#include <iostream>
#include <map>
#include <string>

namespace wu::actr {

//
using SlotsType = std::map<std::string, std::string>;

//
class Slots {
 public:
  //
  Slots() = default;

  //
  Slots(SlotsType values) : values_(values) {}

  //
  void Modify(std::string slot, std::string value) { values_[slot] = value; }

  //
  bool Contains(std::string slot) { return values_.count(slot) > 0; }

  //
  bool SlotEquals(std::string slot, std::string value) {
    return values_[slot] == value;
  }

  //
  SlotsType& values() { return values_; }

 private:
  //
  SlotsType values_;
};

//
class Chunk {
 public:
  //
  Chunk() = default;

  //
  Chunk(std::string name, Slots slots, double creation_time)
      : name_(name), slots_(slots), creation_time_(creation_time) {}

  //
  std::string Modify(Slots& mod_slots);

  //
  bool SlotEquals(Slots& check_slots);

  //
  void Use() { presentations_++; }

  //
  std::string name() { return name_; }

  //
  Slots slots() { return slots_; }

  //
  double creation_time() const { return creation_time_; }

  //
  int presentations() const { return presentations_; }

  //
  friend std::ostream& operator<<(std::ostream& stream, const Chunk& chunk) {
    stream << "[" << chunk.name_ << " presentations=" << chunk.presentations_
           << "]";

    return stream;
  }

 private:
  //
  std::string name_{"default-chunk"};

  //
  Slots slots_;

  //
  double creation_time_{0.0};

  //
  int presentations_{1};
};

}  // namespace wu::actr

#endif