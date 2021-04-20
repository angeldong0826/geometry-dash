#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(kWindowLength, kWindowWidth);
  }

  void GeometryDashApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
  }

  void GeometryDashApp::update() {
    AppBase::update();
  }

  void GeometryDashApp::keyDown(cinder::app::KeyEvent event) {
    AppBase::keyDown(event);
  }
  
}// namespace geometrydash
