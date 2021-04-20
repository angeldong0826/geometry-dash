#pragma once

#include "obstacle.h"
#include "player.h"

namespace geometrydash {
  /**
   * Class that manages the player and its movements.
   */
  class PlayerManager {
  public:
    /**
     * Constructor that initializes game frame and takes in frame boundaries.
     * 
     * @param top_left_coordinate 
     * @param bottom_right_coordinate 
     */
    PlayerManager(const glm::vec2& top_left_coordinate,
                  const glm::vec2& bottom_right_coordinate);
    
    /**
     * Method that determines whether or not player collides with top boundary.
     * 
     * @param player 
     * @param axis 
     * @return true if collided and false otherwise
     */
    bool IsCollideWithTop(Player& player) const;
    
    /**
     * Method that determines whether or not player collides with bottom boundary.
     * 
     * @param player 
     * @return 
     */
    bool IsCollideWithBottom(Player& player) const;
    
    /**
     * Method that calculates post top boundary collision velocity.
     * 
     * @param player 
     */
    void CalculatePostTopCollisionVelocity(Player& player);
    
    /**
     * Method that calculates post bottom boundary collision velocity.
     * 
     * @param player 
     */
    void CalculatePostBottomCollisionVelocity(Player& player);
    
    /**
     * Action taken after playing colliding with boundary.
     * 
     * @param player 
     */
    void CollidesWithBoundary(Player& player);
    
  private:
    const size_t kWindowWidth = 700;                  // display window width
    const size_t kLinePosition = kWindowWidth / 3 * 2;// position of line
    const size_t kJumpDistance = 200; // player vertical jump distance
    const size_t kPlayerWidth = 40;                   // player width

    glm::vec2 top_left_coordinate_;      // top left corner of game frame
    glm::vec2 bottom_right_coordinate_;  // bottom right corner of game frame
  };
}