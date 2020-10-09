#include "pictionary_app.h"

namespace pictionary {
PictionaryApp::PictionaryApp() : canvas_(glm::vec2(kMargin, kMargin), kCanvasSize, kCanvasSize, kPenColors.front()) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void PictionaryApp::draw() {
  // Clear the background
  ci::gl::clear(kAppBackgroundColor);

  // Draw the canvas
  canvas_.Render();

  // Draw the color indicator
  size_t right_margin_width = kWindowWidth - kCanvasSize - kMargin;
  size_t right_margin_start = kWindowWidth - right_margin_width;
  size_t color_bar_margin = static_cast<size_t>(right_margin_width * .1);
  size_t color_bar_height = 20;
  size_t color_bar_padding = 10;
  ci::vec2 color_bar_topleft(right_margin_start + color_bar_margin, 150);
  ci::vec2 color_bar_bottomright(kWindowWidth - color_bar_margin, color_bar_topleft.y + color_bar_height);
  ci::vec2 color_bar_padding_topleft = color_bar_topleft - ci::vec2(color_bar_padding, color_bar_padding);
  ci::vec2 color_bar_padding_bottom_right = color_bar_bottomright + ci::vec2(color_bar_padding, color_bar_padding);
  ci::gl::drawStringCentered("Current pen color:",
                             ci::vec2(kWindowWidth - right_margin_width / 2, 100),
                             ci::Color("white"),
                             kUiFont);
  ci::gl::color(ci::Color::white());
  ci::gl::drawSolidRect(ci::Rectf(color_bar_padding_topleft, color_bar_padding_bottom_right));
  ci::gl::color(kPenColors[color_index_]);
  ci::gl::drawSolidRect(ci::Rectf(color_bar_topleft, color_bar_bottomright));

  // Draw the color instructions
  ci::gl::drawStringCentered("[ TAB ] to change colors",
                             ci::vec2(kWindowWidth - right_margin_width / 2, 200),
                             ci::Color("white"),
                             kUiFont);

  // Draw the clear instructions
  ci::gl::drawStringCentered("[ <-- ] to clear canvas",
                             ci::vec2(kWindowWidth - right_margin_width / 2, 250),
                             ci::Color("white"),
                             kUiFont);

  // Draw the timer instructions
  ci::gl::drawStringCentered("[ Space ] to start timer",
                             ci::vec2(kWindowWidth - right_margin_width / 2, 300),
                             ci::Color("white"),
                             kUiFont);

  if (is_timer_enabled_) {
    ci::Color text_color;
    if (time_remaining_ < 10) {
      text_color = ci::Color("red");
    } else if (time_remaining_ < 20) {
      text_color = ci::Color("yellow");
    } else {
      text_color = ci::Color("white");
    }
    // Draw the time left
    ci::gl::drawStringCentered(std::to_string(time_remaining_),
                               ci::vec2(kWindowWidth - right_margin_width / 2, 400),
                               text_color,
                               kUiFont);
  }
}

void PictionaryApp::update() {
  if (is_timer_enabled_) {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_time = now - start_time_;
    time_remaining_ = kGameSeconds - elapsed_time.count();

    if (time_remaining_ <= 0) {
      is_timer_enabled_ = false;
    }
  }
}

void PictionaryApp::mouseDown(ci::app::MouseEvent event) {
  canvas_.CreateStroke();
}

void PictionaryApp::mouseDrag(ci::app::MouseEvent event) {
  canvas_.ApplyStroke(event.getPos());
}

void PictionaryApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_TAB:
      // Change the color
      canvas_.ChangeColor(GetNextColor());
      break;
    case ci::app::KeyEvent::KEY_BACKSPACE:
      // Clear the canvas
      canvas_.Clear();
      break;
    case ci::app::KeyEvent::KEY_SPACE:
      // Start the timer
      start_time_ = std::chrono::system_clock::now();
      is_timer_enabled_ = true;
      break;
  }
}

ci::Color PictionaryApp::GetNextColor() {
  color_index_ = (color_index_ + 1) % kPenColors.size();
  return kPenColors[color_index_];
}

}  // namespace pictionary