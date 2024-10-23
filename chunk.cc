#include "chunk.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

void Chunk::Modify(Slots &mod_slots) {
  LOG(INFO) << __FUNCTION__ << "[mod_slots=]";

  for (auto &[slot, value] : mod_slots.values()) {
    slots_.Modify(slot, value);
  }
}

bool Chunk::SlotEquals(Slots &check_slots) {
  LOG(INFO) << __FUNCTION__ << "[check_slots=]";

  bool match = true;

  for (auto &[slot, value] : check_slots.values()) {
    if (slots_.Contains(slot)) {
      match &= slots_.SlotEquals(slot, value);
    } else {
      match = false;
      break;
    }
  }

  LOG(INFO) << __FUNCTION__ << "[match=" << (match ? "true" : "false") << "]";
  return match;
}

}  // namespace wu::actr