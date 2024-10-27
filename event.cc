#include "event.h"

#include "imgui.h"

namespace wu::actr::event {

void Ui::Show(const Queue& queue) {
  //
  if (ImGui::CollapsingHeader("Event Queue")) {
    //
    QueueType temp_queue = queue.queue();

    //
    ImGui::Text("Size: %i", temp_queue.size());

    //
    if (ImGui::BeginTable("Events", 5)) {
      ImGui::TableSetupColumn("Position");
      ImGui::TableSetupColumn("Buffer");
      ImGui::TableSetupColumn("Event");
      ImGui::TableSetupColumn("Time");
      ImGui::TableSetupColumn("Priority");
      ImGui::TableHeadersRow();

      int index = 0;
      while (!temp_queue.empty()) {
        ShowEvent(temp_queue.top(), ++index);
        temp_queue.pop();
      }

      ImGui::EndTable();
    }
  }
}

void Ui::ShowEvent(const Event& event, int index) {
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  ImGui::Text("%i", index);
  ImGui::TableNextColumn();
  ImGui::Text(event.buffer().c_str());
  ImGui::TableNextColumn();
  ImGui::Text(event.name().c_str());
  ImGui::TableNextColumn();
  ImGui::Text("%f", event.time());
  ImGui::TableNextColumn();
  ImGui::Text("%i", event.priority());
}

}  // namespace wu::actr::event