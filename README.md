Welcome to Geometry Dash! Glad that you are here :')
- 
 This is a game that was made based off of the popular game
  [Geometry Dash](https://en.wikipedia.org/wiki/Geometry_Dash). Unfortunately, it is lamer. But on a brighter side,
it can be very easily understood and played.

---
  
Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html)
to understand the project layout.

Dependency used: [Cmake](https://cmake.org/), [CLion 2021.1.1](https://www.jetbrains.com/clion/download/#section=mac),
[Clang](https://clang.llvm.org/)

Library used: [Cinder](https://libcinder.org/)

---

To build this project:
-
1) Download and install [Cinder](https://libcinder.org/download)
   (Instructions can be found [here]((https://courses.grainger.illinois.edu/cs126/sp2021/notes/cinder-installation-notes/)))
2) Download and install [CLion](https://www.jetbrains.com/clion/download/#section=mac)
3) Open  ~/Cinder folder in CLion and click green build button on top right to build project.
4) Create a directory folder in ~/Cinder and clone this project into the folder. 
5) Open project in CLion, set the target to cinder-myapp 
6) Click run button to run game. Have fun :')
   
---

Basic game rules:
- 
- YOU ARE THE SQUARE! The square that you see in game is the player,
  aka you. And you have full control over it.
- AVOID OBSTACLES! Running into or hitting any obstacles WILL
kill you.
- There are two modes in this game- original and "flappy bird"

- ORIGINAL MODE
    - Although running into obstacles will kill you, feel free to 
      land on top of the rectangular obstacles!
      - However, make sure to time it right. Hitting any part of 
    obstacles besides the top will again, kill you.
    - Player may only jump once upon every landing. ONCE ONLY.
    JUMP WISELY.
  - Obstacles will only generate on the bottom.
- FLAPPY BIRD MODE
    - This mode begins immediately once player hits a score of 1000.
    - Running into any obstacle WILL kill you.
        - Unlike original, you cannot land on any obstacle.
        - tldr, AVOID OBSTACLES AT ALL COSTS
    - Unlike original, obstacles will generate on top AND bottom.
    - AVOID CEILING AND FLOOR
        - Hitting the top of game frame or the bottom line will also
          kill you.
    - Key down- player moves up.
        - Can hold continuously!
    - Key up- player moves down.
        - Can hold continuously!
- In both modes, obstacles' speed increases as the game runs.
- Don't worry if you die, press ' r ' key anytime to restart game :)

---

Keyboard Commands
-
- Key ' spacebar ' to start game and jump (original mode), move
  up when pressed and move down when released(flappy bird mode).
- Key ' r ' to restart game after death.
- Mac users- Command+Q to quit game.
- Windows users - Ctrl+Q to quit game.

---

**Author**: Angel Dong - [`adong6@illinois.edu`](mailto:adong6@illinois.edu)