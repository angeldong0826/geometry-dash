#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(static_cast<int>(kWindowLength), static_cast<int>(kWindowLength));
  }

  void GeometryDashApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    
    if (is_starting_page_) { // display starting menu if on starting page
      DisplayStartMenu();
      
    } else { // otherwise display actual game
      game_engine_.Display();
    }
  }

  void GeometryDashApp::update() {
    if (!is_starting_page_) { // only updates when not on starting page aka in game
      AppBase::update();
      game_engine_.AdvanceOneFrame();
    }
  }

  void GeometryDashApp::keyDown(cinder::app::KeyEvent event) {
    if (is_starting_page_) { // on starting page
      if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE) {
        is_starting_page_ = false; // leaves starting page and enter game
      }
      
    } else { // in game
      if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE) {
        
        if (!game_engine_.GetIsSecondMode()) { // if game is not in mode 2
          game_engine_.ModeOneJump(); // jump
          
        } else { // if game is in mode 2
          game_engine_.SetIsMovingUp(true); // moves player up
        }
      }
      
      if (event.getChar() == 'r') { // press key r to restart
        game_engine_.Restart();
        
      } else if (event.getChar() == 'i') { // press i key to view instructions
        game_engine_.SetInstructionsPage(true);
      }
    }
  }

  void GeometryDashApp::keyUp(cinder::app::KeyEvent event) {
    if (event.getCode() == cinder::app::KeyEvent::KEY_SPACE && game_engine_.GetIsSecondMode()) {
      game_engine_.SetIsMovingUp(false); // player falls down when spacekey is released
    }
  }
  
  void GeometryDashApp::DisplayStartMenu() const {
    ci::gl::drawStringCentered("WELCOME TO GEOMETRY DASH!", kCenter, "white", ci::Font("Helvetica", 24));
    ci::gl::drawStringCentered("(well a lamer version but yeah uhh hello hi welcome)", kParenthesisDisplay, "white", ci::Font("Helvetica", 17));
    ci::gl::drawStringCentered("PRESS 'SPACEBAR' TO START GAME. GOOD LUCK.", kInstructionDisplay, "white", ci::Font("Helvetica", 20));
  }

}// namespace geometrydash