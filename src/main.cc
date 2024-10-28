#include <functional>
#include <iostream>
#include <map>
#include <string>
#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "actr/agent.h"
#include "actr/chunk.h"
#include "game/camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "raylib.h"
#include "raymath.h"

static wu::actr::Slots Slots(wu::actr::SlotsType slots) {
  return wu::actr::Slots(slots);
}

int main() {
  LOG(INFO) << __FUNCTION__ << "[Start]";

  // double delta_time_s = 1.0 / 60.0;
  // double delta_time = 0.25;
  // std::chrono::milliseconds sleep_duration_ms(100);

  //
  wu::actr::Agent agent;

  // `production-1`
  {
    wu::actr::Conditions conditions = {
        wu::actr::buffer::Query("goal", Slots({{"find", "thing"}}))};
    wu::actr::Actions actions = {
        wu::actr::retrieval::Start(Slots({{"type", "thing"}}))};
    agent.AddProcedure({"production-1", conditions, actions});
  }

  //// `production-2`
  //{
  //  wu::actr::Conditions conditions = {
  //      {"goal", wu::actr::buffer::Query({{"goal", "goal-2"}})}};
  //  wu::actr::Actions actions = {
  //      {"goal", wu::actr::buffer::Modify({{"goal", "goal-3"}})},
  //      {"retrieval", wu::actr::retrieval::Start({{"slot-1", "value-1"}})}};
  //  agent.AddProcedure({"production-2", conditions, actions});
  //}

  //// `production-3`
  //{
  //  wu::actr::Conditions conditions = {
  //      {"retrieval", wu::actr::buffer::Query({{"slot-1", "value-1"}})}};
  //  wu::actr::Actions actions = {
  //      {"goal", wu::actr::buffer::Modify({{"goal", "goal-3"}})},
  //      {"retrieval", wu::actr::buffer::Clear()}};
  //  agent.AddProcedure({"production-3", conditions, actions});
  //}

  //
  auto goal_slots(Slots({{"find", "thing"}}));
  agent.Focus({"goal-chunk", goal_slots, 0.0});

  //
  auto chunk_slots(Slots({{"type", "thing"}}));
  agent.Add({"thing-chunk", chunk_slots, 0.0});

  //
  // while (agent.Step(delta_time)) {
  //  std::this_thread::sleep_for(sleep_duration_ms);
  //}

  const int screen_width = 1920;
  const int screen_height = 1080;

  InitWindow(screen_width, screen_height, "Window");
  SetTargetFPS(60);
  // DisableCursor();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
  ImGui_ImplOpenGL3_Init();

  Camera3D camera;
  camera.position = {0.0f, 10.0f, 10.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 90.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  wu::game::camera::Orbit orbit;

  Vector3 thingPosition = {0.0f, 0.0f, 0.0f};
  Vector3 agentPosition = {5.0f, 0.0f, 0.0f};

  wu::actr::agent::Ui agent_ui;
  const float time_step = 1.0f;

  double current_frame_time = GetTime();
  double previous_frame_time = current_frame_time;
  double accumulator = 0.0f;

  while (!WindowShouldClose()) {
    current_frame_time = GetTime();
    double delta_time = current_frame_time - previous_frame_time;
    previous_frame_time = current_frame_time;
    accumulator += delta_time;

    Vector2 mouse_delta = GetMouseDelta();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //
    agent_ui.Show(agent);

    //
    while (accumulator >= time_step) {
      // agent.Step(time_step);
      accumulator -= time_step;
    }

    //
    // UpdateCamera(&camera, CAMERA_CUSTOM);
    orbit.Update(camera, mouse_delta.x, mouse_delta.y);

    //
    Vector3 direction =
        Vector3Normalize(Vector3Subtract(thingPosition, agentPosition));
    Ray ray = {agentPosition, direction};

    //
    RayCollision collision = GetRayCollisionSphere(ray, thingPosition, 0.5f);
    if (collision.hit) {
    }

    //
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
      {
        DrawSphere(thingPosition, 0.5f, RED);
        DrawSphere(agentPosition, 0.5f, BLUE);

        // DrawRay(ray, RED);
        if (collision.hit) {
          DrawLine3D(agentPosition, collision.point, RED);
        }

        DrawGrid(10, 1.0f);
      }
      EndMode3D();

      DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);
      DrawFPS(10, 10);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    EndDrawing();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  CloseWindow();

  LOG(INFO) << __FUNCTION__ << "[Exit]";
  return 0;
}