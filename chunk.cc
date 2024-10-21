#include "chunk.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

std::string Chunk::Modify(Slots &mod_slots) {
  LOG(INFO) << __FUNCTION__ << "[mod_slots=]";

  for (auto &slot : mod_slots.values()) {
    slots_.Modify(slot.first, slot.second);
  }

  return name();
}

bool Chunk::SlotEquals(Slots &check_slots) {
  LOG(INFO) << __FUNCTION__ << "[check_slots=]";

  bool match = true;

  for (auto &slot : check_slots.values()) {
    if (slots_.Contains(slot.first)) {
      match &= slots_.SlotEquals(slot.first, slot.second);
    }
  }

  LOG(INFO) << __FUNCTION__ << "[match=" << (match ? "true" : "false") << "]";
  return match;
}

}  // namespace wu::actr