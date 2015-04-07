#include "portaApp.h"

//--------------------------------------------------------------
void portaApp::setup()
{
	ofBackground(ofColor::black);
	ofHideCursor();
    ofSetVerticalSync(false);

	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
    ofSetFrameRate(30);
    //piHiPri(20);

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
			settings.enableTexture = false;		//default true
			settings.enableAudio = true;
			settings.listener = this;			//this app extends ofxOMXPlayerListener so it will receive events ;
		}
	}

    ofLogVerbose(__func__) << "loaded video " << movieFile.path();

    omxPlayer.setup(settings);
    omxPlayer.setPaused(true);
    consoleListener.setup(this);

    // intro
    introFile.loadImage( INTRO_IMAGE );

    // Wiring PI
	wiringPiSetupGpio();
	pinMode( SENSOR_PORT, INPUT );
	pullUpDnControl( SENSOR_PORT, PUD_UP );

    //wiringPiISR( SENSOR_PORT, INT_EDGE_BOTH , &portaApp::onPortaChange );
}

//------------------------------------------------------ --------
void portaApp::update() {
	//update background tasks here
    time = ofGetElapsedTimef();

    onPortaChange();
}

void portaApp::onPortaChange(){
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
    omxPlayer.setPaused(false);

    mode = MODE_DOOR_OPEN;
    is_door_open = true;
    ofLog(OF_LOG_VERBOSE, "door opened!");
}

void portaApp::portaClosed(){
    omxPlayer.setPaused(true);
    omxPlayer.seekToTimeInSeconds(0);

    mode = MODE_DOOR_CLOSED;
    ofLog(OF_LOG_VERBOSE, "door closed!");
    is_door_open = false;
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
        /*
        if(omxPlayer.isPlaying() && omxPlayer.isFrameNew()){
            omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
        }
        */

        /*
        if(show_info){
                ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
        }
        */

    }else if(mode == MODE_DOOR_CLOSED){

        // just wait...
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
