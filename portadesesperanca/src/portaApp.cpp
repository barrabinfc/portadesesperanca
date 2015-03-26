#include "portaApp.h"

//--------------------------------------------------------------
void portaApp::setup()
{
	ofBackground(ofColor::black);
	ofHideCursor();

	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
    ofSetFrameRate(60);
    ofSetFullscreen(true);

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
			settings.enableLooping = true;		//default true
			settings.enableTexture = true;		//default true
			settings.listener = this;			//this app extends ofxOMXPlayerListener so it will receive events ;
		}
	}


    if(!settings.enableTexture)
    {
        // adjust width,height x,y, if necessary
        //settings.displayRect.width = ofget;
    }
    omxPlayer.setup(settings);
    omxPlayer.setPaused(true);
    consoleListener.setup(this);

    // intro
    introFile.loadImage( INTRO_IMAGE );

    // Wiring PI
	wiringPiSetupGpio();
	pinMode( SENSOR_PORT, INPUT );
	pullUpDnControl( SENSOR_PORT, PUD_UP );
}

//------------------------------------------------------ --------
void portaApp::update() {
	//update background tasks here
    time = ofGetElapsedTimef();

	// read sensor.
	bool door_read = (bool) digitalRead( SENSOR_PORT );

	// DOOR OPENED
	if(!is_door_open and (door_read == true)){
        portaOpened();
	// DOOR CLOSED
	}else if(is_door_open and (door_read == false)){
        portaClosed();
	}
}

void portaApp::portaOpened(){
    mode = MODE_DOOR_OPEN;
    is_door_open = true;
    ofLog(OF_LOG_VERBOSE, "door opened!");
    omxPlayer.setPaused(false);
}

void portaApp::portaClosed(){
    mode = MODE_DOOR_CLOSED;
    ofLog(OF_LOG_VERBOSE, "door closed!");
    is_door_open = false;
    omxPlayer.setPaused(true);
    omxPlayer.restartMovie();
    omxPlayer.setPaused(true);
}

//--------------------------------------------------------------
void portaApp::draw(){

    //ofDrawBitmapStringHighlight( ofToString(time), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
    if(mode == MODE_INTRO){
        introFile.draw(0,0, ofGetWidth(), ofGetHeight());

        if(time >= INTRO_TIMEOUT){
            mode = MODE_DOOR_CLOSED;
        }
    }else if(mode == MODE_DOOR_OPEN){
        //not used as the non-textured player takes over the screen
        omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

        if(show_info){
                ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
        }
    }
}


void portaApp::keyPressed(int key){
    ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    if (key == 'i'){
		show_info = !show_info;
    }
    if (key == 'o'){
        mode = MODE_DOOR_OPEN;
    }
    if(key == 'c'){
        mode = MODE_DOOR_CLOSED;
    }
    if(key == 'r'){
        mode = MODE_INTRO;
    }
    if(key == 'd'){
        ofLog(OF_LOG_VERBOSE, "Time: %f", time );
    }
}





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
