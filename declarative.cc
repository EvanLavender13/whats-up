#include "declarative.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr::declarative {

bool Module::Retrieve(Slots &slots) {
  LOG(INFO) << __FUNCTION__ << "[slots=]";

  //
  std::vector<Chunk> matches;

  //
  for (auto &[chunk_name, chunk] : chunks_) {
    if (chunk.SlotEquals(slots)) {
      matches.emplace_back(chunk);
    }
  }

  return !matches.empty();
}

//
bool Module::Request(Slots &slots) {
  LOG(INFO) << __FUNCTION__ << "[slots=]";

  return Retrieve(slots);
};

}  // namespace wu::actr::declarative