#pragma once

#include "ofMain.h"
#include "chimeFactory.h"
#include "chimeRenderer.h"
#include "chimeUpdater.h"

#define HOST "127.0.0.1"
#define PORT 57120
#define NUM_CHIMES 85


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void setupChimes();
		void rePopulateRenderList();
	
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
	
	
	ofCamera mCam;
	float scale;
	vector<vector<ofPtr<chime> > > mChimes;

	vector<vector<ofPtr<chime> > > renderList;
	
	customListener mListener;
	ofxOscSender sender;
	
	int selCGroup;
	
	bool isBlurring;
	
	
	
};
