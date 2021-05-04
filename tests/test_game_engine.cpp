#include <catch2/catch.hpp>
#include "game_engine.h"
#include "obstacle.h"
#include "player_manager.h"

namespace geometrydash {

  TEST_CASE("Mode One Game Over") {
    std::vector<Obstacle> obstacles;
    PlayerManager player_manager;
    
    //----------ONE OBSTACLE----------
    
    SECTION("Collide from left of obstacle stationary") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 330 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);
      
      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());
      
      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide from left of obstacle moving") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{-50,0}, 70, 60, "triangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of obstacle stationary") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 230 n edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of obstacle moving") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{75,0}, 70, 60, "triangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from left") {
      Player player(glm::vec2{180, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 100, "rectangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from right") {
      Player player(glm::vec2{220, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 100, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide right on top left corner") {
      Player player(glm::vec2{301, 451}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "rectangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide right on top right corner") {
      Player player(glm::vec2{359, 451}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding on top left corner") {
      Player player(glm::vec2{300, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "rectangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding on top right corner") {
      Player player(glm::vec2{400, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from left with approaching obstacle") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "rectangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from right with approaching obstacle") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{100,0}, 70, 60, "triangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{331, 500}, glm::vec2{0,0}, 70, 60, "rectangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{229, 500}, glm::vec2{0,0}, 70, 60, "triangle")); // 230 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }
    
    //----------MULTIPLE OBSTACLES----------

    SECTION("Collide from left of obstacle stationary in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 330 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{330, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 330 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide from left of second obstacle moving/jumped pass first(obstacles moving left)") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{-1,0}, 70, 60, "triangle")); // 330 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{-50,0}, 70, 60, "rectangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }


    SECTION("Collide/touch from right of obstacle stationary in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "triangle")); // 230 n edge case
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{0,0}, 70, 60, "rectangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of first obstacle moving/jumped pass second(obstacles moving right)") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{75,0}, 70, 60, "triangle"));
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{1,0}, 70, 60, "rectangle"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding in between moving obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "triangle"));
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{-1,0}, 70, 60, "rectangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from left with approaching obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "rectangle"));
      obstacles.push_back(Obstacle(glm::vec2{350, 500}, glm::vec2{-1,0}, 70, 60, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from right with approaching obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{50,0}, 70, 60, "rectangle"));
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{20,0}, 70, 60, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects with player in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{331, 500}, glm::vec2{0,0}, 70, 60, "rectangle"));
      obstacles.push_back(Obstacle(glm::vec2{220, 500}, glm::vec2{0,0}, 70, 60, "triangle"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{359, 500}, glm::vec2{0,0}, 70, 60, "triangle")); // 230 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{429, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 230 is an edge case

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 60, "rectangle")); // 230 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{0,0}, 70, 60, "triangle")); // 230 is an edge case

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }
  }

  TEST_CASE("Mode Two Game Over") {
    
  }

  TEST_CASE("Mode One Collision") {
    SECTION("Collide with top boundary") {
      
    }
    SECTION("Collide with bottom boundary") {
      
    }
    SECTION("Collide with obstacle top") {
      
    }
  }

  TEST_CASE("Mode Two Collision") {
    
  }

  TEST_CASE("Mode one jump") {
    
  }

  TEST_CASE("Mode two jump") {
    
  }
  
}