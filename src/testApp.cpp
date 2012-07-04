#include "testApp.h"


bool compareZpos(ofPtr<chime> a, ofPtr<chime> b){return (a->getZpos() < b->getZpos());}

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(TARGET_FRAME);
	ofSetCircleResolution(100);
	
	scale = 80;
	
	
	mCam.cacheMatrices(true);
	mCam.setNearClip(0);
	mCam.setFarClip(2000);
	mCam.setPosition(0,0,800);
	mCam.lookAt(ofVec3f(0,0,0), ofVec3f(0,1,0));

	sender.setup(HOST,SC_PORT);
	iSender.setup(I_HOST, I_PORT);
	receiver.setup(IN_PORT);
	
	chimeManager::setup(sender, iSender);
	
	ofxOscMessage m;
	m.setAddress("/init");
	sender.sendMessage(m);

	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	
	setupMenus();
	setupPresets();
	
	mCurrentPreset = 0;
	currentMode = e_MenuType(0);

	
}

void testApp::setupMenus(){
	
	menuStrings.push_back("add");
	menuStrings.push_back("select");
	menuStrings.push_back("adjust");
	
}

void testApp::setupPresets(){
	
	groupPreset p;
	
	p.name = "singleQuantPhase";
	p.numChimes = 1;
	p.pos.initVal.set(ofVec2f(0,0));
	p.pos.dType = DT_NONE;
	p.pos.increment.set(ofVec2f(0,0.5));
	p.pos.range = 5;
	p.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p.freq.dType = DT_FLAT;
	p.freq.range = 12;
	p.freq.increment = 3;
	p.iAngle.initVal = 0;
	p.iAngle.dType =  DT_FLAT;
	p.iAngle.increment = b2_pi * 0.05;
	p.iAngle.range = 10;
	p.speed.initVal = 1.0;
	p.length.initVal = 2.0;
	
	mPresets.push_back(p);
	
	groupPreset p2;
	
	p2.name = "multipleQuantPhase";
	p2.numChimes = ofRandom(5,20);
	p2.pos.initVal.set(ofVec2f(0,0));
	p2.pos.dType = DT_NONE;
	p2.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p2.freq.dType = DT_FLAT;
	p2.freq.range = 12;
	p2.freq.increment = 3;
	p2.iAngle.initVal = 0;
	p2.iAngle.dType =  DT_STEP;
	p2.iAngle.increment = b2_pi * (float)1.0f/p2.numChimes;
	p2.speed.initVal = 1.0;
	p2.length.initVal = 2.0;
	
	mPresets.push_back(p2);
	
	
	groupPreset p1;
	
	p1.name = "singleNormSpeed";
	p1.numChimes = 1;
	p1.pos.initVal.set(ofVec2f(0,0));
	p1.pos.dType = DT_NONE;
	p1.pos.increment.set(ofVec2f(0,0.5));
	p1.pos.range = 5;
	p1.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p1.freq.dType = DT_FLAT;
	p1.freq.range = 12;
	p1.freq.increment = 3;
	p1.iAngle.initVal = 0;
	p1.iAngle.dType =  DT_FLAT;
	p1.iAngle.increment = b2_pi * 0.01;
	p1.iAngle.range = 100;
	p1.speed.dType = DT_NORMAL;
	p1.speed.initVal =  -0.3;
	p1.speed.increment = 0.05;
	p1.speed.range = 10;
	p1.length.initVal = 4.0;
	
	mPresets.push_back(p1);
	

	

}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	handleMessages();
	
	chimeManager::update();
	
	
}

void testApp::handleMessages(){

	while (receiver.hasWaitingMessages()) {
		
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if ( m.getAddress() == "/focalPoint" ){
			
			chimeManager::shiftFocalPoint(m.getArgAsFloat(0));
			
			
		}else if ( m.getAddress() == "/zPos" ){
			
			chimeManager::shiftZPos(m.getArgAsFloat(0));
			
		}else if ( m.getAddress() == "/switchGroup" ){
			
			chimeManager::selectNewGroup();
			
		}
			
		
		
	}

}

ofVec2f testApp::getZPlaneProjection(ofVec2f screenPoint){
	
	ofRectangle viewport(0,0,ofGetScreenWidth(),ofGetScreenHeight());
	
	ofVec3f ray[2];
	
	//define ray in screen space
	ray[0] = ofVec3f(screenPoint.x, screenPoint.y, -1);
	ray[1] = ofVec3f(screenPoint.x, screenPoint.y, 1);
	
	//transform ray into world space
	ray[0] = mCam.screenToWorld(ray[0], viewport);
	ray[1] = mCam.screenToWorld(ray[1], viewport);
	
	ofVec3f rayvec(ray[1]-ray[0]);
	ofVec2f intersect;
	
	float u = -1 * ray[0].z/rayvec.z; //for some reason it needs to be reversed
	intersect.x = ray[0].x + rayvec.x * u;
	intersect.y = ray[0].y + rayvec.y * u;
	
	return intersect/scale;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	GLfloat fogColor[4]= {1.0f, 1.0f, 1.0f, 1.0f}; 
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	mCam.begin();
	
	glFogi(GL_FOG_MODE, GL_LINEAR);      
	glFogfv(GL_FOG_COLOR, fogColor);            
	glFogf(GL_FOG_DENSITY, 0.1f);              
	glHint(GL_FOG_HINT, GL_NICEST);       
	glFogf(GL_FOG_START, 800.0f);           
	glFogf(GL_FOG_END, 825.0f);               
	glEnable(GL_FOG);     
	
	
	glPushMatrix();
	glScalef(scale, scale, 1);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	chimeManager::draw();
	
	drawActions();
	
	ofDisableBlendMode();
	
	glPopMatrix();
	
	glDisable(GL_FOG); 
	
	mCam.end();
	
	
	ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	ofEnableAlphaBlending();
	ofSetColor(0,20);
	ofRect(0,0,ofGetScreenWidth(),30);
	ofDisableAlphaBlending();
	ofSetColor(100);
	
	ofDrawBitmapString("mode: " + menuStrings[currentMode], 20,20);
	ofDrawBitmapString("preset: " + mPresets[mCurrentPreset].name, 300,20);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(),2), 1100,20);
	

	
}


void testApp::drawActions(){
	
	ofEnableSmoothing();
	
	if(currentAction  == AT_ADD){};
	
	if(currentAction == AT_SELECT_POS){
			
			ofNoFill();
			ofSetColor(150);
			ofCircle(mouseDownPos, distParam);
			chimeManager::drawSelected();
			
	}
			
	if(currentAction == AT_SELECT_SPEED){
			
		float d = 1.0 + distParam * 2.5;
		
			ofNoFill();
			ofSetColor(150);
			ofCircle(mouseDownPos,d);
			ofVec2f p(mouseDownPos + ofVec2f(0,d));
			p.rotateRad(angleParam * 2,mouseDownPos);
			ofLine(mouseDownPos.x, mouseDownPos.y, p.x, p.y);
			ofDrawBitmapString("rSpeed: " + ofToString(angleParam,2) +
							   "\ntollerance: " + ofToString(distParam, 2),
							   mouseDownPos + d);
			chimeManager::drawSelected();
	}
			
	if(currentAction == AT_ADJUST){};
			
	
	ofDisableSmoothing();


}

void testApp::beginAction(){

	//ActionTypes will become more specific
	
	switch (currentAction) {
		case AT_ADD:
			
			break;
		case AT_SELECT_POS:
			
			break;
		case AT_ADJUST:
			
			break;
		default:
			break;
	}

}

void testApp::continueAction(){
	
	switch (currentAction) {
		case AT_ADD:
			
			break;
		case AT_SELECT_POS:
			distParam = dragDist/2;
			chimeManager::selectByPos(mouseDownPos, distParam);
			break;
		
		case AT_SELECT_SPEED:
			distParam = max(0.0, dragDist - 2.0)/5;
			angleParam = -ofDegToRad(dragAngle)/2;
			angleParam -= fmod(angleParam, 0.01f);
			chimeManager::selectByRotSpeed(angleParam, distParam);
			break;
			
		case AT_ADJUST:
			
			break;
		default:
			break;
	}

	
}

void testApp::endAction(){

	switch (currentAction) {
		case AT_ADD:
			chimeManager::createChimes(mPresets[mCurrentPreset], mouseDownPos); //probably will add dragdist and direction 
			break;																//for user presets
																				//maybe use old strategy of screen mapping for extra controls
		case AT_SELECT_POS:

			
			break;
		case AT_SELECT_SPEED:

			
			break;
		case AT_ADJUST:
			
			break;
		default:
			break;
	}
	
	currentAction = AT_NONE;
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	for(int i = 0; i < MT_COUNT; i++){
	
		if(key == 49 + i)currentMode = e_MenuType(i);
	
	}
	
	
	if(key == OF_KEY_UP)mCurrentPreset = min(mCurrentPreset + 1, (int)mPresets.size() -1);
	if(key == OF_KEY_DOWN)mCurrentPreset = max(mCurrentPreset - 1,0);
	
	if(key == 'x')chimeManager::shiftFocalPoint(0.0f);
	if(key == 'z')chimeManager::shiftFocalPoint(1.0f);
	
	if(key == 'a')chimeManager::shiftZPos(0.0f);
	if(key == 's')chimeManager::shiftZPos(1.0f);
	
	
	/*if(key == 'n'){
	 
	 int count = 0;
	 for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
	 ofVec2f v(0.005,0); 
	 v *= count;
	 v += ofVec2f(-0.005,0) * NUM_CHIMES/2;
	 chimeUpdater::moveView(*it, v);
	 count += 1;
	 }
	 }
	 
	 if(key == 'm'){
	 
	 int count = 0;
	 for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
	 ofVec2f v(-0.005,0); 
	 v *= count;
	 v += ofVec2f(0.005,0) * NUM_CHIMES/2;
	 chimeUpdater::moveView(*it, v);
	 count += 1;
	 }
	 }*/
		

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	

	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	mouseDragPos = getZPlaneProjection(ofVec2f(x,y));
	dragDist = ofVec2f(mouseDragPos - mouseDownPos).length();
	dragAngle = ofVec2f(mouseDragPos - mouseDownPos).angle(ofVec2f(0,1));
	continueAction();
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	mouseDownPos = getZPlaneProjection(ofVec2f(x,y));
	
	switch (currentMode) {
			
		case MT_ADD:currentAction = AT_ADD;break;
		case MT_SELECT:currentAction = (button == 0)? AT_SELECT_POS : AT_SELECT_SPEED; break;
		case MT_ADJUST:currentAction = AT_ADJUST;break;
			
		default:
			break;
	}
	
	beginAction();
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	endAction();
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::exit(){

	ofxOscMessage m;
	m.setAddress("/exit");
	sender.sendMessage(m);

}