#include "game_simulation_app.h"

using geometrydash::GeometryDashApp;

void prepareSettings(GeometryDashApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(GeometryDashApp, ci::app::RendererGl, prepareSettings);