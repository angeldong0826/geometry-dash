#include "player_manager.h"

namespace geometrydash {

  bool PlayerManager::IsCollideWithTop(Player &player) const {
    if ((player.GetVelocity().y < 0) && (player.GetPosition().y <= 
         static_cast<float>(kLinePosition) - static_cast<float>(kJumpDistance))) {
      return true; // if collide
    }

    return false; // if not collide
  }

  bool PlayerManager::IsCollideWithBottom(Player &player) const {
    if ((player.GetVelocity().y > 0) && (player.GetPosition().y + 
         static_cast<float>(kPlayerWidth) / 2 >= static_cast<float>(kLinePosition))) {
      return true; // if collide
    }

    return false; // if not collide
  }

  void PlayerManager::CalculatePostTopCollisionVelocity(Player &player) {
    // Separate out player's x and y velocities
    double x_velocity = player.GetVelocity().x;
    double y_velocity = player.GetVelocity().y;
    y_velocity *= -1; // flips/negates player velocity in y-direction

    player.SetVelocity(glm::vec2(x_velocity, y_velocity));
  }

  void PlayerManager::CalculatePostBottomCollisionVelocity(Player &player) {
    // Separate out player's x and y velocities
    double x_velocity = player.GetVelocity().x;
    double y_velocity = player.GetVelocity().y;
    y_velocity *= 0; // sets y-velocity to 0, doesn't bounce back when reach bottom

    player.SetVelocity(glm::vec2(x_velocity, y_velocity)); // set new velocity
    SetIsValidJump(true);
  }

  void PlayerManager::CollidesWithBoundary(Player &player, std::vector<Obstacle> &obstacles) {
    if (IsCollideWithTop(player)) { // checks if collide on top
      CalculatePostTopCollisionVelocity(player);

    } else if (IsCollideWithBottom(player)) { // otherwise checks if collide on bottom
      CalculatePostBottomCollisionVelocity(player);
    } else if (IsCollideWithObstacleTop(player, obstacles)) {
      CalculatePostObstacleTopCollisionVelocity(player);
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
  
      // if player crashes into any obstacle
      if (((player.GetPosition().x + static_cast<float>(kPlayerWidth)/2) >= (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth())/2))
                                     && ((player.GetPosition().y + static_cast<float>(kPlayerWidth)/2) <= obstacle.GetPosition().y) 
                                     && ((player.GetPosition().y + static_cast<float>(kPlayerWidth)/2) > obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight()))
                                     && (player.GetPosition().x <= (obstacle.GetPosition().x + static_cast<float>((static_cast<float>(kPlayerWidth)/2 + 
                                     static_cast<float>(obstacle.GetWidth())/2))))) {
        game_over_ = true;
      }
    }
  }
  
  bool PlayerManager::IsCollideWithObstacleTop(Player &player, std::vector<Obstacle> &obstacles) {

    for (Obstacle &obstacle : obstacles) {
      
      if (obstacle.GetShape() == "rectangle") {
        if (((player.GetPosition().y + static_cast<float>(kPlayerWidth)/2) <= (obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight())))
            && ((player.GetPosition().x + static_cast<float>(kPlayerWidth)/2) >= (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth())/2))
            && ((player.GetPosition().x - static_cast<float>(kPlayerWidth)/2) <= (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth())/2))
            && (player.GetPosition().y + static_cast<float>(kPlayerWidth)/2) >= (obstacle.GetPosition().y - static_cast<float>(static_cast<float>(obstacle.GetHeight()) 
                                                                                                          + static_cast<float>(kPlayerWidth)/2))){
          if ((player.GetPosition().x + static_cast<float>(kPlayerWidth)/2 >= (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth())/2 + obstacle.GetVelocity().x))
              && (player.GetPosition().x - static_cast<float>(kPlayerWidth)/2 <= (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth())/2 + obstacle.GetVelocity().x))) {
            is_on_obstacle_top_ = true;
          }
          return true;
        }
      }
    }
    
    return false;
  }
  
  void PlayerManager::CalculatePostObstacleTopCollisionVelocity(Player &player) {
      // Separate out player's x and y velocities  
    double x_velocity = player.GetVelocity().x;
    double y_velocity = player.GetVelocity().y;
    if (is_on_obstacle_top_) {  
      std::cout << "hi" << std::endl;
      y_velocity *= 0; // sets y-velocity to 0, doesn't bounce back when reach bottom
//      std::cout << is_on_obstacle_top_ << std::endl;
      is_on_obstacle_top_ = false;
    } else {
      std::cout << "hello" << std::endl;
      y_velocity = -kPlayerJumpVelocity;
    }
//    y_velocity *= 0; // sets y-velocity to 0, doesn't bounce back when reach bottom
//    std::cout << y_velocity << std::endl;
//    std::cout << is_on_obstacle_top_ << std::endl;

    player.SetVelocity(glm::vec2(x_velocity, y_velocity)); // set new velocity
    SetIsValidJump(true);
  }
  
  bool PlayerManager::GetIsGameOver() const {
    return game_over_;
  }
  bool PlayerManager::GetIsValidJump() const {
    return is_valid_jump_;
  }
  void PlayerManager::SetIsValidJump(bool state) {
    is_valid_jump_ = state;
  }
  
}// namespace geometrydash