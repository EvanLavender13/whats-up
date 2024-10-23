#include "declarative.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

namespace wu::actr::declarative {

void Module::Retrieve(Slots &slots) {
  LOG(INFO) << __FUNCTION__ << "[slots=]";

  //
  state(module::kBusy);

  //
  std::map<double, Chunk> matches;

  //
  for (auto &[chunk_name, chunk] : chunks_) {
    if (chunk.SlotEquals(slots)) {
      //
      double activation = BaseLevelActivation(chunk);

      LOG(INFO) << __FUNCTION__ << "[activation=" << activation << "]";

      //
      if (activation > threshold_) {
        matches.emplace(activation, chunk);
      }
    }
  }

  if (!matches.empty()) {
    //
    auto &[activation, chunk] = *matches.begin();

    //
    double retrieval_time = latency_ * std::exp(-latency_exp_ * activation);

    LOG(INFO) << __FUNCTION__
              << "[Match found; retrieval_time=" << retrieval_time << "]";

    //
    double event_time = time_ + retrieval_time;

    //
    auto [buffer_name, name, action, priority] =
        buffer::Set("retrieval", chunk);

    //
    Event event(buffer_name, "retrieved-chunk", event_time, priority,
                [this, action]() {
                  //
                  action(&buffer_);

                  //
                  state(module::kFree);
                });

    //
    event_queue_->Add(event);

    //
    event_queue_->Signal("conflict-resolution", event_time);

  } else {
    LOG(INFO) << __FUNCTION__ << "[No matches found]";

    //
    state(module::kError);

    //
    buffer_.failure(true);
  }
}

void Module::Request(Slots &slots) {
  LOG(INFO) << __FUNCTION__ << "[slots=]";

  Retrieve(slots);
};

void Module::OnBufferClear(std::string chunk_name) {
  chunks_[chunk_name].Use();
  LOG(INFO) << __FUNCTION__ << "[chunk=" << chunks_[chunk_name] << "]";
}

double Module::BaseLevelActivation(Chunk &chunk) {
  return std::log(chunk.presentations() / (1.0 - decay_)) -
         decay_ * std::log(time_ - chunk.creation_time());
}

}  // namespace wu::actr::declarative