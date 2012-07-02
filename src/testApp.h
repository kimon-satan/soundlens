#pragma once

#include "ofMain.h"
#include "chimeManager.h"

#define HOST "127.0.0.1"
#define SC_PORT 57120
#define IN_PORT 8010
#define I_HOST "192.168.1.3"
#define I_PORT 9000

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		

	
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void exit();
	
	private:
	
	void handleMessages();	
	
	ofCamera mCam;
	float scale;
	
	ofxOscSender sender, iSender;
	ofxOscReceiver receiver;
	
	
	
};
