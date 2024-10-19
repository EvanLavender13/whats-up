#include "chunk.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

std::string Chunk::Modify(Slots slots) { return name(); }

bool Chunk::SlotEquals(Slots check_slots) {
  bool equals = true;

  for (auto &slot : check_slots) {
    LOG(INFO) << "wu::actr::Chunk::SlotEquals[slot=[" << slot.first << ", "
              << slot.second << "]]";
    if (slots_.count(slot.first) == 1) {
      equals &= slots_[slot.first] == slot.second;
    }
  }

  return equals;
}

}  // namespace wu::actr