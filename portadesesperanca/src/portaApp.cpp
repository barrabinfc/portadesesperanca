#include "portaApp.h"


void portaApp::onVideoEnd(ofxOMXPlayerListenerEventData& e)
{
	ofLogVerbose(__func__) << " RECEIVED";
    //omxPlayer.restartMovie();
    omxPlayer.pause();
}

void portaApp::onCharacterReceived(KeyListenerEventData& e)
{
    keyPressed( (int) e.character );
}



//--------------------------------------------------------------
void portaApp::setup()
{
	ofBackground(ofColor::black);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	
	//this will let us just grab a video without recompiling
	ofDirectory currentVideoDirectory(ofToDataPath(PORTA_MOVIES_PATH, true));
	if (currentVideoDirectory.exists()) 
	{
		currentVideoDirectory.listDir();
		currentVideoDirectory.sort();
		files = currentVideoDirectory.getFiles();
		if (files.size()>0) 
		{
			settings.videoPath = files[0].path();
			settings.useHDMIForAudio = true;	//default true
			settings.enableLooping = false;		//default true
			settings.enableTexture = true;		//default true
			settings.listener = this;			//this app extends ofxOMXPlayerListener so it will receive events ;
		}		
	}


    if(!settings.enableTexture)
    {
        // adjust width,height x,y, if necessary
        // settings.displayRect.width = 400;
    }

    omxPlayer.setup(settings);
    consoleListener.setup(this);
}

//--------------------------------------------------------------
void portaApp::update() {
	//update background tasks here
}

//--------------------------------------------------------------
void portaApp::draw(){
	//not used as the non-textured player takes over the screen
    //
    omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);

}


void portaApp::keyPressed(int key){
    ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    if(key == 'p'){
        omxPlayer.setPaused( !omxPlayer.isPaused() );
    }
    if (key == 'r'){
        omxPlayer.restartMovie();
    }
}

