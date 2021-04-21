#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(static_cast<int>(kWindowLength), static_cast<int>(kWindowLength));
  }

  void GeometryDashApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    
    game_frame_.Display();
  }

  void GeometryDashApp::update() {
    AppBase::update();

    game_frame_.AdvanceOneFrame();
  }

  void GeometryDashApp::keyDown(cinder::app::KeyEvent event) {

    if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE) {
      game_frame_.Jump();
    }
  }

}// namespace geometrydash