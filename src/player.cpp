#include "../include/player.h"

namespace geometrydash {

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

  void Player::SetPosition(const glm::vec2 &position) {
    position_ = position;
  }
  void Player::SetVelocity(const glm::vec2 &velocity) {
    velocity_ = velocity;
  }

}// namespace geometrydash
