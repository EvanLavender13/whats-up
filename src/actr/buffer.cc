#include "actr/buffer.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

bool Buffer::Query(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << " slots="
            << "]";

  return chunk_.has_value() && chunk_->SlotEquals(slots);
}

void Buffer::Clear() {
  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << "]";

  if (chunk_.has_value() && clear_listener_.has_value()) {
    (*clear_listener_)->OnBufferClear(chunk_->name());
  }

  chunk_ = std::nullopt;
  failure_ = false;
  requested_ = false;
}

void Buffer::Set(Chunk chunk, bool requested, bool clear) {
  //
  if (clear) {
    Clear();
  }

  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << " chunk=" << chunk
            << " requested=" << requested << " clear=" << clear << "]";

  chunk_ = chunk;
  requested_ = requested;
}

void Buffer::Overwrite(Chunk chunk, bool requested) {
  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << " chunk=" << chunk << "]";

  Set(chunk, requested, false);
}

void Buffer::Modify(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << " slots=]";

  if (chunk_.has_value()) {
    chunk_->Modify(slots);
  }
}

void Buffer::Request(Slots slots) {
  LOG(INFO) << __FUNCTION__ << "[name=" << name_ << " slots=]";

  //
  module_->Request(slots);

  //
  Clear();
}

}  // namespace wu::actr