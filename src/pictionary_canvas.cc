#include "pictionary_canvas.h"

namespace pictionary {

using glm::vec2;
using ci::Color;

Canvas::Canvas(const glm::vec2 &top_left_corner,
               size_t pixels_x,
               size_t pixels_y,
               const Color &stroke_color,
               float brush_radius)
  : top_left_corner_(top_left_corner),
    pixels_x_(pixels_x),
    pixels_y_(pixels_y),
    stroke_color_(stroke_color),
    brush_radius_(brush_radius) {}

void Canvas::Render() const {
  // Render the drawing box
  ci::gl::color(kCanvasColor);
  ci::gl::drawSolidRect(ci::Rectf(top_left_corner_, top_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));

  ci::gl::color(stroke_color_);

  if (!strokes_.empty()) {
    for (const std::vector<vec2> &stroke : strokes_) {
      ci::gl::begin(GL_LINE_STRIP);
      ci::gl::lineWidth(5.0);
      for (const vec2 &point : stroke) {
        ci::gl::vertex(point);
      }
      ci::gl::end();
    }
  }
}

void Canvas::CreateStroke() {
  strokes_.emplace_back();
}

void Canvas::ApplyStroke(const glm::vec2 &brush_screen_coords) {
  if (brush_screen_coords.x >= top_left_corner_.x && brush_screen_coords.x <= top_left_corner_.x + pixels_x_
    && brush_screen_coords.y >= top_left_corner_.y && brush_screen_coords.y <= top_left_corner_.y + pixels_y_) {
    strokes_.back().push_back(brush_screen_coords);
  }
}

void Canvas::ChangeColor(const cinder::Color &color) {
  stroke_color_ = color;
}

void Canvas::Clear() {
  strokes_.clear();
}

}  // namespace pictionary