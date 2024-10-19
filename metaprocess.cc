#include "metaprocess.h"

namespace wu::actr {

bool Process::Run(double delta_time) {
  LOG(INFO) << "wu::actr::Process::Run[Start delta_time=" << delta_time
            << " time_=" << time_ << "]";

  auto start = std::chrono::high_resolution_clock::now();

  //
  if (event_queue_->empty()) {
    LOG(INFO) << "wu::actr::Process::Run[No events remaining; exiting]";
    return false;
  }

  LOG(INFO) << "wu::actr::Process::Run[" << event_queue_->size()
            << " event(s) in queue]";

  //
  Event event = event_queue_->top();

  //
  double time_diff = event.time() - time_;

  //
  if (time_diff < 0.001) {
    LOG(INFO) << "wu::actr::Process::Run[event=" << event << "]";

    //
    event_queue_->pop();

    //
    event.Exec();
  } else {
    LOG(INFO) << "wu::actr::Process::Run[No events to process; next in "
              << time_diff << "]";
  }

  auto finish = std::chrono::high_resolution_clock::now();
  auto elapsed_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
          .count();
  LOG(INFO) << "wu::actr::Process::Run[Finish elapsed_time=" << elapsed_time
            << "]";

  time_ += delta_time;
  return true;
}

}  // namespace wu::actr