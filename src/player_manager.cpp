#include "player_manager.h"

namespace geometrydash {

    bool PlayerManager::IsCollideWithTop(Player &player) const {
      if ((player.GetVelocity().y < 0) && (player.GetPosition().y <=
                                           static_cast<float>(kLinePosition -kJumpDistance))) {
        return true;// if collide
      }

      return false;// if not collide
    }

    bool PlayerManager::IsCollideWithFloor(Player &player) const {
      if ((player.GetVelocity().y > 0) && (player.GetPosition().y +
                                           static_cast<float>(kPlayerWidth) / 2 >=
                                           static_cast<float>(kLinePosition))) {
        return true;// if collide
      }

      return false;// if not collide
    }

    void PlayerManager::CalculatePostTopCollisionVelocity(Player &player) {
      // Separate out player's x and y velocities
      double x_velocity = player.GetVelocity().x;
      double y_velocity = player.GetVelocity().y;
      y_velocity *= -1;// flips/negates player velocity in y-direction

      player.SetVelocity(glm::vec2(x_velocity, y_velocity));
    }

    void PlayerManager::CalculatePostBottomCollisionVelocity(Player &player) {
      // Separate out player's x and y velocities
      double x_velocity = player.GetVelocity().x;
      double y_velocity = player.GetVelocity().y;
      y_velocity *= 0;// sets y-velocity to 0, doesn't bounce back when reach bottom

      player.SetVelocity(glm::vec2(x_velocity, y_velocity));// set new velocity
      SetIsValidJump(true);
    }

    void PlayerManager::CollidesWithBoundary(Player &player, std::vector<Obstacle> &obstacles) {
      if (IsCollideWithTop(player)) {// checks if collide on top
        CalculatePostTopCollisionVelocity(player);

      } else if (IsCollideWithFloor(player)) {// otherwise checks if collide on bottom
        CalculatePostBottomCollisionVelocity(player);
        
      } else if (IsCollideWithObstacleTop(player, obstacles)) { // otherwise checks if collide with obstacle top
        CalculatePostObstacleTopCollisionVelocity(player);
      }
    }

    void PlayerManager::IsModeOneGameOver(Player &player, std::vector<Obstacle> &obstacles) {
      for (Obstacle &obstacle : obstacles) {

        // if player crashes into any obstacle
        if (((player.GetPosition().x + static_cast<float>(kPlayerWidth) / 2) >=
             (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2)) &&
            
            ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) <=
             obstacle.GetPosition().y) &&
            
            ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) >
             obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight())) &&
            
            ((player.GetPosition().x - (static_cast<float>(kPlayerWidth) / 2)) <= 
             (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2))) {
          
          is_mode_one_over_ = true;
        }
      }
    }

    void PlayerManager::IsModeTwoGameOver(Player &player, std::vector<Obstacle> &obstacles) {
      // if player hasn't crashed into top or bottom frame
      if (!(((player.GetPosition().y - static_cast<float>(kPlayerWidth) / 2) <= static_cast<float>(kFrameMargin))
          || ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) >= static_cast<float>(kLinePosition)))) {
        
        for (Obstacle &obstacle : obstacles) {
          if (obstacle.GetShape() == "triangle1" || obstacle.GetShape() == "rectangle1") {
            // if player crashes into any obstacle
            if (((player.GetPosition().x + static_cast<float>(kPlayerWidth) / 2) >=
                 (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2)) &&

                ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) <=
                 obstacle.GetPosition().y) &&

                ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) >
                 obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight())) &&

                ((player.GetPosition().x - (static_cast<float>(kPlayerWidth) / 2)) <=
                 (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2))) {
              is_mode_two_over_ = true;
            }
            
          } else if (obstacle.GetShape() == "triangle2" || obstacle.GetShape() == "rectangle2") {
            
            if (((player.GetPosition().x + static_cast<float>(kPlayerWidth) / 2) >=
                 (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2)) &&

                ((player.GetPosition().x - (static_cast<float>(kPlayerWidth) / 2)) <=
                 (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2)) &&

                ((player.GetPosition().y - (static_cast<float>(kPlayerWidth) / 2)) <=
                 (obstacle.GetPosition().y + static_cast<float>(obstacle.GetHeight()))) &&

                ((player.GetPosition().y - (static_cast<float>(kPlayerWidth) / 2)) >= obstacle.GetPosition().y)) {
              is_mode_two_over_ = true;
            }
          }
        }
      } else {
        is_mode_two_over_ = true;
      }
    }

    bool PlayerManager::IsCollideWithObstacleTop(Player &player, std::vector<Obstacle> &obstacles) {

      for (Obstacle &obstacle : obstacles) {

        if (obstacle.GetShape() == "rectangle1") {
          if (
//            ((player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) <= 
//               (obstacle.GetPosition().y - static_cast<float>(obstacle.GetHeight()))) && 
              
              ((player.GetPosition().x + static_cast<float>(kPlayerWidth) / 2) >= 
               (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth()) / 2)) && 
              
              ((player.GetPosition().x - static_cast<float>(kPlayerWidth) / 2) <= 
               (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth()) / 2)) && 
              
              (player.GetPosition().y + static_cast<float>(kPlayerWidth) / 2) >= 
                (obstacle.GetPosition().y - static_cast<float>(static_cast<float>(obstacle.GetHeight()) + -kPlayerJumpVelocity))) {
            
            if ((player.GetPosition().x + static_cast<float>(kPlayerWidth)/2 >= 
                 (obstacle.GetPosition().x - static_cast<float>(obstacle.GetWidth())/2 + obstacle.GetVelocity().x))
                && (player.GetPosition().x - static_cast<float>(kPlayerWidth)/2 <= 
                    (obstacle.GetPosition().x + static_cast<float>(obstacle.GetWidth())/2 + obstacle.GetVelocity().x))) {
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
      
      if (is_on_obstacle_top_) {// if on obstacle top
        y_velocity *= 0;        // sets y-velocity to 0, doesn't bounce back when reach bottom
        is_on_obstacle_top_ = false;
        
      } else {// if no longer on obstacle top
        y_velocity = -kPlayerJumpVelocity;
      }

      player.SetVelocity(glm::vec2(x_velocity, y_velocity));// set new velocity
      SetIsValidJump(true);
    }

    bool PlayerManager::GetIsModeOneOver() const {
      return is_mode_one_over_;
    }

    bool PlayerManager::GetIsValidJump() const {
      return is_valid_jump_;
    }

    void PlayerManager::SetIsValidJump(bool state) {
      is_valid_jump_ = state;
    }
    bool PlayerManager::GetIsModeTwoOver() const {
      return is_mode_two_over_;
    }
    
    void PlayerManager::SetIsModeOneOver(bool state) {
      is_mode_one_over_ = state;
    }
    
    void PlayerManager::SetIsModeTwoOver(bool state) {
      is_mode_two_over_ = state;
    }

}// namespace geometrydash