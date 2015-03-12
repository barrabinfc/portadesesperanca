#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "TerminalListener.h"

#define PORTA_MOVIES_PATH "/home/pi/porta/movies"

class portaApp : public ofBaseApp, public ofxOMXPlayerListener, public KeyListener {

	public:

		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		ofxOMXPlayer omxPlayer;
	
		void onVideoEnd(ofxOMXPlayerListenerEventData& e);
		void onVideoLoop(ofxOMXPlayerListenerEventData& e){ /*empty*/ };

		ofFile movieFile;
	
		void onCharacterReceived(KeyListenerEventData& e);
		TerminalListener consoleListener;
		ofxOMXPlayerSettings settings;
};

