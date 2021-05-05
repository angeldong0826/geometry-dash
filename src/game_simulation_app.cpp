#include "../include/game_simulation_app.h"

namespace geometrydash {
  GeometryDashApp::GeometryDashApp() {
    ci::app::setWindowSize(static_cast<int>(kWindowLength), static_cast<int>(kWindowLength));
  }

  void GeometryDashApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    
    if (is_starting_page_ && is_instructions_page_) { // display instructions menu if on starting page and instructions page
      DisplayInstructionsPage();
      
    } else if (is_starting_page_) { // display start menu when only on starting page
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
        is_starting_page_ = false; // leaves starting page and enters game
        
      } else if (event.getChar() == 'i') { // press i key to view instructions
        is_instructions_page_ = true; // leaves starting page and enters instructions page

      } else if (event.getCode() == cinder::app::KeyEvent::KEY_ESCAPE) { // press escape key to leave instructions page
        is_instructions_page_ = false; // leaves instructions page and goes back to starting page
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
    ci::gl::drawStringCentered("PRESS 'SPACEBAR' TO START GAME. GOOD LUCK.", kSpaceToEnterDisplay, "white", ci::Font("Helvetica", 20));
    ci::gl::drawStringCentered("PRESS ' i ' to view game instructions.", kIForInstructions, "white", ci::Font("Helvetica", 18));
  }

  void GeometryDashApp::DisplayInstructionsPage() const {
    ci::gl::drawStringCentered("KEY COMMANDS:", kFirst, "white", ci::Font("Helvetica", 24));
    ci::gl::drawStringCentered("Original mode: ' spacebar ' to jump, ' r ' to restart game after death.", kSecond, "white", ci::Font("Helvetica", 17));
    ci::gl::drawStringCentered("Flappy bird mode: hold ' spacebar ' to fly up, release to fly down. ' r ' to restart.", kThird, "white", ci::Font("Helvetica", 17));
    ci::gl::drawStringCentered("Mac users - Command+Q to quit game. Windows users - Ctrl+Q to quit game.", kFourth, "white", ci::Font("Helvetica", 17));
    ci::gl::drawStringCentered("BASIC RULES:", kFifth, "white", ci::Font("Helvetica", 23));
    ci::gl::drawStringCentered("Original mode: you may jump only once per landing, yet you can land on rectangular obstacles.", kSixth, "white", ci::Font("Helvetica", 17));
    ci::gl::drawStringCentered("Flappy bird mode: avoid all obstacles as well as the top and bottom frames. or else you die.", kSeventh, "white", ci::Font("Helvetica", 17));
  }

}// namespace geometrydash