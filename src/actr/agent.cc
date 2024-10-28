#include "actr/agent.h"

#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "imgui.h"

namespace wu::actr::agent {

void Ui::Show(const Agent& agent) { process_ui_.Show(agent.process()); }

}  // namespace wu::actr::agent