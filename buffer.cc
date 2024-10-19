#include "buffer.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr {

bool Buffer::Query(Slots slots) {
  LOG(INFO) << "wu::actr::Buffer::Query[name=" << name_ << " slots=["
            << "]]";

  return chunk_.has_value() && chunk_->SlotEquals(slots);
}

std::string Buffer::Clear() {
  LOG(INFO) << "wu::actr::Buffer::Clear[name=" << name_ << "]";

  std::string name = chunk_.has_value() ? chunk_->name() : "nil";
  chunk_ = std::nullopt;
  failure_ = false;
  requested_ = false;
  return name;
}

std::string Buffer::Set(Chunk chunk, bool requested) {
  LOG(INFO) << "wu::actr::Buffer::Set[name=" << name_ << " chunk=" << chunk
            << "]";
  Clear();

  chunk_ = chunk;
  requested_ = requested;
  return chunk.name();
}

std::string Buffer::Overwrite(Chunk chunk) { return chunk.name(); }

std::string Buffer::Modify(Slots slots) {
  LOG(INFO) << "wu::actr::Buffer::Modify[name=" << name_ << " slots=]";

  return chunk_.has_value() ? chunk_->Modify(slots) : "nil";
}

}  // namespace wu::actr