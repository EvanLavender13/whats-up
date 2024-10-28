#include "game/camera.h"

#include <iostream>

namespace wu::game::camera {

void Orbit::Update(Camera3D& camera, float mouse_dx, float mouse_dy) {
  longitude_degrees_ -= mouse_dx;

  if (longitude_degrees_ < 0.0f) {
    longitude_degrees_ += 360.0f;
  }

  if (longitude_degrees_ > 360.0f) {
    longitude_degrees_ -= 360.0f;
  }

  latitude_degrees_ = Clamp(-85.0f, 85.0f, latitude_degrees_ + mouse_dy);

  float latitude_radians = latitude_degrees_ * DEG2RAD;
  float longitude_radians = longitude_degrees_ * DEG2RAD;

  direction_.x = cos(latitude_radians) * sin(longitude_radians);
  direction_.y = sin(latitude_radians);
  direction_.z = cos(latitude_radians) * cos(longitude_radians);

  camera.position = Vector3Scale(direction_, 5.0f);
}

}  // namespace wu::game::camera