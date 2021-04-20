#pragma once

#include "cinder/gl/gl.h"
#include "obstacle.h"
#include "player.h"

namespace geometrydash {

  /**
 * The frame in which all of the game happens in. This class
 * stores all of the obstacles and player and updates them on each frame of the simulation.
 */
  class GameEngine {
  public:
    /**
     * Constructor that takes in the boundaries of frame and initializes
     * frame.
     *
     * @param top_left_corner coordinates of top left corner of frame
     * @param bottom_right_corner coordinates of bottom right corner of frame
     */
    GameEngine(const glm::vec2 &top_left_corner, const glm::vec2 &bottom_right_corner);

    /**
     * Displays the frame walls and the current positions of the particles in game.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all obstacles and player.
     */
    void AdvanceOneFrame();

    /**
     * Method that generates a random number between the lower and upper input
     * bounds.
     *
     * @param lower_bound as a size_t
     * @param upper_bound as a size_t
     * @return randomly generated number as a size_t
     */
    size_t RandomNumberGenerator(size_t lower_bound, size_t upper_bound);

    /**
     * Method that generates a new obstacle to be added to game.
     */
    void GenerateObstacle();

    /**
     * Getter method to retrieve vector of obstacles in game.
     * @return vector of obstacles in game
     */
    std::vector<Obstacle> GetObstacles() const;

    void Jump();

  private:
    // game frame attributes
    const size_t kContainerBorderWidth = 5;// border width of container

    glm::vec2 top_left_coordinate_;    // top left corner of container
    glm::vec2 bottom_right_coordinate_;// bottom right corner of container

    const size_t kWindowLength = 1300;                // display window length
    const size_t kWindowWidth = 700;                  // display window width
    const size_t kPlayerWidth = 40;                   // player width
    const size_t kFrameMargin = 100;                  // frame margin
    const size_t kLinePosition = kWindowWidth / 3 * 2;// position of line
    const double kJumpFactor = -10.0; // factor that player jumps by

    const glm::vec2 starting_position_ = {kWindowLength / 5 + kPlayerWidth / 2,
                                          kLinePosition - kPlayerWidth / 2};// player starting position
    const glm::vec2 starting_velocity_ = glm::vec2{0, 0};               // player starting velocity

    Player player_ = Player(starting_position_, starting_velocity_);// instance of player

    size_t advancement_tracker_;// tracks number of advancement

    std::vector<Obstacle> obstacle_;// vector of obstacles in game
  };

}// namespace geometrydash
