#include "../include/obstacle.h"

namespace geometrydash {

  //  Obstacle::Obstacle(const glm::vec2& position, const glm::vec2& velocity,
  //                     const cinder::geom::Source& shape, const ci::Color& color) {
  //    position_ = position;
  //    velocity_ = velocity;
  //    shape_ = shape;
  //    color_ = color;
  //  }

  Obstacle::Obstacle(const glm::vec2 &position, const glm::vec2 &velocity) {
    position_ = position;
    velocity_ = velocity;
  }

  glm::vec2 Obstacle::GetPosition() const {
    return position_;
  }
  glm::vec2 Obstacle::GetVelocity() const {
    return velocity_;
  }
//    cinder::geom::Source Obstacle::GetShape() const {
//      return shape_;
//    }
  //  ci::Color Obstacle::GetColor() const {
  //    return color_;
  //  }

}// namespace geometrydash