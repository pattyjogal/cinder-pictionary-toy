#include "pictionary_app.h"

using pictionary::PictionaryApp;

void prepareSettings(PictionaryApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(PictionaryApp, ci::app::RendererGl, prepareSettings)