#pragma once

#include "cinder/gl/gl.h"
#include "obstacle.h"
#include "player.h"
#include "player_manager.h"

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
     * Method that executes on player when jump key is pressed.
     */
    void Jump();

    /**
     * Method that updates obstacles.
     */
    void UpdateObstacle();

    /**
     * Method that updates player.
     */
    void UpdatePlayer();

  private:
    // game frame attributes
    const size_t kFrameBorderWidth = 5;           // border width of container
    const size_t kWindowLength = 1300;                // display window length
    const size_t kWindowWidth = 700;                  // display window width
    const size_t kFrameMargin = 100;                  // frame margin
    const size_t kLinePosition = kWindowWidth / 3 * 2;// position of line

    // player attributes
    const size_t kPlayerWidth = 40;       // player width
    const double kPlayerJumpFactor = -7.0;// factor that player jumps by
    const glm::vec2 player_position_ = {kWindowLength / 5 + kPlayerWidth / 2,
                                        kLinePosition - kPlayerWidth / 2};// player starting position
    const glm::vec2 player_velocity_ = glm::vec2{0, 0};                   // player starting velocity

    // obstacle attributes
    const size_t kObstacleSpawningFrequencyLowerBound = 50;                              // obstacle spawning frequency lower bound
    const size_t kObstacleSpawningFrequencyUpperBound = 100;                             // obstacle spawning frequency upper bound
    const size_t kObstacleBorderWidth = 2;                                               // obstacle border width
    const glm::vec2 kObstacleSpawningPosition = {kWindowLength / 4 * 3.5, kLinePosition};// position to spawn obstacles at
    const glm::vec2 kObstacleVelocity = {-3, 0};                                         // velocity obstacles move at
    const size_t kObstacleHeightHigh = 130;                                              // obstacle height upper bound
    const size_t kObstacleHeightLow = 50;                                                // obstacle height lower bound
    const size_t kObstacleWidthLow = 30;                                                 // obstacle width lower bound
    const size_t kObstacleWidthHigh = 55;                                                // obstacle width upper bound

    const glm::vec2 center_ = {650, 350};// center of game
    
    Player players_ = Player(player_position_, player_velocity_);// instance of player
    PlayerManager player_manager_;                               // instance of player manager for calculation purpose
    std::vector<Obstacle> obstacles_;                            // vector of obstacles in game

    glm::vec2 top_left_coordinate_;    // top left corner of container
    glm::vec2 bottom_right_coordinate_;// bottom right corner of container

    size_t advancement_tracker_;// tracks number of advancement
  };

}// namespace geometrydash
