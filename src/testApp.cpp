#include "testApp.h"


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
	
	isSearching = false;
	cSearchPreset = 0;
	cMacroStage = 0;
	
	setupSearchPresets();
	
	menuStrings.push_back("add");
	menuStrings.push_back("adjust");
	menuStrings.push_back("select");
	
}


void testApp::setupPresets(){
	
	groupPreset preset1;
	
	preset1.name = "single";
	preset1.numChimes.setInitVal(1);
	

	preset1.fParams[CH_FREQ].setInitVal(MIDI_MIN + MIDI_RANGE/2);
	preset1.fParams[CH_FREQ].setDType(DT_NONE);
	preset1.fParams[CH_DECAY].setInitVal(1.8);
	
	
	preset1.fParams[CH_PHASE].setInitVal(b2_pi);
	preset1.fParams[CH_PHASE].setDType(DT_FLAT);
	preset1.fParams[CH_PHASE].setVal(DD_UNIT, b2_pi * 1.0f/64.0f);
	preset1.fParams[CH_PHASE].setVal(DD_RNG, b2_pi * 2);
	preset1.fParams[CH_SPEED].setInitVal(1.0);
	preset1.fParams[CH_LENGTH].setInitVal(2.0);
	
	preset1.fParams[CH_PIV_NUM].setInitVal(0);
	
	preset1.fParams[CH_PIV_LGTH].setInitVal(2.0);
	
	preset1.fParams[CH_PIV_PH_MUL].setInitVal(1);
	preset1.fParams[CH_PIV_SPD_SKEW].setInitVal(0);
	
	mPresets.push_back(preset1);
	
	groupPreset preset2;
	
	preset2.name = "multiple";
	preset2.numChimes.setInitVal(20);
	preset2.numChimes.setDType(DT_NONE);

	preset2.fParams[CH_FREQ].setInitVal(MIDI_MIN + MIDI_RANGE/2);
	preset2.fParams[CH_FREQ].setDType(DT_FLAT);
	preset2.fParams[CH_FREQ].setVal(DD_RNG, 24);
	preset2.fParams[CH_FREQ].setVal(DD_UNIT, 3);
	preset2.fParams[CH_DECAY].setInitVal(1.8);
	
	
	preset2.fParams[CH_PHASE].setInitVal(0);
	preset2.fParams[CH_PHASE].setDType(DT_SLICE);
	preset2.fParams[CH_PHASE].setVal(DD_UNIT, 0);
	preset2.fParams[CH_PHASE].setVal(DD_RNG, b2_pi);
	preset2.fParams[CH_SPEED].setInitVal(0.5);
	preset2.fParams[CH_LENGTH].setInitVal(2.0);
	
	preset2.fParams[CH_PIV_NUM].setInitVal(2);
	preset2.fParams[CH_PIV_LGTH].setInitVal(4);
	preset2.fParams[CH_PIV_SPD_SKEW].setInitVal(0);
	preset2.fParams[CH_PIV_PH_MUL].setInitVal(1);
	
	mPresets.push_back(preset2);
	
	
	groupPreset preset3;
	
	preset3.name = "multipleClimber";
	preset3.numChimes.setInitVal(10);
	preset3.numChimes.setDType(DT_FLAT);
	preset3.numChimes.setVal(DD_RNG, 3);
	
	preset3.fParams[CH_FREQ].setInitVal(MIDI_MIN + MIDI_RANGE/2);
	preset3.fParams[CH_FREQ].setDType(DT_NONE);
	preset3.fParams[CH_DECAY].setInitVal(1.8);
	
	preset3.fParams[CH_PHASE].setInitVal(0);
	preset3.fParams[CH_PHASE].setDType(DT_SLICE);
	preset3.fParams[CH_PHASE].setVal(DD_RNG, b2_pi);
	preset3.fParams[CH_SPEED].setInitVal(1.0);
	preset3.fParams[CH_LENGTH].setInitVal(2.0);
	preset3.fParams[CH_PIV_NUM].setInitVal(0);
	
	mapDef freq;
	freq.mapType = MAP_1_TO_R;
	freq.inMap = CH_PHASE;
	freq.outMap = CH_FREQ;
	freq.outRange[0] = MIDI_MIN;
	freq.outRange[1] = MIDI_MIN + MIDI_RANGE;
	preset3.mapParams.push_back(freq);
	
	mPresets.push_back(preset3);
	
	groupPreset preset4;
	
	preset4.name = "multipleSpeeds";
	preset4.numChimes.setInitVal(4);
	preset4.numChimes.setDType(DT_NONE);
	preset4.numChimes.setVal(DD_RNG, 3);
	preset4.numChimes.setVal(DD_UNIT, 1);
	

	preset4.fParams[CH_FREQ].setInitVal(MIDI_MIN,MIDI_MIN + MIDI_RANGE, SET_USER_B); //need a method to set increment
	preset4.fParams[CH_FREQ].setVal(DD_UNIT, 1);
	preset4.fParams[CH_FREQ].setVal(DD_RNG, 6,12,SET_USER_A);
	preset4.fParams[CH_FREQ].setDType(DT_SLICE);
	preset4.fParams[CH_DECAY].setInitVal(0.5);
	
	preset4.fParams[CH_PHASE].setInitVal(0,b2_pi/2,SET_USER_B);
	preset4.fParams[CH_PHASE].setDType( DT_NONE);
	preset4.fParams[CH_SPEED].setInitVal(0.2);
	preset4.fParams[CH_SPEED].setDType(DT_SLICE);
	preset4.fParams[CH_SPEED].setVal(DD_RNG, 1);
	preset4.fParams[CH_SPEED].setVal(DD_UNIT, 0.3);
	preset4.fParams[CH_LENGTH].setInitVal(2.0);
	preset4.fParams[CH_PIV_NUM].setInitVal(0);
	
	preset4.fParams[CH_PIV_LGTH].setInitVal(2.0);
	preset4.fParams[CH_PIV_NUM].setInitVal(1);
	preset4.fParams[CH_PIV_PH_MUL].setInitVal(0.25);
	preset4.fParams[CH_PIV_SPD_SKEW].setInitVal(0);
	
	mPresets.push_back(preset4);
	
}

void testApp::setupSearchPresets(){

	searchPreset sp3;
	
	sp3.name = "allSearch";
	sp3.manualMacro.push_back(SEARCH_POSITION);
	
	searchPresets.push_back(sp3);
	
	searchPreset sp1;
	
	sp1.name = "surfaceSearch";
	sp1.autoMacro.push_back(SEARCH_BPF_FDIST);
	sp1.autoSettings.push_back(ofVec2f(0.2,0.1));
	sp1.manualMacro.push_back(SEARCH_POSITION);
	
	searchPresets.push_back(sp1);
	
	searchPreset sp2;
	
	sp2.name = "pulseSearch";
	sp2.autoMacro.push_back(SEARCH_MATCH_SPEED);
	sp2.autoSettings.push_back(ofVec2f(0,0));
	sp2.manualMacro.push_back(SEARCH_FUND_PHASE);
	sp2.manualMacro.push_back(SEARCH_QUANT_PHASE);
	
	searchPresets.push_back(sp2);

}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	chimeManager::update();

}

void testApp::handleMessages(){

	/*while (receiver.hasWaitingMessages()) {
		
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if ( m.getAddress() == "/focalPoint" ){
			
			chimeManager::shiftFocalPoint(m.getArgAsFloat(0));
			
			
		}else if ( m.getAddress() == "/zPos" ){
			
			chimeManager::shiftZPos(m.getArgAsFloat(0));
			
		}else if ( m.getAddress() == "/switchGroup" ){
			
			//chimeManager::selectNewGroup();
			
		}
			
		
		
	}*/
	
	//not using iphone control

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
		chimeManager::drawSample();
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
		
		string mString = "preset: ";
		
		mString += searchPresets[cSearchPreset].name + " | ";
		
		for(int i = 0; i < searchPresets[cSearchPreset].autoMacro.size(); i++){
			mString += chimeManager::getSearchName(searchPresets[cSearchPreset].autoMacro[i]);
			mString += ", ";
		}
		
		mString += " / ";
		
		for(int i = 0; i < searchPresets[cSearchPreset].manualMacro.size(); i++){
			mString += chimeManager::getSearchName(searchPresets[cSearchPreset].manualMacro[i]);
			mString += ", ";
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
	
	if(currentAction == AT_ADD){
	
		chimeManager::drawPreviewChimes();
		ofSetColor(100);
		ofLine(mouseDownPos.x, mouseDownPos.y, mouseDragPos.x, mouseDragPos.y);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
		
	}
	
	if(currentAction == AT_SELECT){
		
		chimeManager::drawTmpSelected();
		chimeManager::drawSearchEngine(searchPresets[cSearchPreset].manualMacro[cMacroStage],dragDist, dragAngle);
		
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
			mDisplayString = chimeManager::continueSearch(searchPresets[cSearchPreset].manualMacro[cMacroStage],
														  mouseDownPos, mouseDragPos, dragDist, dragAngle);
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
			cMacroStage = min(cMacroStage + 1,(int)searchPresets[cSearchPreset].manualMacro.size()-1);
			break;
		

		case AT_ADJUST:
			chimeManager::endMod(currentMod);
			break;
			
		default:
			break;
	}
	
	currentAction = AT_NONE;
	
	
	
}

void testApp::newSearch(bool useResults){

	if(!isSearching){
		cMacroStage = 0;
		isSearching = true;
		chimeManager::newSearch(useResults);
		
		for(int i = 0; i < searchPresets[cSearchPreset].autoMacro.size(); i++){
			chimeManager::beginSearch();
			chimeManager::continueSearch(searchPresets[cSearchPreset].autoMacro[i],
										 mouseMovePos,
										 mouseMovePos,
										 searchPresets[cSearchPreset].autoSettings[i].x, 
										 searchPresets[cSearchPreset].autoSettings[i].y 
										 );
			chimeManager::endSearch();
			
			
		}
	}

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
		
		if(key == OF_KEY_UP)cSearchPreset = min(cSearchPreset + 1, (int)searchPresets.size() - 1);
		if(key == OF_KEY_DOWN)cSearchPreset = max(cSearchPreset - 1,0);

	}
	
	if(currentMode == MT_ADJUST){
		
		if(key == OF_KEY_UP)currentMod = min(currentMod + 1, (int)MOD_COUNT -1);
		if(key == OF_KEY_DOWN)currentMod = max(currentMod - 1,0);
		
	}
	
	
	if(key == ' ')newSearch(false);
	if(key == OF_KEY_RETURN)newSearch(true);
	
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
	
	if(key == 'D')chimeRenderer::isDrawPivots = !chimeRenderer::isDrawPivots;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if(key == ' ' || key == OF_KEY_RETURN){
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