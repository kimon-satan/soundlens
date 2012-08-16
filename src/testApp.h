#pragma once

#include "ofMain.h"
#include "chimeManager.h"
#include "tuningEngine.h"

#define HOST "127.0.0.1"
#define SC_PORT 57120
#define IN_PORT 8010
#define I_HOST "192.168.1.3"
#define I_PORT 9000

//could have somthing similar for mods

struct searchPreset{

	string name;
	vector<int> autoMacro;
	vector<ofVec2f>autoSettings;
	
	vector<int> manualMacro;

};

struct bank{
	
	string name;
	
	vector<searchPreset> searches;
	vector<copyPreset> copies;
	vector<int> mods;


};


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
		MT_COPY,
		MT_SEARCH,
		MT_MOVE,
		MT_PIVOT,
		MT_COUNT,
	};
	
	
	void handleMessages();	

	void setupCopyPresets();
	void setupSearchPresets();
	void setupBanks();
	searchPreset getSearchPreset(string name);
	copyPreset getCopyPreset(string name);
	
	ofVec2f getZPlaneProjection(ofVec2f screenPoint);
	
	void beginAction();
	void continueAction();
	void endAction();
	
	void drawActions();
	
	void newSearch(bool useResults);

	ofCamera mCam;
	float scale;
	
	ofxOscSender sender, iSender;
	ofxOscReceiver receiver;
	
	e_ActionType currentAction;
	int currentMode;
	int mDCount;
	
	vector<string> menuStrings;
	
	//mouse stuff
	
	ofVec2f mouseDownPos, mouseDragPos, mouseMovePos;
	bool isMouseDown, isRM;
	float dragDist, dragAngle;
	float distParam, angleParam;
	string mDisplayString;

	bool isLastActionCopy;
	
	//search stuff

	vector<searchPreset> searchPresets;
	vector<copyPreset> copyPresets;
	
	vector<bank> banks;
	
	vector<vector<searchPreset> > searchBank;
	vector<vector<copyPreset> > copyBank;
	
	
	int cSearchPreset, cMacroStage;
	int currentMod;
	int mCurrentCopier, mCurrentBank;
	bool isTab;
	
	
};
