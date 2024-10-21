#include "metaprocess.h"

namespace wu::actr {

bool Process::Run(double delta_time) {
  LOG(INFO) << __FUNCTION__ << " ---------------- [Start step=" << step_
            << " delta_time=" << delta_time << " time_=" << time_
            << "] ----------------";

  //
  for (Module *module : modules_) {
    module->time(time_);
  }

  //
  if (event_queue_->Empty()) {
    LOG(INFO)
        << __FUNCTION__
        << " ---------------- [No events remaining; exiting] ----------------";
    return false;
  }

  LOG(INFO) << __FUNCTION__ << "[" << event_queue_->Size()
            << " event(s) in queue]";

  auto start = std::chrono::high_resolution_clock::now();

  //
  while (event_queue_->Size() > 0) {
    //
    Event event = event_queue_->Next();

    //
    double time_diff = event.time() - time_;

    //
    if (event.time() <= 0.0 || event.time() < time_ || time_diff < 0.001) {
      LOG(INFO) << __FUNCTION__ << "[event=" << event << "]";

      //
      event_queue_->Pop();

      //
      event.Exec();
    } else {
      LOG(INFO) << __FUNCTION__ << "[Next event in " << time_diff << "]";

      break;
    }
  }

  auto finish = std::chrono::high_resolution_clock::now();
  auto elapsed_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
          .count();
  LOG(INFO) << __FUNCTION__
            << " ---------------- [Finish elapsed_time=" << elapsed_time
            << "] ----------------";

  time_ += delta_time;
  step_++;
  return true;
}

}  // namespace wu::actr