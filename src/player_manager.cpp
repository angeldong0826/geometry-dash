#include "player_manager.h"

namespace geometrydash {

  bool PlayerManager::IsCollideWithTop(Player &player) const {
    if ((player.GetVelocity().y < 0) && (player.GetPosition().y <= 
         static_cast<float>(kLinePosition) - static_cast<float>(kJumpDistance))) {
      return true;
    }

    return false;
  }

  bool PlayerManager::IsCollideWithBottom(Player &player) const {
    if ((player.GetVelocity().y > 0) && (player.GetPosition().y + 
         static_cast<float>(kPlayerWidth) / 2 >= static_cast<float>(kLinePosition))) {
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
    y_velocity *= 0;

    player.SetVelocity(glm::vec2(x_velocity, y_velocity));
  }

  void PlayerManager::CollidesWithBoundary(Player &player) {
    if (IsCollideWithTop(player)) {
      CalculatePostTopCollisionVelocity(player);

    } else if (IsCollideWithBottom(player)) {
      CalculatePostBottomCollisionVelocity(player);
    }
  }

  void PlayerManager::IsGameOver(Player &player, std::vector<Obstacle> &obstacles) {

    for (Obstacle &obstacle : obstacles) {
//      if ((obstacle.GetPosition().x - (obstacle.GetWidth()/2 + kPlayerWidth/2)) <= player.GetPosition().x
//          && player.GetPosition().x <= (obstacle.GetPosition().x + (kPlayerWidth/2 + obstacle.GetWidth()/2))
//          && (kLinePosition + kPlayerWidth/2 - (obstacle.GetHeight())) <= player.GetPosition().y 
//          && player.GetPosition().y <= kLinePosition + kPlayerWidth/2) {
//        game_over_ = true;
//      }
  
      if (((player.GetPosition().x + static_cast<float>(kPlayerWidth) / 2) >= (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2))
                                     && ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) <= obstacle.GetPosition().y) 
                                     && (player.GetPosition().y > obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight()))
                                     && (player.GetPosition().x <= (obstacle.GetPosition().x + static_cast<float>((static_cast<float>(kPlayerWidth)/2 + 
                                     static_cast<float>(obstacle.GetWidth())/2))))) {
        game_over_ = true;
      }
    }
  }

  bool PlayerManager::GetIsGameOver() const {
    return game_over_;
  }

}// namespace geometrydash