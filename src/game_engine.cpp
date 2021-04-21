#include "../include/game_engine.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

namespace geometrydash {

  GameEngine::GameEngine(const glm::vec2 &top_left_coordinate,
                         const glm::vec2 &bottom_right_coordinate)
      : player_manager_(PlayerManager(top_left_coordinate, bottom_right_coordinate)) {
    top_left_coordinate_ = top_left_coordinate;
    bottom_right_coordinate_ = bottom_right_coordinate;
  }

  void GameEngine::Display() const {
    if (!player_manager_.GetIsGameOver()) {
      // Display game frame
      ci::gl::color(ci::Color("white"));
      ci::gl::drawStrokedRect(
              ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), static_cast<float>(kContainerBorderWidth));

      // Display player, and line
      ci::Color("white");
      ci::gl::drawLine(glm::vec2{kFrameMargin, kLinePosition}, glm::vec2{kWindowLength - kFrameMargin, kLinePosition});
      ci::gl::drawSolidRect(ci::Rectf(glm::vec2{players_.GetPosition().x - static_cast<float>(kPlayerWidth) / 2,
                                                players_.GetPosition().y - static_cast<float>(kPlayerWidth) / 2},
                                      glm::vec2{players_.GetPosition().x + static_cast<float>(kPlayerWidth) / 2,
                                                players_.GetPosition().y + static_cast<float>(kPlayerWidth) / 2}));

      // Display obstacle
      ci::Color("white");
      for (const auto &obstacle : obstacles_) {
        if (obstacle.GetPosition().x >= static_cast<float>(kFrameMargin) + static_cast<float>(kObstacleWidth) / 2) {
          ci::gl::drawStrokedRect(ci::Rectf(glm::vec2{obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2,
                                                      obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight())},
                                            glm::vec2{obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2,
                                                      obstacle.GetPosition().y}),
                                  static_cast<float>(kObstacleBorderWidth));
        }
      }
    } else if (player_manager_.GetIsGameOver()) {
      ci::gl::drawStringCentered("GAME OVER", center_);
    }
  }

  void GameEngine::AdvanceOneFrame() {
    if (!player_manager_.GetIsGameOver()) {
      if (advancement_tracker_ == RandomNumberGenerator(kObstacleSpawningFrequencyLowerBound, kObstacleSpawningFrequencyUpperBound) || advancement_tracker_ > kObstacleSpawningFrequencyUpperBound) {
        GenerateObstacle();
      }

      players_.SetPosition(players_.GetPosition() + players_.GetVelocity());
      player_manager_.CollidesWithBoundary(players_);

      for (auto &obstacle : obstacles_) {
        obstacle.SetPosition(obstacle.GetPosition() + obstacle.GetVelocity());
      }

      player_manager_.IsGameOver(players_, obstacles_);// check if game is over

      advancement_tracker_++;// increments advance one frame every time it is called
    }
  }

  void GameEngine::GenerateObstacle() {
    obstacles_.emplace_back(kObstacleSpawningPosition, kObstacleVelocity, kObstacleHeight, kObstacleWidth);
    advancement_tracker_ = 0;
  }

  std::vector<Obstacle> GameEngine::GetObstacles() const {
    return obstacles_;
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

}// namespace geometrydash