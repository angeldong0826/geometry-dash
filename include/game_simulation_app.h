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
     * Method that applies function from keyboard, when key is pressed down.
     *
     * @param event
     */
    void keyDown(cinder::app::KeyEvent event) override;

    /**
     * Method that applies function from keyboard, when key is released.
     * 
     * @param event 
     */
    void keyUp(cinder::app::KeyEvent event) override;

    /**
     * Method to display start menu.
     */
    void DisplayStartMenu() const;

  private:
    const size_t kWindowLength = 1300;// display window length
    const size_t kWindowWidth = 700;  // display window width
    const size_t kFrameMargin = 100;  // frame margin
    const glm::vec2 kCenter = {650, 350};// center of game frame
    const glm::vec2 kParenthesisDisplay = {650,400}; // position for score display
    const glm::vec2 kInstructionDisplay = {650,450}; // position for score display

    bool is_starting_page_ = true; // if on starting page

    GameEngine game_engine_ =
            GameEngine(glm::vec2(kFrameMargin, kFrameMargin),
                       glm::vec2(kWindowLength - kFrameMargin, kWindowWidth - kFrameMargin));// instance of game engine
  };

}// namespace geometrydash
