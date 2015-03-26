#pragma once
#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "TerminalListener.h"

#include "wiringPi.h"

#define PORTA_MOVIES_PATH "/home/pi/porta/movies"
#define INTRO_IMAGE       "/home/pi/porta/img/intro.png"
#define SENSOR_PORT 36

#define MODE_INTRO 0
#define MODE_DOOR_CLOSED 1
#define MODE_DOOR_OPEN 2
#define MODE_DOOR_VIDEOPLAYED 3

#define INTRO_TIMEOUT 3000

class portaApp : public ofBaseApp, public ofxOMXPlayerListener, public KeyListener {

	public:
		portaApp() :
			sensor_port(SENSOR_PORT),
			is_door_open(false),
			show_info(false),
            mode( MODE_INTRO )
		{};

		ofxOMXPlayerSettings settings;
		ofxOMXPlayer omxPlayer;
		ofFile      movieFile;
        ofImage     introFile;

		int  sensor_port; 	// BCM Port
		bool is_door_open;
		bool show_info;

        int mode;
        float time;

		void setup();
		void update();
		void draw();

        void doorOpened();
        void doorClosed();

		void keyPressed(int key);

		void onVideoEnd(ofxOMXPlayerListenerEventData& e);
		void onVideoLoop(ofxOMXPlayerListenerEventData& e){ /*empty*/ };

		TerminalListener consoleListener;
		void onCharacterReceived(KeyListenerEventData& e);
};

