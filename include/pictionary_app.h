#pragma once

#include <vector>
#include <chrono>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pictionary_canvas.h"

namespace pictionary {

class PictionaryApp : public ci::app::App {
 public:
  PictionaryApp();

  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const size_t kCanvasSize = 750;
  const size_t kWindowWidth = 1200;
  const size_t kWindowHeight = 900;
  const size_t kMargin = 100;

 private:
  ci::Color GetNextColor();

  const double kGameSeconds = 30.0;
  const double kTimeLow = 20.0;
  const double kTimeCritical = 10.0;
  const ci::Color kAppBackgroundColor = ci::Color::black();
  const std::vector<ci::Color> kPenColors = {
    ci::Color("black"),
    ci::Color("red"),
    ci::Color("green"),
    ci::Color("blue")
  };
  const ci::Font kUiFont = ci::Font("Arial", 28);

  size_t color_index_ = 0;
  Canvas canvas_;
  std::chrono::time_point<std::chrono::system_clock> start_time_;
  double time_remaining_;
  bool is_timer_enabled_ = false;
};
}  // namespace pictionary