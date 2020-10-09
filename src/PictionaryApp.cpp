#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PictionaryApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void PictionaryApp::setup()
{
}

void PictionaryApp::mouseDown( MouseEvent event )
{
}

void PictionaryApp::update()
{
}

void PictionaryApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( PictionaryApp, RendererGl )
