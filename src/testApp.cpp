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
	
	tuningEngine::setSender(&sender);
	tuningEngine::setReciever(&receiver);
	
	ofxOscMessage m;
	m.setAddress("/init");
	sender.sendMessage(m);
	
	tuningEngine::requestScale();

	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);

	currentMode = MT_COPY;
	currentMod = MOD_GATHER; //need to change name of this
	
	mCurrentCopier= 0;
	cSearchPreset = 0;
	cMacroStage = 0;
	mCurrentBank = 0;
	
	isMouseDown = false;
	
	setupSearchPresets();
	setupCopyPresets();
	setupBanks();
	
	chimeManager::createInitialChime();
	
	menuStrings.push_back("copy");
	menuStrings.push_back("search");
	menuStrings.push_back("move");
	menuStrings.push_back("pivot");
	
	currentAction = AT_NONE;
	isLastActionCopy = false;
	
	isTab = false;
	mDCount = 0;
	
}



void testApp::setupSearchPresets(){

	searchPreset sp1;
	
	sp1.name = "position";
	sp1.manualMacro.push_back(SEARCH_POSITION);
	sp1.manualMacro.push_back(SEARCH_BPF_FDIST);
	
	searchPresets.push_back(sp1);
	
	
	searchPreset sp2;
	
	sp2.name = "phaseFund";
	sp2.manualMacro.push_back(SEARCH_FUND_PHASE);
	sp2.manualMacro.push_back(SEARCH_UNIQUE);
	sp2.manualMacro.push_back(SEARCH_QUANT_PHASE);
	
	searchPresets.push_back(sp2);
	
	
	searchPreset sp4;
	
	sp4.name = "matchUnique";
	sp4.manualMacro.push_back(SEARCH_MATCH_MULTI);
	sp4.manualMacro.push_back(SEARCH_UNIQUE);
	
	searchPresets.push_back(sp4);
	
	
	searchPreset sp5;
	
	sp5.name = "freqSieve";
	sp5.manualMacro.push_back(SEARCH_SIEVE);
	sp5.manualMacro.push_back(SEARCH_UNIQUE);
	
	searchPresets.push_back(sp5);
	
	
	searchPreset sp5a;
	
	sp5a.name = "fundSieve";
	
	sp5a.manualMacro.push_back(SEARCH_FUND_PHASE);
	sp5a.manualMacro.push_back(SEARCH_SIEVE);
	
	searchPresets.push_back(sp5a);
	
	searchPreset sp6;
	
	sp6.name = "unique2";
	
	sp6.manualMacro.push_back(SEARCH_UNIQUE);
	sp6.manualMacro.push_back(SEARCH_UNIQUE);
	
	searchPresets.push_back(sp6);
	
	

	

}

void testApp::setupCopyPresets(){

	copierSpec cs;
	copyPreset cp;
	
	//---------------------------
	
	cp.name = "p trans";
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0.01,1.0,SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	//---------------------------
	
	cp.name = "fp trans1";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0.0,1.0,SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);	
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-6,6,SET_MAP_Y);
	cs.para1.incr = 0.5;
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	//---------------------------
	
	cp.name = "fp trans2";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0.0,1.0,SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);	
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-12,12,SET_USER_A);
	cs.para1.incr = 0.5;
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	//--------------------------------------
	
	cp.name = "fp transMut";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-6,6,SET_USER_A);
	cs.para1.incr = 0.5;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0,1,SET_USER_B);
	cs.para1.incr = 0.05;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_MUTATE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0.5);
	cs.para1.incr = 0.01;
	cs.para2.set(0.25);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	//--------------------------------------
	
	cp.name = "f transMut";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-6,6,SET_USER_B);
	cs.para1.incr = 0.5;
	cp.copiers.push_back(cs);

	
	cs.copierType = CP_MUTATE;
	cs.chParam = CH_FREQ;
	cs.para1.set(0,7,SET_USER_A);
	cs.para1.incr = 0.5;
	cs.para2.set(0.35);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	//--------------------------------------
	
	cp.name = "fp transSieve";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-12,12,SET_USER_A);
	cs.para1.incr = 1.0;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0.0,1.0,SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_SIEVE;
	cs.para1.set(0);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	//--------------------------------------
	
	cp.name = "f transSieve";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-12,12,SET_USER_A);
	cs.para1.incr = 1.0;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_SIEVE;
	cs.para1.set(0,12,SET_USER_B);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	//--------------------------------------
	
	cp.name = "fs transSieve";
	cp.copiers.clear();
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_FREQ;
	cs.para1.set(-12,12,SET_USER_A);
	cs.para1.incr = 1.0;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_TRANSPOSE;
	cs.chParam = CH_SPEED;
	cs.para1.set(0.1,2.0,SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_SIEVE;
	cs.para1.set(0);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	
	//-----------------------------------------
	
	cp.name = "p resTrans";
	cp.copiers.clear();
	

	cs.chParam = CH_PHASE;
	cs.copierType = CP_RESIZE;
	cs.para1.set(0.25, 2.0, SET_USER_A);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	cs.chParam = CH_PHASE;
	cs.copierType = CP_TRANSPOSE;
	cs.para1.set(0, 1, SET_USER_B);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	
	//-----------------------------------------
	
	cp.name = "fp arrTrans";
	cp.copiers.clear();
	
	cs.copierType = CP_ARRANGE;
	cs.chParam = CH_FREQ;
	cs.para1.set(0,3,SET_USER_B);
	cs.para1.incr = 1.0;
	cs.para2.set(1);
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_ARRANGE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0,3,SET_USER_B);
	cs.para1.incr = 1.0;
	cs.para2.set(1);
	cp.copiers.push_back(cs);
	
	cs.chParam = CH_PHASE;
	cs.copierType = CP_TRANSPOSE;
	cs.para1.set(0, 1, SET_USER_A);
	cs.para1.incr = 0.01;
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	//-----------------------------------------
	
	cp.name = "fp arrSieve";
	cp.copiers.clear();
	
	cs.copierType = CP_ARRANGE;
	cs.chParam = CH_FREQ;
	cs.para1.set(0,3,SET_USER_B);
	cs.para1.incr = 1.0;
	cs.para2.set(1,20,SET_USER_A);
	cs.para2.incr = 1.0;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_ARRANGE;
	cs.chParam = CH_PHASE;
	cs.para1.set(0,3,SET_USER_B);
	cs.para1.incr = 1.0;
	cs.para2.set(1,20,SET_USER_A);
	cs.para2.incr = 1.0;
	cp.copiers.push_back(cs);
	
	cs.copierType = CP_SIEVE;
	cs.para1.set(0);
	cp.copiers.push_back(cs);
	
	copyPresets.push_back(cp);
	
	
	
}

void testApp::setupBanks(){

	
	bank tb;
	
	//allPresets
	tb.name = "allPresets";
	tb.copies = copyPresets;
	tb.searches = searchPresets;
	
	banks.push_back(tb);
	
	
	//------------------------------------------------------
	
	tb.copies.clear();
	tb.searches.clear();
	
	tb.name = "build";
	
	tb.searches.push_back(getSearchPreset("position"));
	tb.searches.push_back(getSearchPreset("phaseFund"));
	
	tb.copies.push_back(getCopyPreset("fp trans1"));
	tb.copies.push_back(getCopyPreset("fp transMut"));
	tb.copies.push_back(getCopyPreset("fp trans2"));
	
	banks.push_back(tb);

	
	//--------------------------------------------------------
	
	tb.copies.clear();
	tb.searches.clear();
	
	tb.name = "arranging";
	
	tb.searches.push_back(getSearchPreset("position"));
	tb.searches.push_back(getSearchPreset("phaseFund"));


	//for arranging copying
	
	tb.copies.push_back(getCopyPreset("p trans"));
	tb.copies.push_back(getCopyPreset("fp arrTrans"));
	tb.copies.push_back(getCopyPreset("fp arrSieve"));
	
	
	banks.push_back(tb);
	
	//--------------------------------------------------------
	
	tb.copies.clear();
	tb.searches.clear();
	
	tb.name = "wheels";
	
	tb.searches.push_back(getSearchPreset("position"));
	tb.searches.push_back(getSearchPreset("phaseFund"));
	tb.searches.push_back(getSearchPreset("fundSieve"));
	tb.searches.push_back(getSearchPreset("freqSieve"));
	tb.searches.push_back(getSearchPreset("unique2"));
	
	
	//for arranging copying
	
	tb.copies.push_back(getCopyPreset("fp trans2"));
	tb.copies.push_back(getCopyPreset("fp transSieve"));
	tb.copies.push_back(getCopyPreset("f transMut"));
	
	banks.push_back(tb);
	
	//--------------------------------------------------------
	
	tb.copies.clear();
	tb.searches.clear();
	
	tb.name = "polyLayers";
	
	tb.searches.push_back(getSearchPreset("matchUnique"));
	tb.searches.push_back(getSearchPreset("unique2"));
	tb.searches.push_back(getSearchPreset("position"));

	tb.copies.push_back(getCopyPreset("fp arrSieve"));
	tb.copies.push_back(getCopyPreset("fp transSieve"));
	tb.copies.push_back(getCopyPreset("f transSieve"));
	tb.copies.push_back(getCopyPreset("fs transSieve"));
	tb.copies.push_back(getCopyPreset("p resTrans"));
	
	
	banks.push_back(tb);
	
	
	

}

searchPreset testApp::getSearchPreset(string name){
	
	for(int i = 0; i < searchPresets.size(); i++)if(searchPresets[i].name == name)return searchPresets[i];
	
}

copyPreset testApp::getCopyPreset(string name){

	for(int i = 0; i < copyPresets.size(); i++)if(copyPresets[i].name == name)return copyPresets[i];
	

}

//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	chimeManager::update();
	tuningEngine::handleMessages();
	
	if(isMouseDown){
		continueAction();
		mDCount += 1;
	}

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
	glFogf(GL_FOG_DENSITY, 0.05f);              
	glHint(GL_FOG_HINT, GL_NICEST);       
	glFogf(GL_FOG_START, 800.0f);           
	glFogf(GL_FOG_END, 825.0f);               
	glEnable(GL_FOG);     
	
	
	glPushMatrix();
	glScalef(scale, scale, 1);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	chimeManager::draw();
		
	if(currentMode == MT_SEARCH){
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

	

	ofDrawBitmapString("mode: " + menuStrings[currentMode], 20,20);
	ofDrawBitmapString("preset: " + banks[mCurrentBank].name, 150,20);
	
	if(currentMode == MT_SEARCH){
		
		string mString = "macro: ";
		
		mString += banks[mCurrentBank].searches[cSearchPreset].name + " | ";
		
		for(int i = 0; i < banks[mCurrentBank].searches[cSearchPreset].autoMacro.size(); i++){
			mString += chimeManager::getSearchName(banks[mCurrentBank].searches[cSearchPreset].autoMacro[i]);
			mString += ", ";
		}
		
		mString += " / ";
		
		for(int i = 0; i < banks[mCurrentBank].searches[cSearchPreset].manualMacro.size(); i++){
			mString += chimeManager::getSearchName(banks[mCurrentBank].searches[cSearchPreset].manualMacro[i]);
			mString += ", ";
		}
		
		
		ofDrawBitmapString(mString,350,20);
		
	}else{
		
		switch (currentMode) {
			case MT_COPY:
				ofDrawBitmapString("copier: " + banks[mCurrentBank].copies[mCurrentCopier].name, 350,20);
				break;
			case MT_MOVE:
				ofDrawBitmapString("moveType: " + chimeManager::getModName(currentMod) , 350,20);
				break;
			case MT_PIVOT:
				ofDrawBitmapString("adjustPivots: " , 350,20);
				break;
			
				
			default:
				break;
		}
		
	}
	
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(),2), 1150,20);
	
	ofDrawBitmapString("sieve: " + tuningEngine::getCScaleName(), 800, 20);
	
	//for debugging
	/*ofSetColor(100);
	ofNoFill();
	ofRect(50,ofGetScreenHeight() - 50, ofGetScreenWidth()- 100, 30);
	float fp = ofMap(chimeUpdater::getFocalPoint(), 0, 2, 50, ofGetScreenWidth() - 50, true);
	ofRect( fp ,ofGetScreenHeight() - 50, 20, 30);*/
	
}


void testApp::drawActions(){
	
	ofEnableSmoothing();
	
	if(currentAction == AT_ADD){
	
		chimeManager::drawPreviewChimes();
		ofSetColor(100);
		chimeManager::drawCopyEngine(dragDist, dragAngle);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
		
	}
	
	if(currentAction == AT_SELECT){
		
		chimeManager::drawTmpSelected();
		chimeManager::drawSearchEngine(banks[mCurrentBank].searches[cSearchPreset].manualMacro[cMacroStage],dragDist, dragAngle);
		
		ofSetColor(100);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
		
		
	}
	
			
	if(currentAction == AT_ADJUST){
	
		chimeManager::drawSelected();
		if(currentMode != MT_PIVOT){
			chimeManager::drawModEngine(currentMod, dragDist, dragAngle);
		}else{
			chimeManager::drawModEngine(MOD_SET_MULTI, dragDist, dragAngle);
		}
		
		ofSetColor(100);
		ofDrawBitmapString(mDisplayString, mouseDownPos.x + 0.5, mouseDownPos.y + 0.5);
	}
			
	
	ofDisableSmoothing();


}

void testApp::beginAction(){

	if(isLastActionCopy){
		isLastActionCopy = false;
		chimeManager::clearAllMods();
	}	

	
	switch (currentAction) {
		
		case AT_ADD:
			chimeManager::beginCopy(banks[mCurrentBank].copies[mCurrentCopier]);
			break;
			
		case AT_SELECT:
			chimeManager::beginSearch();
			break;
			
		case AT_ADJUST:
			chimeManager::beginMod(isRM);
			break;
			
		default:
			break;
	}

}

void testApp::continueAction(){
	
	switch (currentAction) {
		case AT_ADD:
			mDisplayString = chimeManager::continueCopy(mouseDownPos, mouseDragPos, dragDist, dragAngle, isRM);
			break;
			
		case AT_SELECT:
			mDisplayString = chimeManager::continueSearch(banks[mCurrentBank].searches[cSearchPreset].manualMacro[cMacroStage],
														  mouseDownPos, mouseDragPos, dragDist, dragAngle);
			break;
			
		case AT_ADJUST:
			if(currentMode != MT_PIVOT){
				mDisplayString = chimeManager::continueMod(currentMod, mouseDownPos, mouseDragPos, dragDist, dragAngle);
			}else{
				mDisplayString = chimeManager::continueMod(MOD_SET_MULTI, mouseDownPos, mouseDragPos, dragDist, dragAngle);
			}
			break;
			
		default:
			break;
	}

	
}

void testApp::endAction(){

	switch (currentAction) {
		case AT_ADD:
			chimeManager::endNewChimes();	
			isLastActionCopy = true;
			break;																
																				
		case AT_SELECT:
			chimeManager::endSearch(isRM);
			cMacroStage = min(cMacroStage + 1,(int)banks[mCurrentBank].searches[cSearchPreset].manualMacro.size()-1);
			break;
		

		case AT_ADJUST:
			if(currentMode != MT_PIVOT){
				chimeManager::endMod(currentMod);
			}else{
				chimeManager::endMod(MOD_SET_MULTI);
			}
			break;
			
		default:
			break;
	}
	
	currentAction = AT_NONE;
	
	
	
}

void testApp::newSearch(bool useResults){
	
	
	if(currentMode != MT_SEARCH){
		cMacroStage = 0;
		currentMode = MT_SEARCH;
		chimeManager::newSearch(useResults);
		
		for(int i = 0; i < banks[mCurrentBank].searches[cSearchPreset].autoMacro.size(); i++){
			chimeManager::beginSearch();
			chimeManager::continueSearch(banks[mCurrentBank].searches[cSearchPreset].autoMacro[i],
										 mouseMovePos,
										 mouseMovePos,
										 banks[mCurrentBank].searches[cSearchPreset].autoSettings[i].x, 
										 banks[mCurrentBank].searches[cSearchPreset].autoSettings[i].y 
										 );
			chimeManager::endSearch(false);
			
			
		}
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	
	if(currentMode == MT_SEARCH){
		
		if(key == OF_KEY_UP)cSearchPreset = min(cSearchPreset + 1, (int)banks[mCurrentBank].searches.size() - 1);
		if(key == OF_KEY_DOWN)cSearchPreset = max(cSearchPreset - 1,0);
		
	}else if(currentMode == MT_COPY){
		
		if(key == OF_KEY_UP)mCurrentCopier= min(mCurrentCopier+ 1, (int)banks[mCurrentBank].copies.size() - 1);
		if(key == OF_KEY_DOWN)mCurrentCopier= max(mCurrentCopier- 1,0);
		
	}else if(currentMode == MT_MOVE){
		
		if(key == OF_KEY_UP)currentMod = min(currentMod + 1, (int)MOD_COUNT -2);
		if(key == OF_KEY_DOWN)currentMod = max(currentMod - 1,0);
		
	}
	
	
	if(key == OF_KEY_LEFT){
		mCurrentBank = max(mCurrentBank - 1, 0);
		currentMod = 0;
		mCurrentCopier = 0;
		cSearchPreset = 0;
	}
	
	if(key == OF_KEY_RIGHT){
		mCurrentBank = min(mCurrentBank +1, (int)banks.size()-1);
		currentMod = 0;
		mCurrentCopier = 0;
		cSearchPreset = 0;
	}
	
	if(key == ' ')newSearch(false);
	if(key == 0)newSearch(true); //ctrl + space
	if(key == 'm')currentMode = MT_MOVE;
	if(key == 'n')currentMode = MT_PIVOT;
	if(key == '.')chimeManager::incrementMod(1);
	if(key == ',')chimeManager::incrementMod(-1);
	
	
	if(key == 'z')chimeManager::shiftFocalPoint(-1.0f);
	if(key == 'x')chimeManager::shiftFocalPoint(1.0f);
	
	if(key == 'a')chimeManager::shiftZPos(-1.0f);
	if(key == 's')chimeManager::shiftZPos(1.0f);
	if(key == 'A')chimeManager::crossFade(-1.0f);
	if(key == 'S')chimeManager::crossFade(1.0f); 
	if(key == 'q')chimeManager::equalizeZPos();
	
	if(key == 't')tuningEngine::changeCScale(1);
	if(key == 'r')tuningEngine::changeCScale(-1);
	
	if(key == 'i')chimeManager::invertSelection();
	if(key == 9)isTab = true;
	
	for(int i=0; i < 10; i++)if(key == 48 + i)chimeManager::switchToBank(i, isTab);
	
	switch(key){
		case'!':chimeManager::saveToBank(1);break;
		case'@':chimeManager::saveToBank(2);break;
		case 163:chimeManager::saveToBank(3);break; //£ doesn't work ?
		case'$':chimeManager::saveToBank(4);break;
		case'%':chimeManager::saveToBank(5);break;
		case'^':chimeManager::saveToBank(6);break;
		case'&':chimeManager::saveToBank(7);break;
		case'*':chimeManager::saveToBank(8);break;
		case'(':chimeManager::saveToBank(9);break;
		case')':chimeManager::saveToBank(0);break;
	}
	
	
	if(key == '[')chimeManager::incrHistory(-1);
	if(key == ']')chimeManager::incrHistory(1);
	
	
	if(key == 'D')chimeRenderer::isDrawPivots = !chimeRenderer::isDrawPivots;
	if(key == OF_KEY_BACKSPACE)chimeManager::deleteHiddenChimes();
	
	if(key == 'F')ofToggleFullscreen();
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if(key == ' ' || key == 'n'|| key == 'm' || key == 0){
		currentMode = MT_COPY;
	}
	
	if(key == 9)isTab = false;
	
	if(key == 'r' || key == 't')tuningEngine::requestScale();
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	mouseMovePos = getZPlaneProjection(ofVec2f(x,y));
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if(mDCount > 10){
		mouseDragPos = getZPlaneProjection(ofVec2f(x,y));
		dragDist = ofMap(ofVec2f(mouseDragPos - mouseDownPos).length(),1,4,0,1,true);
		dragAngle = ofVec2f(mouseDownPos - mouseDragPos).angle(ofVec2f(0,-1));
		if(dragAngle < 0)dragAngle += 360;
		dragAngle = ofMap(dragAngle, 0,360, 0, 1);
	}
	
	
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	mouseDownPos = getZPlaneProjection(ofVec2f(x,y));
	
	mDCount = 0;
	
	isRM = (button > 0);
	
	switch (currentMode) {
			
		case MT_COPY:currentAction = AT_ADD;break;
		case MT_MOVE: case MT_PIVOT: currentAction = AT_ADJUST;break;
		case MT_SEARCH:currentAction  = AT_SELECT;break;
			
		default:
			break;
	}
		
	beginAction();
	isMouseDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	endAction();
	isMouseDown = false;
	
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