#include "../include/game_engine.h"
#include "cinder/app/App.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

namespace geometrydash {

  GameEngine::GameEngine(const glm::vec2 &top_left_coordinate,
                         const glm::vec2 &bottom_right_coordinate) {
    top_left_coordinate_ = top_left_coordinate;
    bottom_right_coordinate_ = bottom_right_coordinate;
  }

  GameEngine::GameEngine(Player &player, std::vector<Obstacle> &obstacles) {
    player_ = player;
    obstacles_ = obstacles;
  }

  void GameEngine::Display() const {
    if (!player_manager_.GetIsModeOneOver() && !player_manager_.GetIsModeTwoOver()) {// if game isn't over
      DisplayGame();                                                                 // display game

    } else if (player_manager_.GetIsModeOneOver() || player_manager_.GetIsModeTwoOver()) {// if game is over
      GameOverMenuDisplay();                                                              // display game over menu
    }
  }

  void GameEngine::AdvanceOneFrame() {
    if (!player_manager_.GetIsModeOneOver() && !player_manager_.GetIsModeTwoOver()) {// if game isn't over

      if (!is_mode_two_) {// if game is in mode 1
        ModeOneActions();

      } else {// if game is in mode 2
        ModeTwoActions();
      }

      Increment(); // increments score and tracker
      Accelerate();// accelerates throughout game
      SwitchMode();// switches game mode

    } else if (player_manager_.GetIsModeOneOver() || player_manager_.GetIsModeTwoOver()) {// if game is over
      CalculateMaxScore(score_);                                                          // calculates maximum score
    }
  }

  void GameEngine::GenerateModeOneObstacles() {
    size_t rand = RandomNumberGenerator(kLow, kHigh);

    if (rand < kThree) {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "triangle1");
    } else {
      obstacles_.emplace_back(kModeOneObstacleSpawningPosition, obstacle_velocity_,
                              RandomNumberGenerator(kModeOneObstacleHeightLow, kModeOneObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "rectangle1");
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
      player_manager_.SetIsValidJump(false);// only allowed to jump once per jump
    }
  }

  void GameEngine::UpdateObstacle() {
    for (auto &obstacle : obstacles_) {
      obstacle.SetPosition(obstacle.GetPosition() + obstacle.GetVelocity());

//      I tried to erase obstacles from obstacles vector when they are out of frame
//      but the game became a bit glitchy and the obstacles would shift right a tiny bit
//      therefore I commented the erasing part out. See code below. (working code)

//      if (obstacle.GetPosition().x < static_cast<float>(kFrameMargin)) {
//        obstacles_.erase(obstacles_.begin());
//      }
    }
  }

  void GameEngine::UpdatePlayer() {
    if (is_mode_two_) {// if in mode 2
      if (is_moving_up_) {
        player_.SetVelocity(glm::vec2(0, -kFlyFactor));// player moves up

      } else {
        player_.SetVelocity(glm::vec2(0, kFlyFactor));// player moves down
      }
    }

    player_.SetPosition(player_.GetPosition() + player_.GetVelocity());// set player position regardless of mode
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
    player_.SetPosition(player_position_);
  }

  void GameEngine::Accelerate() {
    if (score_ % kObstacleAccelerationDistance == 0) {
      obstacle_velocity_ = glm::vec2{kObstacleAccelerationFactor * obstacle_velocity_.x, 0};
    }
  }

  void GameEngine::Increment() {
    advancement_tracker_++;// increments advance one frame every time it is called
    score_++;              // increments player score
  }

  void GameEngine::GameOverMenuDisplay() const {
    ci::gl::draw(ci::gl::Texture::create(loadImage(ci::app::loadAsset("skull.jpeg"))));
    ci::gl::drawStringCentered("GAME OVER. YA DEAD.", kGameOverCenter, "red", ci::Font("Helvetica", 24));
    ci::gl::drawStringCentered("SCORE: " + std::to_string(score_), kScoreDisplay, "white", ci::Font("Helvetica", 20));
    ci::gl::drawStringCentered("RECORD: " + std::to_string(record_), kMaxScoreDisplay, "white", ci::Font("Helvetica", 20));
    ci::gl::drawStringCentered("PRESS  ' r '  TO RESTART.", kRestartTextDisplay, "white", ci::Font("Helvetica", 22));
  }

  void GameEngine::SwitchMode() {
    if (score_ % kModeTwoSwitchDistance == 0) {
      is_mode_two_ = true;
    } else if (score_ % kModeOneSwitchDistance == 0) {
      is_mode_two_ = false;
    }
  }

  void GameEngine::ModeOneActions() {
    if (advancement_tracker_ == RandomNumberGenerator(kModeOneObstacleSpawningFrequencyLowerBound, kModeOneObstacleSpawningFrequencyUpperBound) 
        || advancement_tracker_ > kModeOneObstacleSpawningFrequencyUpperBound) {

      GenerateModeOneObstacles();// generate obstacles at random time frames for first mode
    }

    UpdatePlayer();  // update player position
    UpdateObstacle();// update obstacle position

    player_manager_.CollidesWithBoundary(player_, obstacles_);// check if player collides with boundary that it can jump within
    player_manager_.IsModeOneGameOver(player_, obstacles_);   // check if mode 1 game is over
  }

  void GameEngine::ModeTwoActions() {
    if (advancement_tracker_ == RandomNumberGenerator(kModeTwoObstacleSpawningFrequencyLowerBound, kModeTwoObstacleSpawningFrequencyUpperBound) 
        || advancement_tracker_ > kModeTwoObstacleSpawningFrequencyUpperBound) {

      GenerateModeTwoObstacles();// generate obstacles at random time frames for second mode
    }

    UpdatePlayer();  // update player position
    UpdateObstacle();// update obstacle position

    player_manager_.IsModeTwoGameOver(player_, obstacles_);// check if mode 2 game is over
  }

  bool GameEngine::GetIsSecondMode() const {
    return is_mode_two_;
  }

  void GameEngine::SetIsMovingUp(bool state) {
    is_moving_up_ = state;
  }

  void GameEngine::DisplayGame() const {
    // Display game frame
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(
      ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), static_cast<float>(kFrameBorderWidth));

    // Display line and player
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(kLineLeft, kLineRight);

    glm::vec2 player_top_left_corner = {player_.GetPosition().x - static_cast<float>(kPlayerWidth) / 2,
                                        player_.GetPosition().y - static_cast<float>(kPlayerWidth) / 2};
    glm::vec2 player_bottom_right_corner = {player_.GetPosition().x + static_cast<float>(kPlayerWidth) / 2,
                                            player_.GetPosition().y + static_cast<float>(kPlayerWidth) / 2};

    ci::gl::drawSolidRect(ci::Rectf(player_top_left_corner, player_bottom_right_corner));

    // Display obstacle
    for (Obstacle obstacle : obstacles_) {// only display if obstacle is moving in frame

      if (obstacle.GetPosition().x >= static_cast<float>(kFrameMargin) + static_cast<float>(obstacle.GetWidth()) / 2) {
        obstacle.DrawObstacle();
      }
    }

    // Display score
    ci::gl::drawStringCentered("CURRENT SCORE: " + std::to_string(score_), kScoreDisplayPosition, "white", ci::Font("Helvetica", 20));

    // Display warning message pre-mode switch
    if (score_ >= kModeTwoWarningDisplay && score_ < kModeTwoSwitchDistance) {
      ci::gl::drawStringCentered("!!Warning!! MODE CHANGE AT SCORE 1000 !!", kWarningDisplayPosition, "red", ci::Font("Helvetica", 20));
    } else if (score_ >= kModeOneWarningDisplay && score_ < kModeOneSwitchDistance) {
      ci::gl::drawStringCentered("!!Warning!! MODE CHANGE AT SCORE 2000 !!", kWarningDisplayPosition, "red", ci::Font("Helvetica", 20));
    }
  }

  std::vector<Obstacle> GameEngine::GetObstacle() const {
    return obstacles_;
  }
  
  Player GameEngine::GetPlayer() const {
    return player_;
  }
  
  void GameEngine::SetIsModeTwo(bool state) {
    is_mode_two_ = state;
  }
  
  size_t GameEngine::GetMaxScore() const {
    return record_;
  }
  
  size_t GameEngine::GetScore() const {
    return score_;
  }
  
  size_t GameEngine::GetAdvancementTracker() const {
    return advancement_tracker_;
  }
  
  glm::vec2 GameEngine::GetObstacleVelocity() const {
    return obstacle_velocity_;
  }
  
  void GameEngine::SetScore(size_t score) {
    score_ = score;
  }
  
  void GameEngine::SetAdvancementTracker(size_t tracker) {
    advancement_tracker_ = tracker;
  }

} // namespace geometrydash