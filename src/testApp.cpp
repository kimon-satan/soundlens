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
	
	setupPresets();
	
	mCurrentPreset = 0;
	currentMode = e_MenuType(0);

	currentMod = MOD_GATHER;
	
	searchMacro[0] = SEARCH_POSITION;
	searchMacro[1] = SEARCH_SAMP_SPEED;
	searchMacro[2] = SEARCH_SAMP_PHASE_FUND;
	searchMacro[3] = SEARCH_QUANT_PHASE;
	
	isSearching = false;
	macroStage = 0;
	
	menuStrings.push_back("add");
	menuStrings.push_back("adjust");
	menuStrings.push_back("select");
	
}


void testApp::setupPresets(){
	
	groupPreset preset1;
	
	preset1.name = "single";
	preset1.numChimes.initVal.set(1);
	
	for(int i = 0; i < 2; i ++){
		preset1.fParams[CH_FREQ_A + i].initVal.set(MIDI_MIN + MIDI_RANGE/2);
		preset1.fParams[CH_FREQ_A + i].dType = DT_NONE;
		preset1.fParams[CH_DECAY_A + i].initVal.set(1.8);
	}
	
	preset1.fParams[CH_PHASE].initVal.set(0.5);
	preset1.fParams[CH_PHASE].dType =  DT_FLAT;
	preset1.fParams[CH_PHASE].increment.set(b2_pi * 1.0f/64.0f);
	preset1.fParams[CH_PHASE].range.set(10);
	preset1.fParams[CH_SPEED].initVal.set(1.0);
	preset1.fParams[CH_LENGTH].initVal.set(2.0);
	
	mPresets.push_back(preset1);
	
	groupPreset preset2;
	
	preset2.name = "multiple";
	preset2.numChimes.initVal.set(10);
	preset2.numChimes.dType = DT_FLAT;
	preset2.numChimes.range.set(3);
	preset2.numChimes.increment.set(1);
	
	for(int i = 0; i < 2; i ++){
		preset2.fParams[CH_FREQ_A + i].initVal.set(MIDI_MIN + MIDI_RANGE/2);
		preset2.fParams[CH_FREQ_A + i].dType = DT_FLAT;
		preset2.fParams[CH_FREQ_A + i].range.set(12);
		preset2.fParams[CH_FREQ_A + i].increment.set(3);
		preset2.fParams[CH_DECAY_A + i].initVal.set(1.8);
	}
	
	preset2.fParams[CH_PHASE].initVal.set(0);
	preset2.fParams[CH_PHASE].dType =  DT_SLICE;
	preset2.fParams[CH_PHASE].increment.set(b2_pi * 1.0f/64.0f);
	preset2.fParams[CH_PHASE].range.set(64);
	preset2.fParams[CH_SPEED].initVal.set(1.0);
	preset2.fParams[CH_LENGTH].initVal.set(2.0);
	
	mPresets.push_back(preset2);
	
	
	groupPreset preset3;
	
	preset3.name = "multipleClimber";
	preset3.numChimes.initVal.set(10);
	preset3.numChimes.dType = DT_FLAT;
	preset3.numChimes.range.set(3);
	preset3.numChimes.increment.set(1);
	
	for(int i = 0; i < 2; i ++){
		preset3.fParams[CH_FREQ_A + i].initVal.set(MIDI_MIN + MIDI_RANGE/2);
		preset3.fParams[CH_FREQ_A + i].dType = DT_NONE;
		preset3.fParams[CH_DECAY_A + i].initVal.set(1.8);
	}
	
	preset3.fParams[CH_PHASE].initVal.set(0);
	preset3.fParams[CH_PHASE].dType =  DT_SLICE;
	preset3.fParams[CH_PHASE].increment.set(b2_pi * 1.0f/64.0f);
	preset3.fParams[CH_PHASE].range.set(64);
	preset3.fParams[CH_SPEED].initVal.set(1.0);
	preset3.fParams[CH_LENGTH].initVal.set(2.0);
	
	mapDef freq;
	freq.mapType = MAP_1_TO_R;
	freq.inMap = CH_PHASE;
	freq.outMap = CH_FREQ_A;
	freq.outRange[0] = MIDI_MIN;
	freq.outRange[1] = MIDI_MIN + MIDI_RANGE;
	preset3.mapParams.push_back(freq);
	freq.outMap = CH_FREQ_B;
	preset3.mapParams.push_back(freq);
	
	mPresets.push_back(preset3);
	

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
		
	if(isSearching){
		chimeManager::drawSelected();
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
	
	if(isSearching){
		ofDrawBitmapString("mode: " + menuStrings[2], 20,20);
	}else{
		ofDrawBitmapString("mode: " + menuStrings[currentMode], 20,20);
	}
	
	
	if(isSearching){
		
		string mString = "macro: ";
		for(int i = 0; i < 4; i++){
			mString += chimeManager::getSearchName(searchMacro[i]);
			if(i < 3)mString += ", ";
		}
		ofDrawBitmapString(mString,300,20);
		
	}else{
		
		switch (currentMode) {
			case MT_ADD:
				ofDrawBitmapString("preset: " + mPresets[mCurrentPreset].name, 300,20);
				break;
			case MT_ADJUST:
				ofDrawBitmapString("modType: " + chimeManager::getModName(currentMod) , 300,20);
				break;
				
			default:
				break;
		}
		
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
		chimeManager::drawSample();
		chimeManager::drawSearchEngine(searchMacro[macroStage],dragDist, dragAngle);
		
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
			chimeManager::beginSearch();
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
			mDisplayString = chimeManager::continueSearch(searchMacro[macroStage], mouseDownPos, mouseDragPos, dragDist, dragAngle);
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
			macroStage = min(macroStage + 1,3);
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
			break;
		}
	
	}
	
	if(currentMode == MT_ADD){
		if(key == OF_KEY_UP)mCurrentPreset = min(mCurrentPreset + 1, (int)mPresets.size() -1);
		if(key == OF_KEY_DOWN)mCurrentPreset = max(mCurrentPreset - 1,0);
	}
	
	if(isSearching){
		
		if(key == OF_KEY_UP)searchMacro[0] = min(searchMacro[0] + 1, (int)SEARCH_COUNT -1);
		if(key == OF_KEY_DOWN)searchMacro[0] = max(searchMacro[0] - 1,0);

	}
	
	if(currentMode == MT_ADJUST){
		
		if(key == OF_KEY_UP)currentMod = min(currentMod + 1, (int)MOD_COUNT -1);
		if(key == OF_KEY_DOWN)currentMod = max(currentMod - 1,0);
		
	}
	
	
	if(key == ' '){
		
		if(!isSearching){
			macroStage = 0;
			isSearching = true;
			chimeManager::newSearch();
		}
			
		
	}
	
	if(key == 'x')chimeManager::shiftFocalPoint(0.0f);
	if(key == 'z')chimeManager::shiftFocalPoint(1.0f);
	
	if(key == 'a')chimeManager::shiftZPos(0.0f);
	if(key == 's')chimeManager::shiftZPos(1.0f);
	
	if(key == 'n')chimeManager::incrementMod(-1);
	if(key == 'm')chimeManager::incrementMod(1);
	
	
	if(key == 'i')chimeManager::clearSelBanks();
	if(key == 'o')chimeManager::deleteSelBank();
	if(key == 'p')chimeManager::saveSelBank();
	if(key == '[')chimeManager::switchSelBank(-1);
	if(key == ']')chimeManager::switchSelBank(1);
	
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
	
	if(!isSearching){

		switch (currentMode) {
				
			case MT_ADD:currentAction = AT_ADD;break;
			case MT_ADJUST:currentAction = AT_ADJUST;break;
				
			default:
				break;
		}
		
	}else{
	
		currentAction  = AT_SELECT;
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