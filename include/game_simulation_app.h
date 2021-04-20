#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_engine.h"

namespace geometrydash {

/**
 * An app for visualizing the game of Geometry Dash.
 */
  class GeometryDashApp : public ci::app::App {
  public:
    /**
     * Constructor that initializes a container for game to run in.
     */
    GeometryDashApp();

    /**
     * Method that shows the current state of game.
     */
    void draw() override;

    /**
     * Method that updates the current state of game.
     */
    void update() override;

    /**
     * Method that applies function from keyboard.
     *
     * @param event
     */
    void keyDown(cinder::app::KeyEvent event) override;

  private:
    const size_t kWindowLength = 1300;    // display window length
    const size_t kWindowWidth = 700;      // display window width
    const size_t kContainerMargin = 100;  // container margin

    GameEngine game_frame_ =
            GameEngine(glm::vec2(kContainerMargin, kContainerMargin),
                    glm::vec2(kWindowLength - kContainerMargin, kWindowWidth - kContainerMargin));  // instance of game frame
  };

}  // namespace idealgas
