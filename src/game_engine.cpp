#include "../include/game_engine.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

namespace geometrydash {

  GameEngine::GameEngine(const glm::vec2 &top_left_coordinate,
                         const glm::vec2 &bottom_right_coordinate) {
    top_left_coordinate_ = top_left_coordinate;
    bottom_right_coordinate_ = bottom_right_coordinate;

    GenerateObstacle();
  }

  void GameEngine::Display() const {
    // Display game frame
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(
            ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), static_cast<float>(kContainerBorderWidth));

    // Display obstacle, player, and line
    ci::Color("white");
    ci::gl::drawLine(glm::vec2{kFrameMargin, kLinePosition}, glm::vec2{kWindowLength - kFrameMargin, kLinePosition});
    ci::gl::drawSolidRect(ci::Rectf(glm::vec2{player_.GetPosition().x - static_cast<float>(kPlayerWidth) / 2,
                                              player_.GetPosition().y - static_cast<float>(kPlayerWidth) / 2},
                                      glm::vec2{player_.GetPosition().x + static_cast<float>(kPlayerWidth) / 2,
                                              player_.GetPosition().y + static_cast<float>(kPlayerWidth) / 2}));
  }

  void GameEngine::AdvanceOneFrame() {
    advancement_tracker_++;

    glm::vec2 position = player_.GetPosition();
    player_.SetPosition(position + player_.GetVelocity());
  }

  void GameEngine::GenerateObstacle() {
  }

  std::vector<Obstacle> GameEngine::GetObstacles() const {
    return obstacle_;
  }

  size_t GameEngine::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
    size_t random_number_ =
            (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

    return random_number_;
  }

  void GameEngine::Jump() {
    player_.SetVelocity(glm::vec2{0, kJumpFactor});
  }

}// namespace geometrydash