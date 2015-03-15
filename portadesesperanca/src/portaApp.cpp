#include "portaApp.h"


void portaApp::onVideoEnd(ofxOMXPlayerListenerEventData& e)
{
	ofLogVerbose(__func__) << " RECEIVED";
    //omxPlayer.restartMovie();
    omxPlayer.setPaused(true);
}

void portaApp::onCharacterReceived(KeyListenerEventData& e)
{
    keyPressed( (int) e.character );
}



//--------------------------------------------------------------
void portaApp::setup()
{
	ofBackground(ofColor::black);
	ofHideCursor()

	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	
	//this will let us just grab a video without recompiling
	ofDirectory currentVideoDirectory(ofToDataPath(PORTA_MOVIES_PATH, true));
	if (currentVideoDirectory.exists()) 
	{
		currentVideoDirectory.listDir();
		currentVideoDirectory.sort();
		vector<ofFile> files = currentVideoDirectory.getFiles();
		if (files.size()>0) 
		{
			movieFile = files[0].path();
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

    // Wiring PI
	wiringPiSetupGpio();    
	pinMode( SENSOR_PORT, INPUT );
	pullUpDnControl( SENSOR_PORT, PUD_UP );
}

//--------------------------------------------------------------
void portaApp::update() {
	//update background tasks here

	// read sensor.
	bool door_read = (bool) digitalRead( SENSOR_PORT );

	// DOOR OPENED
	if(!is_door_open and (door_read == TRUE)){
    	ofLog(OF_LOG_VERBOSE, "door opened!");
		omxPlayer.setPaused(false);
	// DOOR CLOSED
	}else if(is_door_open and (door_read == FALSE)){
    	ofLog(OF_LOG_VERBOSE, "door closed!");
		omxPlayer.restartMovie();
		omxPlayer.setPaused(true);
	}
}

//--------------------------------------------------------------
void portaApp::draw(){
	//not used as the non-textured player takes over the screen
    //
    omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	if(show_info){
			ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
	}

}


void portaApp::keyPressed(int key){
    ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    if(key == 'p'){
        omxPlayer.setPaused( !omxPlayer.isPaused() );
    }
    if (key == 'r'){
        omxPlayer.restartMovie();
    }
    if (key == 'i'){
		show_info = !show_info;
    }
}

