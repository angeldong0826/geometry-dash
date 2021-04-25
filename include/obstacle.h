#pragma once

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>

namespace geometrydash {
  /**
   * Class that creates obstacles to be generated in game.
   */
  class Obstacle {
  public:
    //    /**
    //     * Constructor that initializes obstacle attributes.
    //     *
    //     * @param position of obstacle
    //     * @param velocity of obstacle
    //     * @param shape of obstacle
    //     * @param color of obstacle
    //     */
    //    Obstacle(const glm::vec2& position, const glm::vec2& velocity, const cinder::geom::Source& shape, const ci::Color& color);

    /**
     * Constructor that initializes obstacle attributes.
     * 
     * @param position of obstacle
     * @param velocity of obstacle
     * @param height of obstacle
     * @param width of obstacle
     */
    Obstacle(const glm::vec2 &position, const glm::vec2 &velocity, const size_t height, const size_t width, std::string shape);
    
    /**
     * Method that draws obstacles.
     */
    void DrawObstacle();

    // Getter methods
    glm::vec2 GetPosition() const;
    glm::vec2 GetVelocity() const;
    size_t GetHeight() const;
    size_t GetWidth() const;
    std::string GetShape() const;

    // Setter methods
    void SetPosition(const glm::vec2 &position);
    void SetVelocity(const glm::vec2 &velocity);

  private:
    // rectangular obstacle attributes
    const size_t kObstacleBorderWidth = 2;                                               // obstacle border width

    glm::vec2 position_;// position of obstacle
    glm::vec2 velocity_;// velocity of obstacle
    size_t height_;     // height of obstacle
    size_t width_;      // width of obstacle
    std::string shape_; // shape of obstacle
  };

}// namespace geometrydash