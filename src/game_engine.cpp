#include "../include/game_engine.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

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
      ci::Color("white");
      ci::gl::drawLine(glm::vec2{kFrameMargin, kLinePosition}, glm::vec2{kWindowLength - kFrameMargin, kLinePosition});

      ci::gl::drawSolidRect(ci::Rectf(glm::vec2{players_.GetPosition().x - static_cast<float>(kPlayerWidth) / 2,
                                                players_.GetPosition().y - static_cast<float>(kPlayerWidth) / 2},
                                      glm::vec2{players_.GetPosition().x + static_cast<float>(kPlayerWidth) / 2,
                                                players_.GetPosition().y + static_cast<float>(kPlayerWidth) / 2}));

      // Display obstacle
      ci::Color("white");
      for (const auto &obstacle : obstacles_) {
        // if obstacle is moving in frame
        if (obstacle.GetPosition().x >= static_cast<float>(kFrameMargin) + static_cast<float>(obstacle.GetWidth()) / 2) {
          ci::gl::drawStrokedRect(ci::Rectf(glm::vec2{obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2,
                                                      obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight())},
                                            glm::vec2{obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2,
                                                      obstacle.GetPosition().y}),
                                  static_cast<float>(kObstacleBorderWidth));
        }
      }
    } else if (player_manager_.GetIsGameOver()) {// if game is over
      ci::gl::drawStringCentered("GAME OVER. YA DEAD.", center_, "white", ci::Font("Helvetica", 24));
    }
  }

  void GameEngine::AdvanceOneFrame() {
    if (!player_manager_.GetIsGameOver()) {// if game isn't over
      if (advancement_tracker_ == RandomNumberGenerator(kObstacleSpawningFrequencyLowerBound, kObstacleSpawningFrequencyUpperBound) || advancement_tracker_ > kObstacleSpawningFrequencyUpperBound) {
        GenerateObstacle();// generate obstacles at random time frames
      }

      player_manager_.CollidesWithBoundary(players_);// check if player collide with boundary that it can jump within

      UpdatePlayer();  // update player position
      UpdateObstacle();// update obstacle position

      player_manager_.IsGameOver(players_, obstacles_);// check if game is over

      advancement_tracker_++;// increment advance one frame every time it is called
    }
  }

  void GameEngine::GenerateObstacle() {
    obstacles_.emplace_back(kObstacleSpawningPosition, kObstacleVelocity,
                            RandomNumberGenerator(kObstacleHeightLow, kObstacleHeightHigh),
                            RandomNumberGenerator(kObstacleWidthLow, kObstacleWidthHigh));
    advancement_tracker_ = 0;// reset tracker every time an obstacle is generated
  }

  size_t GameEngine::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
    size_t random_number_ =
            (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

    return random_number_;
  }

  void GameEngine::Jump() {
    players_.SetVelocity(glm::vec2{0, kPlayerJumpFactor});
  }

  void GameEngine::UpdateObstacle() {
    for (auto &obstacle : obstacles_) {
      obstacle.SetPosition(obstacle.GetPosition() + obstacle.GetVelocity());
    }
  }

  void GameEngine::UpdatePlayer() {
    players_.SetPosition(players_.GetPosition() + players_.GetVelocity());
  }

}// namespace geometrydash