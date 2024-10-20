#include "buffer.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

bool Buffer::Query(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots="
            << "]";

  return chunk_.has_value() && chunk_->SlotEquals(slots);
}

std::string Buffer::Clear() {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << "]";

  std::string name = chunk_.has_value() ? chunk_->name() : "nil";
  chunk_ = std::nullopt;
  failure_ = false;
  requested_ = false;
  return name;
}

std::string Buffer::Set(Chunk chunk, bool requested, bool clear) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name()
            << " chunk=" << chunk << " requested=" << requested
            << " clear=" << clear << "]";

  //
  if (clear) {
    Clear();
  }

  chunk_ = chunk;
  requested_ = requested;
  return chunk.name();
}

// std::string Buffer::Overwrite(Chunk chunk) { return Set(chunk, true, false);
// }

std::string Buffer::Modify(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots=]";

  return chunk_.has_value() ? chunk_->Modify(slots) : "nil";
}

bool Buffer::Request(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots=]";

  return module_->Request(slots);
}

}  // namespace wu::actr