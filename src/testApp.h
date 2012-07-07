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
	
	enum e_ActionType {
		AT_ADD,
		AT_SELECT,
		AT_ADJUST,
		AT_NONE
	};
	
	enum e_MenuType {
		MT_ADD,
		MT_SELECT,
		MT_ADJUST,
		MT_COUNT
	};
	

	
	void setupMenus();
	
	void handleMessages();	
	void setupPresets();
	ofVec2f getZPlaneProjection(ofVec2f screenPoint);
	
	void beginAction();
	void continueAction();
	void endAction();
	
	void drawActions();

	ofCamera mCam;
	float scale;
	
	ofxOscSender sender, iSender;
	ofxOscReceiver receiver;
	
	vector<groupPreset> mPresets;
	int mCurrentPreset;
	
	e_ActionType currentAction;
	e_MenuType currentMode;

	
	vector<string> menuStrings;
	vector<string> selectStrings;
	vector<string> modStrings;
	
	//mouse stuff
	
	ofVec2f mouseDownPos, mouseDragPos, mouseMovePos;
	float dragDist, dragAngle;
	float distParam, angleParam;
	string mDisplayString;
	
	//search stuff
	
	bool isSearching;
	int currentFilter;
	int currentPreFilter;
	
	int currentMod;

	
	
};
