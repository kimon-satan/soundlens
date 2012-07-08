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
	currentFilter= e_SearchType(1);
	currentPreFilter = SEARCH_SAMP_SPEED;
	currentMod = MOD_GATHER;
	
	isSearching = false;
	
}

void testApp::setupMenus(){
	
	menuStrings.push_back("add");
	menuStrings.push_back("select");
	menuStrings.push_back("adjust");
	
	
	
}

void testApp::setupPresets(){
	
	groupPreset p;
	
	p.name = "single";
	p.numChimes.initVal.set(1);
	
	for(int i = 0; i < 2; i ++){
		p.fParams[CH_FREQ_A + i].initVal.set(MIDI_MIN + MIDI_RANGE/2);
		p.fParams[CH_FREQ_A + i].dType = DT_NONE;
		p.fParams[CH_DECAY_A + i].initVal.set(1.8);
	}
	
	p.fParams[CH_PHASE].initVal.set(0.5);
	p.fParams[CH_PHASE].dType =  DT_FLAT;
	p.fParams[CH_PHASE].increment.set(b2_pi * 1.0f/64.0f);
	p.fParams[CH_PHASE].range.set(10);
	p.fParams[CH_SPEED].initVal.set(1.0);
	p.fParams[CH_LENGTH].initVal.set(2.0);
	
	mPresets.push_back(p);
	

	

}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	handleMessages();
	
	chimeManager::update();
	
	if(currentMode == MT_SELECT){
		if(isSearching){
			chimeManager::selectSample(mouseMovePos);
			chimeManager::newSearch();
			if(currentPreFilter == SEARCH_SAMP_SPEED){
				chimeManager::continueSearch(currentPreFilter, mouseDownPos, mouseDragPos, dragDist, dragAngle);
			}
		}
	}
	
	
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
			
			//chimeManager::selectNewGroup();
			
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
	
	if(MT_SELECT){
		
		if(isSearching){
			chimeManager::drawSample();
			chimeManager::drawTmpSelected();
		}
		

	}
	
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
	
	switch (currentMode) {
		case MT_ADD:
			ofDrawBitmapString("preset: " + mPresets[mCurrentPreset].name, 300,20);
			break;
		case MT_SELECT:
			ofDrawBitmapString("preFilter: " + chimeManager::getSearchName(currentPreFilter), 300,20);
			ofDrawBitmapString("filter: " + chimeManager::getSearchName(currentFilter), 600,20);
			break;
		case MT_ADJUST:
			ofDrawBitmapString("modType: " + chimeManager::getModName(currentMod) , 300,20);
			break;
			
		default:
			break;
	}
	
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(),2), 1100,20);
	

	
}


void testApp::drawActions(){
	
	ofEnableSmoothing();
	
	if(currentAction  == AT_ADD){
	
		chimeManager::drawPreviewChimes();
		ofSetColor(100);
		ofLine(mouseDownPos.x, mouseDownPos.y, mouseDragPos.x, mouseDragPos.y);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
		
	}
	
	if(currentAction == AT_SELECT){
		
		chimeManager::drawTmpSelected();
		chimeManager::drawSelected();
		chimeManager::drawSearchEngine(currentFilter,dragDist, dragAngle);
		ofSetColor(100);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
		
		
	}
	
			
	if(currentAction == AT_ADJUST){
	
		chimeManager::drawSelected();
		chimeManager::drawModEngine(currentMod, dragDist, dragAngle);
		ofSetColor(100);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
	}
			
	
	ofDisableSmoothing();


}

void testApp::beginAction(){

	//ActionTypes will become more specific
	
	switch (currentAction) {
		case AT_ADD:
			break;
			
		case AT_SELECT:
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
			mDisplayString = chimeManager::createChimes(mPresets[mCurrentPreset], mouseDownPos, dragDist, dragAngle);
			break;
			
		case AT_SELECT:
			mDisplayString = chimeManager::continueSearch(currentFilter, mouseDownPos, mouseDragPos, dragDist, dragAngle);
			break;
			
		case AT_ADJUST:
			mDisplayString = chimeManager::continueMod(currentMod, mouseDownPos, mouseDragPos, dragDist, dragAngle);
			break;
			
		default:
			break;
	}

	
}

void testApp::endAction(){

	switch (currentAction) {
		case AT_ADD:
			chimeManager::endNewChimes();										
			break;																
																				
		case AT_SELECT:
			chimeManager::endSearch();
			break;
		

		case AT_ADJUST:
			chimeManager::endMod(currentMod);
			break;
			
		default:
			break;
	}
	
	currentAction = AT_NONE;
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	for(int i = 0; i < MT_COUNT; i++){
	
		if(key == 49 + i){
			currentMode = e_MenuType(i);
			if(currentMode == MT_SELECT)chimeManager::clearTmps();
			break;
		}
	
	}
	
	if(currentMode == MT_ADD){
		if(key == OF_KEY_UP)mCurrentPreset = min(mCurrentPreset + 1, (int)mPresets.size() -1);
		if(key == OF_KEY_DOWN)mCurrentPreset = max(mCurrentPreset - 1,0);
	}
	
	if(currentMode == MT_SELECT){
		
		if(key == OF_KEY_UP)currentFilter = min(currentFilter + 1, (int)SEARCH_COUNT -1);
		if(key == OF_KEY_DOWN)currentFilter = max(currentFilter - 1,0);
		if(key == ' '){isSearching = true;}

	}
	
	if(currentMode == MT_ADJUST){
		
		if(key == OF_KEY_UP)currentMod = min(currentMod + 1, (int)MOD_COUNT -1);
		if(key == OF_KEY_DOWN)currentMod = max(currentMod - 1,0);
		
	}
	
	
	if(key == 'x')chimeManager::shiftFocalPoint(0.0f);
	if(key == 'z')chimeManager::shiftFocalPoint(1.0f);
	
	if(key == 'a')chimeManager::shiftZPos(0.0f);
	if(key == 's')chimeManager::shiftZPos(1.0f);
	
	if(key == 'n')chimeManager::incrementMod(-1);
	if(key == 'm')chimeManager::incrementMod(1);

	
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

	if(key == ' '){
		isSearching = false;
		if(currentPreFilter == SEARCH_SAMP_SPEED){
			chimeManager::endSearch();
		}
		
	}
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	mouseMovePos = getZPlaneProjection(ofVec2f(x,y));
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	mouseDragPos = getZPlaneProjection(ofVec2f(x,y));
	dragDist = ofMap(ofVec2f(mouseDragPos - mouseDownPos).length(),1,4,0,1,true);
	dragAngle = ofVec2f(mouseDownPos - mouseDragPos).angle(ofVec2f(0,-1));
	if(dragAngle < 0)dragAngle += 360;
	dragAngle = ofMap(dragAngle, 0,360, 0, 1);
	continueAction();
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	mouseDownPos = getZPlaneProjection(ofVec2f(x,y));
	
	switch (currentMode) {
			
		case MT_ADD:currentAction = AT_ADD;break;
		case MT_SELECT:currentAction = AT_SELECT; break;
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