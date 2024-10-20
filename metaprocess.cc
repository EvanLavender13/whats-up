#include "metaprocess.h"

namespace wu::actr {

bool Process::Run(double delta_time) {
  LOG(INFO) << __FUNCTION__ << "[Start delta_time=" << delta_time
            << " time_=" << time_ << "]";

  auto start = std::chrono::high_resolution_clock::now();

  //
  if (event_queue_->empty()) {
    LOG(INFO) << __FUNCTION__ << "[No events remaining; exiting]";
    return false;
  }

  LOG(INFO) << __FUNCTION__ << "[" << event_queue_->size()
            << " event(s) in queue]";

  while (event_queue_->size() > 0) {
    //
    Event event = event_queue_->top();

    //
    double time_diff = event.time() - time_;

    //
    if (event.time() < 0.0 || time_diff < 0.001) {
      LOG(INFO) << __FUNCTION__ << "[event=" << event << "]";

      //
      event_queue_->pop();

      //
      event.Exec();
    } else {
      LOG(INFO) << __FUNCTION__ << "[No events to process; next in "
                << time_diff << "]";

      break;
    }
  }

  auto finish = std::chrono::high_resolution_clock::now();
  auto elapsed_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
          .count();
  LOG(INFO) << __FUNCTION__ << "[Finish elapsed_time=" << elapsed_time << "]";

  time_ += delta_time;
  return true;
}

}  // namespace wu::actr