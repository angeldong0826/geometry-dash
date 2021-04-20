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
     */
    Obstacle(const glm::vec2 &position, const glm::vec2 &velocity);

    // Getter methods
    glm::vec2 GetPosition() const;
    glm::vec2 GetVelocity() const;
//    cinder::geom::Source GetShape() const;
//    ci::Color GetColor() const;

  private:
    glm::vec2 position_;// position of obstacle
    glm::vec2 velocity_;// velocity of obstacle
//    cinder::geom::Source shape_;// shape of obstacle
//    ci::Color color_;   // color of obstacle
  };

}// namespace geometrydash