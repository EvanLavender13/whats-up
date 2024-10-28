#ifndef WHATS_UP_CAMERA_H_
#define WHATS_UP_CAMERA_H_

#include "raylib.h"
#include "raymath.h"

namespace wu::game::camera {

class Orbit {
 public:
  //
  void Update(Camera3D &camera, float mouse_dx, float mouse_dy);

 private:
  //
  float latitude_degrees_{0.0f};

  //
  float longitude_degrees_{0.0f};

  //
  Vector3 direction_;
};

}  // namespace wu::game::camera

#endif