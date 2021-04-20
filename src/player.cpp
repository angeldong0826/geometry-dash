#include "../include/player.h"

namespace geometrydash {

  //  Player::Player(const glm::vec2 &position, const glm::vec2 &velocity,
  //                 const cinder::geom::Source &shape, const cinder::Color &color) {
  //    position_ = position;
  //    velocity_ = velocity;
  //    shape_ = shape;
  //    color_ = color;
  //  }

  Player::Player(const glm::vec2 &position, const glm::vec2 &velocity) {
    position_ = position;
    velocity_ = velocity;
  }

  glm::vec2 Player::GetPosition() const {
    return position_;
  }
  glm::vec2 Player::GetVelocity() const {
    return velocity_;
  }
  
  void Player::SetPosition(glm::vec2 position) {
    position_ = position;
  }
  void Player::SetVelocity(glm::vec2 velocity) {
    velocity_ = velocity;
  }
  
  //  cinder::geom::Source Player::GetShape() const {
  //    return shape_;
  //  }
  //  ci::Color Player::GetColor() const {
  //    return color_;
  //  }

}// namespace geometrydash
