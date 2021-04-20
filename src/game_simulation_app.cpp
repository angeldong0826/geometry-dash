#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(kWindowLength, kWindowWidth);
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
    
    if (event.getChar() == 'j') {
      game_frame_.Jump();
    }
  }
  
}// namespace geometrydash