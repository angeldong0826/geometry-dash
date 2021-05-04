#include "../include/obstacle.h"

namespace geometrydash {

  Obstacle::Obstacle(const glm::vec2 &position, const glm::vec2 &velocity, const size_t height, const size_t width, std::string shape) {
    position_ = position;
    velocity_ = velocity;
    height_ = height;
    width_ = width;
    shape_ = shape;
  }

  void Obstacle::DrawObstacle() {
    if (shape_ == "rectangle1") {
      ci::gl::color(ci::Color("white"));
      ci::gl::drawStrokedRect(ci::Rectf(glm::vec2{position_.x - static_cast<float>(width_) / 2,
                                                  position_.y - static_cast<float>(height_)},
                                        glm::vec2{position_.x + static_cast<float>(width_) / 2,
                                                  position_.y}),static_cast<float>(kObstacleBorderWidth));
    } else if (shape_ == "triangle1") {
      ci::gl::color(ci::Color("teal"));
      ci::gl::drawSolidTriangle(glm::vec2{position_.x - static_cast<float>(width_) / 2, position_.y}, 
                                glm::vec2{position_.x + static_cast<float>(width_) / 2, position_.y},
                                glm::vec2{position_.x, position_.y - static_cast<float>(height_)});
      } else if (shape_ == "rectangle2") {
        ci::gl::color(ci::Color("teal"));
        ci::gl::drawStrokedRect(ci::Rectf(glm::vec2{position_.x - static_cast<float>(width_) / 2, position_.y},
                                          glm::vec2{position_.x + static_cast<float>(width_) / 2, position_.y + static_cast<float>(height_)}), 
                                static_cast<float>(kObstacleBorderWidth));
      } else if (shape_ == "triangle2") {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidTriangle(glm::vec2{position_.x - static_cast<float>(width_) / 2, position_.y},
                                glm::vec2{position_.x + static_cast<float>(width_) / 2, position_.y},
                                  glm::vec2{position_.x, position_.y + static_cast<float>(height_)});
      }
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
  std::string Obstacle::GetShape() const {
    return shape_;
  }
  void Obstacle::SetPosition(const glm::vec2 &position) {
    position_ = position;
  }
  
}// namespace geometrydash