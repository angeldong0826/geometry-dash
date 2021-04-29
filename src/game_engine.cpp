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
    if (!player_manager_.GetIsGameOver()) {// if game isn't over

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
      for (Obstacle obstacle : obstacles_) {
        // if obstacle is moving in frame
        if (obstacle.GetPosition().x >= static_cast<float>(kFrameMargin) + static_cast<float>(obstacle.GetWidth()) / 2) {
          obstacle.DrawObstacle();
        }
      }
      
      // Display score
      ci::gl::drawStringCentered("CURRENT SCORE: " + std::to_string(score_), kScoreDisplayPosition, "white",ci::Font("Helvetica", 20));
      
    } else if (player_manager_.GetIsGameOver()) {// if game is over
      ci::gl::draw(ci::gl::Texture::create(loadImage(ci::app::loadAsset("skull.jpeg"))));
      ci::gl::drawStringCentered("GAME OVER. YA DEAD.", center_, "white", ci::Font("Helvetica", 24));
      ci::gl::drawStringCentered("SCORE: " + std::to_string(score_), score_display_, "white", ci::Font("Helvetica",20));
      ci::gl::drawStringCentered("RECORD: " + std::to_string(record_), max_score_display_, "white", ci::Font("Helvetica",20));
      ci::gl::drawStringCentered("PRESS  ' r '  TO RESTART.", restart_text_display_, "white", ci::Font("Helvetica", 22));
    }
  }

  void GameEngine::AdvanceOneFrame() {
    if (!player_manager_.GetIsGameOver()) {// if game isn't over
      if (advancement_tracker_ == RandomNumberGenerator(kObstacleSpawningFrequencyLowerBound, kObstacleSpawningFrequencyUpperBound) || advancement_tracker_ > kObstacleSpawningFrequencyUpperBound) {
        GenerateObstacle();// generate obstacles_ at random time frames
      }
      
      UpdatePlayer();  // update player position
      UpdateObstacle();// update obstacle position

      player_manager_.CollidesWithBoundary(player_, obstacles_);// check if player collide with boundary that it can jump within
      
      player_manager_.IsGameOver(player_, obstacles_);// check if game is over

      advancement_tracker_++;// increments advance one frame every time it is called
      score_++;// increments player score
      
    } else if (player_manager_.GetIsGameOver()) {
      CalculateMaxScore(score_);
    }
  }

  void GameEngine::GenerateObstacle() {
    size_t rand = RandomNumberGenerator(low_, high_);
    if (rand < mid_) {
      obstacles_.emplace_back(kObstacleSpawningPosition, kObstacleVelocity,
                              RandomNumberGenerator(kObstacleHeightLow, kObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "rectangle");
    } else {
      obstacles_.emplace_back(kObstacleSpawningPosition, kObstacleVelocity,
                              RandomNumberGenerator(kObstacleHeightLow, kObstacleHeightHigh),
                              RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh), "triangle");
    }
    
    advancement_tracker_ = 0;// reset tracker every time an obstacle is generated
  }
  
  size_t GameEngine::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
    size_t random_number_ =
            (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

    return random_number_;
  }

  void GameEngine::Jump() {
    if (player_manager_.GetIsValidJump()) {
      player_.SetVelocity(glm::vec2{0, kPlayerJumpVelocity});
      player_manager_.SetIsValidJump(false);
    }
  }

  void GameEngine::UpdateObstacle() {
    for (auto &obstacle : obstacles_) {
      obstacle.SetPosition(obstacle.GetPosition() + obstacle.GetVelocity());
    }
  }

  void GameEngine::UpdatePlayer() {
    player_.SetPosition(player_.GetPosition() + player_.GetVelocity());
  }
  
  void GameEngine::CalculateMaxScore(size_t current) {
    if (current > record_) {
      record_ = current;
    }
  }
  
  void GameEngine::Restart() {
    score_ = 0;
    advancement_tracker_ = 0;
    obstacles_.clear();
    player_manager_.SetIsGameOver(false);
  }

}// namespace geometrydash