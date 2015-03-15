#pragma once
#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "TerminalListener.h"

#include "wiringPi.h"

#define PORTA_MOVIES_PATH "/home/pi/porta/movies"
#define SENSOR_PORT 36

class portaApp : public ofBaseApp, public ofxOMXPlayerListener, public KeyListener {

	public:
		ofxOMXPlayerSettings settings;
		ofxOMXPlayer omxPlayer;
		ofFile movieFile;

		int  sensor_port = 36; 	// BCM Port
		bool is_door_open = false;

		bool show_info = false;

		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
	
		void onVideoEnd(ofxOMXPlayerListenerEventData& e);
		void onVideoLoop(ofxOMXPlayerListenerEventData& e){ /*empty*/ };

		TerminalListener consoleListener;
		void onCharacterReceived(KeyListenerEventData& e);
};

