#pragma once

#include "cinder/gl/gl.h"

namespace geometrydash {
  /**
   * Class that creates player to be used in simulation.
   */
  class Player {
  public:
    //    /**
    //     * Constructor that initializes player attributes.
    //     *
    //     * @param player position
    //     * @param player velocity
    //     * @param player shape
    //     * @param player color
    //     */
    //    Player(const glm::vec2& position, const glm::vec2& velocity, const cinder::geom::Source& shape, const ci::Color& color);

    /**
     * Constructor that initializes player attributes.
     * 
     * @param player position 
     * @param player velocity 
     */
    Player(const glm::vec2 &position, const glm::vec2 &velocity);

    // Getter methods
    glm::vec2 GetPosition() const;
    glm::vec2 GetVelocity() const;
    //    cinder::geom::Source GetShape() const;
    //    ci::Color GetColor() const;

    // Setter methods
    void SetPosition(const glm::vec2 &position);
    void SetVelocity(const glm::vec2 &velocity);

  private:
    glm::vec2 position_;// player position
    glm::vec2 velocity_;// player velocity

    //    cinder::geom::Source shape_; // player shape
    //    ci::Color color_;   // player color
  };

}// namespace geometrydash