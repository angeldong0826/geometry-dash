#pragma once

#include "cinder/gl/gl.h"
#include "obstacle.h"

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
    GameEngine(const glm::vec2 &top_left_corner,
               const glm::vec2 &bottom_right_corner);

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

  private:
    // game frame attributes
    const size_t kContainerBorderWidth = 5;// border width of container

    //    const size_t kParticleAmount = 42;       // amount of particles in container

    //    // pink particles attributes
    //    const double kPinkMass = 5.0;         // pink particle mass
    //    const double kPinkRadius = 7.0;       // pink particle radius
    //    const ci::Color kPinkColor = "pink";  // pink particle color
    //    const glm::vec2 kPinkInitialVelocity = {
    //            6.0, 6.0};  // pink particle initial velocity
    //
    //    // teal particles attributes
    //    const double kTealMass = 20.0;        // teal particle mass
    //    const double kTealRadius = 20.0;      // teal particle radius
    //    const ci::Color kTealColor = "teal";  // teal particle color
    //    const glm::vec2 kTealInitialVelocity = {
    //            4.0, -4.0};  // teal particle initial velocity
    //
    //    // white particles attributes
    //    const double kWhiteMass = 30.0;         // white particle mass
    //    const double kWhiteRadius = 30.0;       // white particle radius
    //    const ci::Color kWhiteColor = "white";  // white particle color
    //    const glm::vec2 kWhiteInitialVelocity = {
    //            1.4, 1.4};  // white particle initial velocity

    glm::vec2 top_left_coordinate_;    // top left corner of container
    glm::vec2 bottom_right_coordinate_;// bottom right corner of container

    const size_t kWindowLength = 1300;// display window length
    const size_t kWindowWidth = 700;  // display window width

    size_t advancement_tracker_;// tracks number of advancement

    std::vector<Obstacle> obstacle_;// vector of obstacles in game
  };

}// namespace geometrydash
