#include "player_manager.h"

namespace geometrydash {
  PlayerManager::PlayerManager(const glm::vec2 &top_left_coordinate,
                               const glm::vec2 &bottom_right_coordinate) {
    top_left_coordinate_ = top_left_coordinate;
    bottom_right_coordinate_ = bottom_right_coordinate;
  }

  bool PlayerManager::IsCollideWithTop(Player &player) const {
    // if player collides with top or bottom boundary
    if ((player.GetVelocity().y < 0) && (player.GetPosition().y <= static_cast<float>(kLinePosition) - static_cast<float>(kJumpDistance))) {
      return true;
    }

    return false;
  }


  bool PlayerManager::IsCollideWithBottom(Player &player) const {
    if ((player.GetVelocity().y > 0) && (player.GetPosition().y + static_cast<float>(kPlayerWidth)/2 >= static_cast<float>(kLinePosition))) {
      return true;
    }

    return false;
  }

  void PlayerManager::CalculatePostTopCollisionVelocity(Player &player) {
    // Separate out player's x and y velocities
    double x_velocity = player.GetVelocity().x;

    double y_velocity = player.GetVelocity().y;
    y_velocity *= -1;

    player.SetVelocity(glm::vec2(x_velocity, y_velocity));
  }

  void PlayerManager::CalculatePostBottomCollisionVelocity(Player &player) {
    // Separate out player's x and y velocities
    double x_velocity = player.GetVelocity().x;

    double y_velocity = player.GetVelocity().y;
    y_velocity = 0;

    player.SetVelocity(glm::vec2(x_velocity, y_velocity));
  }

  void PlayerManager::CollidesWithBoundary(Player &player) {
    if (IsCollideWithTop(player)) {
      CalculatePostTopCollisionVelocity(player);
      
    } else if (IsCollideWithBottom(player)) {
      CalculatePostBottomCollisionVelocity(player);
    }
  }
}// namespace geometrydash