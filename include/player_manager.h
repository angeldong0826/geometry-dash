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
     * Method that determines whether or not player collides with top boundary.
     * 
     * @param player 
     * @param axis 
     * @return true if collided and false otherwise
     */
    bool IsCollideWithTop(Player &player) const;

    /**
     * Method that determines whether or not player collides with bottom boundary.
     * 
     * @param player 
     * @return 
     */
    bool IsCollideWithBottom(Player &player) const;

    /**
     * Method that calculates post top boundary collision velocity.
     * 
     * @param player 
     */
    void CalculatePostTopCollisionVelocity(Player &player);

    /**
     * Method that calculates post bottom boundary collision velocity.
     * 
     * @param player 
     */
    void CalculatePostBottomCollisionVelocity(Player &player);

    /**
     * Action taken after playing colliding with boundary.
     * 
     * @param player 
     */
    void CollidesWithBoundary(Player &player);

    /**
     * Method that determines whether player has collided with obstacle/lost the game.
     * 
     * @param player 
     * @return true if collided false otherwise
     */
    void IsGameOver(Player &player, std::vector<Obstacle> &obstacles);

    // Getter methods
    bool GetIsGameOver() const; 
    bool GetIsValidJump() const;
    
    //Setter methods
    void SetIsValidJump(bool state);

  private:
    const size_t kWindowWidth = 700;                  // display window width
    const size_t kLinePosition = kWindowWidth / 3 * 2;// position of line
    const size_t kJumpDistance = 260;                 // player vertical jump distance
    const size_t kPlayerWidth = 40;                   // player width

    bool game_over_ = false;// game status
    bool is_valid_jump_ = true; // to ensure single jumps
  };
}// namespace geometrydash