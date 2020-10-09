#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Color.h"

namespace pictionary {

class Canvas {
 public:
  Canvas(const glm::vec2& top_left_corner, size_t pixels_x, size_t pixels_y, ci::Color stroke_color, float brush_radius = 1.15);

  void Render() const;

  void CreateStroke();

  void ApplyStroke(const glm::vec2& brush_screen_coords);

  void ChangeColor(const cinder::Color& color);

  void Clear();

 private:
  const ci::Color kCanvasColor = ci::Color::white();

  glm::vec2 top_left_corner_;

  size_t pixels_x_;
  size_t pixels_y_;

  float brush_radius_;
  std::vector<std::vector<glm::vec2>> strokes_;
  ci::Color stroke_color_;
};
}  // namespace pictionary