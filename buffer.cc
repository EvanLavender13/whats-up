#include "buffer.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

bool Buffer::Query(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots="
            << "]";

  return chunk_.has_value() && chunk_->SlotEquals(slots);
}

void Buffer::Clear() {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << "]";

  if (chunk_.has_value() && clear_listener_.has_value()) {
    (*clear_listener_)->OnClear(*chunk_);
  }

  chunk_ = std::nullopt;
  failure_ = false;
  requested_ = false;
}

void Buffer::Set(Chunk chunk, bool requested, bool clear) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name()
            << " chunk=" << chunk << " requested=" << requested
            << " clear=" << clear << "]";

  //
  if (clear) {
    Clear();
  }

  chunk_ = chunk;
  requested_ = requested;
}

void Buffer::Overwrite(Chunk chunk, bool requested) {
  LOG(INFO) << __FUNCTION__ << "[chunk=" << chunk << "]";

  Set(chunk, requested, false);
}

std::string Buffer::Modify(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots=]";

  return chunk_.has_value() ? chunk_->Modify(slots) : "nil";
}

void Buffer::Request(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[module=" << module_->name() << " slots=]";

  //
  module_->Request(slots);

  //
  Clear();
}

}  // namespace wu::actr