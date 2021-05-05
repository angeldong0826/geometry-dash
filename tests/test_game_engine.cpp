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
      obstacles.push_back(Obstacle(glm::vec2{330, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 330 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);
      
      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());
      
      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide from left of obstacle moving") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{-50,0}, 70, 60, "triangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of obstacle stationary") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 230 n edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of obstacle moving") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{75,0}, 70, 60, "triangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from left stationary") {
      Player player(glm::vec2{180, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 100, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from left moving") {
      Player player(glm::vec2{180, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{-1,0}, 70, 100, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from right stationary") {
      Player player(glm::vec2{220, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 100, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide in middle of obstacle from right moving") {
      Player player(glm::vec2{220, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{1,0}, 70, 100, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide right on top left corner") {
      Player player(glm::vec2{301, 451}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "rectangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide right on top right corner") {
      Player player(glm::vec2{359, 451}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding on top left corner") {
      Player player(glm::vec2{300, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding on top right corner") {
      Player player(glm::vec2{400, 450}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{350, 540}, glm::vec2{0,0}, 70, 60, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from left with approaching obstacle") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "rectangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from right with approaching obstacle") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{100,0}, 70, 60, "triangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{331, 500}, glm::vec2{0,0}, 70, 60, "rectangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{229, 500}, glm::vec2{0,0}, 70, 60, "triangle1")); // 230 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }
    
    //----------MULTIPLE OBSTACLES----------

    SECTION("Collide from left of obstacle stationary in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 330 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{330, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 330 is an edge case
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide from left of second obstacle moving/jumped pass first(obstacles moving left)") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{-1,0}, 70, 60, "triangle1")); // 330 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{-50,0}, 70, 60, "rectangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }


    SECTION("Collide/touch from right of obstacle stationary in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{0,0}, 70, 60, "triangle1")); // 230 n edge case
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{0,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Collide/touch from right of first obstacle moving/jumped pass second(obstacles moving right)") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{75,0}, 70, 60, "triangle1"));
      obstacles.push_back(Obstacle(glm::vec2{340, 500}, glm::vec2{1,0}, 70, 60, "rectangle1"));
      
      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding in between moving obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "triangle1"));
      obstacles.push_back(Obstacle(glm::vec2{230, 500}, glm::vec2{-1,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from left with approaching obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 500}, glm::vec2{-50,0}, 70, 60, "rectangle1"));
      obstacles.push_back(Obstacle(glm::vec2{350, 500}, glm::vec2{-1,0}, 70, 60, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding from right with approaching obstacles") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{50,0}, 70, 60, "rectangle1"));
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{20,0}, 70, 60, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects with player in between") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{331, 500}, glm::vec2{0,0}, 70, 60, "rectangle1"));
      obstacles.push_back(Obstacle(glm::vec2{220, 500}, glm::vec2{0,0}, 70, 60, "triangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{359, 500}, glm::vec2{0,0}, 70, 60, "triangle1")); // 230 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{429, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 230 is an edge case

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{280, 480}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{200, 500}, glm::vec2{0,0}, 70, 60, "rectangle1")); // 230 is an edge case
      obstacles.push_back(Obstacle(glm::vec2{100, 500}, glm::vec2{0,0}, 70, 60, "triangle1")); // 230 is an edge case

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeOneGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeOneOver());
    }
  }

  TEST_CASE("Mode Two Game Over") {
    // ----------all of the mode one game over tests are applicable to mode two so I will not repeat them----------
    std::vector<Obstacle> obstacles;
    PlayerManager player_manager;

    //----------ONE OBSTACLE----------

    SECTION("Collide from left of obstacle stationary") {
      Player player(glm::vec2{280, 420}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide from left of obstacle moving") {
      Player player(glm::vec2{279, 420}, glm::vec2{0,0}); // 279 is edge case
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{-1,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide/touch from right of obstacle stationary") {
      Player player(glm::vec2{380, 420}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide/touch from right of obstacle moving") {
      Player player(glm::vec2{381, 420}, glm::vec2{0,0}); // 381 is edge case
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{1,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide in middle of obstacle from left moving") {
      Player player(glm::vec2{280, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{-1,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide in middle of obstacle from left stationary") {
      Player player(glm::vec2{280, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide in middle of obstacle from right moving") {
      Player player(glm::vec2{381, 430}, glm::vec2{0,0}); // 381 is edge case
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{1,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide in middle of obstacle from right stationary") {
      Player player(glm::vec2{380, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide right on bottom left corner") {
      Player player(glm::vec2{280, 490}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide right on bottom right corner") {
      Player player(glm::vec2{380, 490}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      
      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding on bottom left corner") {
      Player player(glm::vec2{359, 191}, glm::vec2{0,0}); // right off the corner
      obstacles.push_back(Obstacle(glm::vec2{400, 100}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding on bottom right corner") {
      Player player(glm::vec2{441, 191}, glm::vec2{0,0}); // right off the corner
      obstacles.push_back(Obstacle(glm::vec2{400, 100}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding from left with approaching obstacle") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{-1,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding from right with approaching obstacle") {
      Player player(glm::vec2{500, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{1,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{500, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

      //----------MULTIPLE OBSTACLES----------

    SECTION("Collide from left of obstacle stationary in between") {
      Player player(glm::vec2{280, 420}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{430, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide from left of second obstacle moving/jumped pass first(obstacles moving left)") {
      Player player(glm::vec2{280, 420}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{-1,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{180, 400}, glm::vec2{-1,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }


    SECTION("Collide/touch from right of obstacle stationary in between") {
      Player player(glm::vec2{380, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));
      obstacles.push_back(Obstacle(glm::vec2{180, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide/touch from right of first obstacle moving/jumped pass second(obstacles moving right)") {
      Player player(glm::vec2{380, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{330, 400}, glm::vec2{1,0}, 70, 60, "triangle2"));
      obstacles.push_back(Obstacle(glm::vec2{480, 400}, glm::vec2{1,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding in between moving obstacles") {
      Player player(glm::vec2{380, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{320, 400}, glm::vec2{1,0}, 70, 60, "triangle2"));
      obstacles.push_back(Obstacle(glm::vec2{480, 400}, glm::vec2{1,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding from left with approaching obstacles") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{-1,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{500, 100}, glm::vec2{-2,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding from right with approaching obstacles") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{1,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{500, 100}, glm::vec2{2,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding stationary objects with player in between") {
      Player player(glm::vec2{380, 430}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{320, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));
      obstacles.push_back(Obstacle(glm::vec2{480, 400}, glm::vec2{0,0}, 70, 60, "triangle2"));


      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding stationary objects from right") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{500, 100}, glm::vec2{0,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Not colliding stationary objects from left") {
      Player player(glm::vec2{200, 350}, glm::vec2{0,0});
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));
      obstacles.push_back(Obstacle(glm::vec2{500, 100}, glm::vec2{0,0}, 70, 60, "triangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      game_engine.UpdateObstacle();
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE_FALSE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide with top game frame") {
      Player player(glm::vec2{200, 100}, glm::vec2{0,0}); // 100 is y of top frame
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);
      
      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }

    SECTION("Collide with bottom game frame") {
      Player player(glm::vec2{200, 467}, glm::vec2{0,0}); // 467 is y of bottom frame
      obstacles.push_back(Obstacle(glm::vec2{400, 101}, glm::vec2{0,0}, 70, 60, "rectangle2"));

      GameEngine game_engine = GameEngine(player, obstacles);

      player_manager.IsModeTwoGameOver(player, game_engine.GetObstacle());

      REQUIRE(player_manager.GetIsModeTwoOver());
    }
  }

  TEST_CASE("Mode One Collision") {
    std::vector<Obstacle> obstacles;
    PlayerManager player_manager;
    
    SECTION("Collide with top boundary") {
      Player player(glm::vec2{200, 167}, glm::vec2{0,-1}); // 177 is y of top jump bound

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE(player_manager.IsCollideWithTop(player));
      
      player_manager.CalculatePostTopCollisionVelocity(player);
      REQUIRE(player.GetVelocity() == glm::vec2{0,1});
    }

    SECTION("Post top collision velocity") {
      Player player(glm::vec2{200, 167}, glm::vec2{0,-1});

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();
      player_manager.CalculatePostTopCollisionVelocity(player);
      
      REQUIRE(player.GetVelocity() == glm::vec2{0,1});
    }

    SECTION("Doesn't collide with top boundary") {
      Player player(glm::vec2{200, 200}, glm::vec2{0,-1});

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE_FALSE(player_manager.IsCollideWithTop(player));
    }
    
    SECTION("Collide with bottom boundary") {
      Player player(glm::vec2{200, 550}, glm::vec2{0,1});

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE(player_manager.IsCollideWithFloor(player));
    }

    SECTION("Post bottom collision velocity") {
      Player player(glm::vec2{200, 550}, glm::vec2{0,1});

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();
      player_manager.CalculatePostBottomCollisionVelocity(player);

      REQUIRE(player.GetVelocity() == glm::vec2{0,0});
    }

    SECTION("Doesn't collide with bottom boundary") {
      Player player(glm::vec2{200, 444}, glm::vec2{0,1});

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE_FALSE(player_manager.IsCollideWithFloor(player));
    }
    
    SECTION("Collide with obstacle top") {
      Player player(glm::vec2{200, 300}, glm::vec2{0,1});
      obstacles.push_back(Obstacle(glm::vec2{200, 350}, glm::vec2{0,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE(player_manager.IsCollideWithObstacleTop(player, obstacles));
    }
    
    SECTION("Post obstacle top collision velocity") {
      Player player(glm::vec2{200, 300}, glm::vec2{0,1});
      obstacles.push_back(Obstacle(glm::vec2{200, 350}, glm::vec2{0,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();
      player_manager.CalculatePostObstacleTopCollisionVelocity(player);

      REQUIRE(player.GetVelocity() == glm::vec2{0,6.5});
    }

    SECTION("Doesn't collide with obstacle top") {
      Player player(glm::vec2{200, 200}, glm::vec2{0,1});
      obstacles.push_back(Obstacle(glm::vec2{200, 350}, glm::vec2{0,0}, 70, 60, "rectangle1"));

      GameEngine game_engine = GameEngine(player, obstacles);
      game_engine.UpdatePlayer();

      REQUIRE_FALSE(player_manager.IsCollideWithObstacleTop(player, obstacles));
    }
  }

  TEST_CASE("Mode one jump") {
    
  }

  TEST_CASE("Mode two jump") {
    
  }
  
}