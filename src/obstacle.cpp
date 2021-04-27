#include "../include/obstacle.h"

namespace geometrydash {

  //  Obstacle::Obstacle(const glm::vec2& position, const glm::vec2& velocity,
  //                     const cinder::geom::Source& shape, const ci::Color& color) {
  //    position_ = position;
  //    velocity_ = velocity;
  //    shape_ = shape;
  //    color_ = color;
  //  }

  Obstacle::Obstacle(const glm::vec2 &position, const glm::vec2 &velocity, const size_t height, const size_t width) {
    position_ = position;
    velocity_ = velocity;
    height_ = height;
    width_ = width;
  }

  glm::vec2 Obstacle::GetPosition() const {
    return position_;
  }
  glm::vec2 Obstacle::GetVelocity() const {
    return velocity_;
  }
  size_t Obstacle::GetHeight() const {
    return height_;
  }
  size_t Obstacle::GetWidth() const {
    return width_;
  }

  void Obstacle::SetPosition(const glm::vec2 &position) {
    position_ = position;
  }

  void Obstacle::SetVelocity(const glm::vec2 &velocity) {
    velocity_ = velocity;
  }

  //    cinder::geom::Source Obstacle::GetShape() const {
  //      return shape_;
  //    }
  //  ci::Color Obstacle::GetColor() const {
  //    return color_;
  //  }

}// namespace geometrydash