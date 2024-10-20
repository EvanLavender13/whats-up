#include "chunk.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

std::string Chunk::Modify(Slots &mod_slots) {
  LOG(INFO) << __FUNCTION__ << "[mod_slots=]";

  for (auto &slot : mod_slots) {
    slots_[slot.first] = slot.second;
  }

  return name();
}

bool Chunk::SlotEquals(Slots &check_slots) {
  LOG(INFO) << __FUNCTION__ << "[check_slots=]";

  bool match = true;

  for (auto &slot : check_slots) {
    if (slots_.count(slot.first) == 1) {
      match &= slots_[slot.first] == slot.second;
    }
  }

  LOG(INFO) << __FUNCTION__ << "[match=" << (match ? "true" : "false") << "]";
  return match;
}

}  // namespace wu::actr