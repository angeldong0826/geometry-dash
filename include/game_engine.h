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
     * Constructor to initiate game with player and obstacles.
     * 
     * @param player 
     * @param obstacles 
     */
    GameEngine(Player &player, std::vector<Obstacle> &obstacles);

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
     * Method that generates new obstacles to be added to part one of game.
     */
    void GenerateModeOneObstacles();

    /**
     * Method that generates new obstacles to be added to part two of game. 
     */
    void GenerateModeTwoObstacles();

    /**
     * Method that executes on player when jump key is pressed in mode 1 of game.
     */
    void ModeOneJump();

    /**
     * Method that updates obstacles.
     */
    void UpdateObstacle();

    /**
     * Method that updates player.
     */
    void UpdatePlayer();

    /**
     * Method that calculates max score.
     * 
     * @param current 
     */
    void CalculateMaxScore(size_t current);

    /**
     * Method that restarts the game.
     */
    void Restart();

    /**
     * Method that speeds up the game along the way it goes.
     */
    void Accelerate();

    /**
     * Methods that increments variables needed.
     */
    void Increment();

    /**
     * Game over menu.
     */
    void GameOverMenuDisplay() const;

    /**
     * Method to switch between game mode.
     */
    void SwitchMode();

    /**
     * Actions taken in mode one of advance one frame.
     */
    void ModeOneActions();

    /**
     * Actions taken in mode two of advance one frame.
     */
    void ModeTwoActions();

    /**
     * Method that contains all the displays in game.
     */
    void DisplayGame() const;

    // Getter method
    bool GetIsSecondMode() const;
    std::vector<Obstacle> GetObstacle() const;

    // Setter method
    void SetIsMovingUp(bool state);

  private:
    // game frame attributes
    const size_t kFrameBorderWidth = 5;// border width of container
    const size_t kWindowLength = 1300; // display window length
    const size_t kWindowWidth = 700;   // display window width
    const size_t kFrameMargin = 100;   // frame margin

    const size_t kLinePosition = kWindowWidth / 3 * 2;// position of line
    const glm::vec2 kLineLeft = {kFrameMargin, kLinePosition};
    const glm::vec2 kLineRight = {kWindowLength - kFrameMargin, kLinePosition};

    // player attributes
    const size_t kPlayerWidth = 40;                                                                            // player width
    const glm::vec2 kPlayerVelocity = {0, 0};                                                                  // player starting velocity
    const double kPlayerJumpVelocity = -6.5;                                                                   // velocity that player jumps by
    const glm::vec2 kPlayerPosition = {kWindowLength / 5 + kPlayerWidth / 2, kLinePosition - kPlayerWidth / 2};// player position

    // obstacle attributes
    const size_t kModeOneObstacleSpawningFrequencyLowerBound = 70;                              // obstacle spawning frequency lower bound
    const size_t kModeOneObstacleSpawningFrequencyUpperBound = 140;                             // obstacle spawning frequency upper bound
    const glm::vec2 kModeOneObstacleSpawningPosition = {kWindowLength / 4 * 3.5, kLinePosition};// position to spawn obstacles at for part 1
    const size_t kModeOneObstacleHeightHigh = 130;                                              // obstacle height upper bound for part 1
    const size_t kModeOneObstacleHeightLow = 60;                                                // obstacle height lower bound for part 1
    const size_t kObstacleWidthLow = 30;                                                        // obstacle width lower bound
    const size_t kObstacleWidthHigh = 55;                                                       // obstacle width upper bound
    const double kObstacleAccelerationFactor = 1.2;                                             // obstacle acceleration factor
    const size_t kObstacleAccelerationDistance = 700;                                           // obstacle acceleration distance
    const glm::vec2 kOriginalObstacleVelocity = {-3.5, 0};                                      // velocity obstacles_ move at

    // score attributes
    const glm::vec2 kScoreDisplayPosition = {kWindowLength / 2, 50};
    const glm::vec2 kWarningDisplayPosition = {kWindowLength / 2, 650};
    const glm::vec2 kGameOverCenter = {925, 350};    // center of game frame
    const glm::vec2 kScoreDisplay = {925, 400};      // position for score display
    const glm::vec2 kMaxScoreDisplay = {925, 450};   // position for max score display
    const glm::vec2 kRestartTextDisplay = {925, 500};//restart message display position

    // for random spawning purposes
    const size_t kHigh = 9;
    const size_t kLow = 0;
    const size_t kFirstBound = 2;
    const size_t kSecondBound = 5;
    const size_t kThirdBound = 7;
    const size_t kThree = 3;

    // for mode 2 purposes
    const size_t kModeTwoSwitchDistance = 1000;                                                // distance to enter mode two
    const size_t kModeOneSwitchDistance = 2003;                                                // distance to enter mode one
    const glm::vec2 kModeTwoObstacleSpawningPosition = {kWindowLength / 4 * 3.5, kFrameMargin};// position to spawn obstacles at for part 2
    const size_t kModeTwoObstacleHeightHigh = 185;                                             // obstacle height upper bound for part 2
    const size_t kModeTwoObstacleHeightLow = 100;                                              // obstacle height lower bound for part 2
    const size_t kModeTwoObstacleSpawningFrequencyLowerBound = 40;                             // obstacle spawning frequency lower bound
    const size_t kModeTwoObstacleSpawningFrequencyUpperBound = 100;                            // obstacle spawning frequency upper bound
    const int kFlyFactor = 3;                                                                  // factor that player "flies" in in mode 2
    const size_t kModeTwoWarningDisplay = 750;                                                 // score that warning message starts displaying at
    const size_t kModeOneWarningDisplay = 1753;                                                // score that warning message starts displaying at
    bool is_mode_two_ = false;                                                                 // bool to determine if game is in mode 2
    bool is_moving_up_ = false;                                                                // bool to determine if player is moving up

    glm::vec2 player_position_ = {kWindowLength / 5 + kPlayerWidth / 2, kLinePosition - kPlayerWidth / 2};// player position
    glm::vec2 obstacle_velocity_ = {-3.5, 0};                                                             // velocity obstacles_ move at

    Player player_ = Player(player_position_, kPlayerVelocity);// instance of player
    PlayerManager player_manager_;                             // instance of player manager for calculation purpose
    std::vector<Obstacle> obstacles_;                          // vector of obstacles_ in game

    glm::vec2 top_left_coordinate_;    // top left corner of container
    glm::vec2 bottom_right_coordinate_;// bottom right corner of container

    size_t advancement_tracker_;// tracks number of advancement
    size_t score_ = 0;          // game score
    size_t record_ = 0;         // max game score
  };

}// namespace geometrydash
