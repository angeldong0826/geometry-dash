#include "../include/game_engine.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>
#include "cinder/app/App.h"

namespace geometrydash {

  GameEngine::GameEngine(const glm::vec2 &top_left_coordinate,
                         const glm::vec2 &bottom_right_coordinate) {
    top_left_coordinate_ = top_left_coordinate;
    bottom_right_coordinate_ = bottom_right_coordinate;
  }

  void GameEngine::Display() const {
    if (!player_manager_.GetIsModeOneOver() && !player_manager_.GetIsModeTwoOver()) {// if game isn't over

      // Display game frame
      ci::gl::color(ci::Color("white"));
      ci::gl::drawStrokedRect(
              ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), static_cast<float>(kFrameBorderWidth));

      // Display player and line
      ci::gl::color(ci::Color("white"));
      ci::gl::drawLine(kLineLeft, kLineRight);

      glm::vec2 player_top_left_corner = {player_.GetPosition().x - static_cast<float>(kPlayerWidth) / 2,
                                          player_.GetPosition().y - static_cast<float>(kPlayerWidth) / 2};
      glm::vec2 player_bottom_right_corner = {player_.GetPosition().x + static_cast<float>(kPlayerWidth) / 2,
                                              player_.GetPosition().y + static_cast<float>(kPlayerWidth) / 2};
      
      ci::gl::drawSolidRect(ci::Rectf(player_top_left_corner, player_bottom_right_corner));

      // Display obstacle
      for (Obstacle obstacle : obstacles_) { // only display if obstacle is moving in frame
        
        if (obstacle.GetPosition().x >= static_cast<float>(kFrameMargin) + static_cast<float>(obstacle.GetWidth()) / 2) {
          obstacle.DrawObstacle();
        }
      }
      
      // Display score
      ci::gl::drawStringCentered("CURRENT SCORE: " + std::to_string(score_), kScoreDisplayPosition, "white",ci::Font("Helvetica", 20));
      
    } else if (player_manager_.GetIsModeOneOver() || player_manager_.GetIsModeTwoOver()) {// if game is over
      GameOverMenuDisplay();
    }
  }

  void GameEngine::AdvanceOneFrame() {
    if (!player_manager_.GetIsModeOneOver() && !player_manager_.GetIsModeTwoOver()) {// if game isn't over

      if (!is_mode_two_) { // if game is in mode 1
        if (advancement_tracker_ == RandomNumberGenerator(kModeOneObstacleSpawningFrequencyLowerBound, kModeOneObstacleSpawningFrequencyUpperBound) 
            || advancement_tracker_ > kModeOneObstacleSpawningFrequencyUpperBound) {

          GenerateModeOneObstacles();// generate obstacles at random time frames for first mode
        }

        UpdatePlayer();  // update player position
        UpdateObstacle();// update obstacle position
        
        player_manager_.CollidesWithBoundary(player_, obstacles_);// check if player collides with boundary that it can jump within
        player_manager_.IsModeOneGameOver(player_, obstacles_);          // check if mode 1 game is over
        
      } else { // if game is in mode 2
        if (advancement_tracker_ == RandomNumberGenerator(kModeTwoObstacleSpawningFrequencyLowerBound, kModeTwoObstacleSpawningFrequencyUpperBound) 
            || advancement_tracker_ > kModeTwoObstacleSpawningFrequencyUpperBound) {

          GenerateModeTwoObstacles();// generate obstacles at random time frames for second mode
        }

        UpdatePlayer();  // update player position
        UpdateObstacle();// update obstacle position
        
        player_manager_.IsModeTwoGameOver(player_, obstacles_); // check if mode 2 game is over
      }

      Increment(); // increments score and tracker
      Accelerate(); // accelerates throughout game
      SwitchMode(); // switches game mode

    } else if (player_manager_.GetIsModeOneOver() || player_manager_.GetIsModeTwoOver()) {
      CalculateMaxScore(score_); // calculates maximum score when game is over
    }
  }

  void GameEngine::GenerateModeOneObstacles() {
    size_t rand = RandomNumberGenerator(kLow, kHigh);
    if (rand < kThree) {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "rectangle1");
    } else {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "triangle1");
    }
    
    advancement_tracker_ = 0;// reset tracker every time an obstacle is generated
  }

  void GameEngine::GenerateModeTwoObstacles() {
    size_t rand = RandomNumberGenerator(kLow, kHigh);
    
    if (rand < kFirstBound) {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "triangle1");
    } else if (rand >= kFirstBound && rand < kSecondBound) {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "rectangle1");
    } else if (rand >= kSecondBound && rand < kThirdBound) {
      obstacles_.emplace_back(kModeTwoObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeTwoObstacleHeightLow, kModeTwoObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "triangle2");
    } else {
      obstacles_.emplace_back(kModeTwoObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeTwoObstacleHeightLow, kModeTwoObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "rectangle2");
    }
    
    advancement_tracker_ = 0;// reset tracker every time an obstacle is generated
  }
  
  size_t GameEngine::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
    size_t random_number_ =
            (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

    return random_number_;
  }

  void GameEngine::ModeOneJump() {
    if (player_manager_.GetIsValidJump()) {
      player_.SetVelocity(glm::vec2{0, kPlayerJumpVelocity});
      player_manager_.SetIsValidJump(false);
    }
  }

  void GameEngine::UpdateObstacle() {
    for (auto &obstacle : obstacles_) {
      obstacle.SetPosition(obstacle.GetPosition() + obstacle.GetVelocity());
//      if (obstacle.GetPosition().x < static_cast<float>(kFrameMargin)) {
//        obstacles_.erase(obstacles_.begin());
//      }
    }
  }

  void GameEngine::UpdatePlayer() {
    if (is_mode_two_) { // if in mode 2
      if (is_moving_up_) {
        player_.SetVelocity(glm::vec2(0, -kFlyFactor));
      } else {
        player_.SetVelocity(glm::vec2(0, kFlyFactor));
      }
    }
    
    player_.SetPosition(player_.GetPosition() + player_.GetVelocity()); // set position no matter what mode
  }
  
  void GameEngine::CalculateMaxScore(size_t current) {
    if (current > record_) {
      record_ = current;
    }
  }
  
  void GameEngine::Restart() {
    score_ = 0;
    advancement_tracker_ = 0;
    is_mode_two_ = false;
    obstacles_.clear();
    player_manager_.SetIsModeOneOver(false);
    player_manager_.SetIsModeTwoOver(false);
    obstacle_velocity_ = kOriginalObstacleVelocity;
    player_position_ = kPlayerPosition;
  }
  
  void GameEngine::Accelerate() {
    if (score_ % kObstacleAccelerationDistance == 0) {
      obstacle_velocity_ = glm::vec2{kObstacleAccelerationFactor * obstacle_velocity_.x, 0};
    }
  }
  
  void GameEngine::Increment() {
    advancement_tracker_++;// increments advance one frame every time it is called
    score_++;// increments player score
  }
  
  void GameEngine::GameOverMenuDisplay() const {
    ci::gl::draw(ci::gl::Texture::create(loadImage(ci::app::loadAsset("skull.jpeg"))));
    ci::gl::drawStringCentered("GAME OVER. YA DEAD.", kCenter, "white", ci::Font("Helvetica", 24));
    ci::gl::drawStringCentered("SCORE: " + std::to_string(score_), kScoreDisplay, "white", ci::Font("Helvetica",20));
    ci::gl::drawStringCentered("RECORD: " + std::to_string(record_), kMaxScoreDisplay, "white", ci::Font("Helvetica",20));
    ci::gl::drawStringCentered("PRESS  ' r '  TO RESTART.", kRestartTextDisplay, "white", ci::Font("Helvetica", 22));
  }
  
  void GameEngine::SwitchMode() {
    if (score_ % kModeTwoDistance == 0) {
      is_mode_two_ = true;
    }
  }
  
  bool GameEngine::GetIsSecondMode() const{
    return is_mode_two_;
  }
  
  void GameEngine::SetIsMovingUp(bool state) {
    is_moving_up_ = state;
  }

}// namespace geometrydash