#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(static_cast<int>(kWindowLength), static_cast<int>(kWindowLength));
  }

  void GeometryDashApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    
    if (is_starting_page_) {
      ci::gl::drawStringCentered("WELCOME TO GEOMETRY DASH!", kCenter, "white", ci::Font("Helvetica", 24));
      ci::gl::drawStringCentered("(well a lamer version but yeah uhh hello hi welcome)", kParenthesisDisplay, "white", ci::Font("Helvetica", 17));
      ci::gl::drawStringCentered("PRESS 'SPACE' TO START GAME. GOOD LUCK.", kInstructionDisplay, "white", ci::Font("Helvetica", 20));
      
    } else {
      game_engine_.Display();
    }
  }

  void GeometryDashApp::update() {
    if (!is_starting_page_) {
      AppBase::update();
      
      game_engine_.AdvanceOneFrame();
    }
  }

  void GeometryDashApp::keyDown(cinder::app::KeyEvent event) {
    if (is_starting_page_) {
      if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE) {
        is_starting_page_ = false;
      }
      
    } else {
      if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE) {
        game_engine_.Jump();
      }
      if (event.getChar() == 'r') {
        game_engine_.Restart();
      }
    }
  }

}// namespace geometrydash