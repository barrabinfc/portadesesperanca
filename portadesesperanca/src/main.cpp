#include "ofMain.h"
#include "portaApp.h"
#include "ofGLProgrammableRenderer.h"

int main()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1080, 1920, OF_FULLSCREEN);
	ofRunApp( new portaApp());
}
