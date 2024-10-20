#include "goal.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "event.h"

namespace wu::actr::goal {

void Module::Focus(Chunk chunk) {
  LOG(INFO) << __FUNCTION__ << "[chunk=" << chunk << "]";

  Event event(name_, "goal-focus", 0.0, 100,
              [this, chunk]() { buffer_.Set(chunk); });

  event_queue_->Add(event);
}

}  // namespace wu::actr::goal