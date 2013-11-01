#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(false);
	ofSetFrameRate(TARGET_FRAME);
	ofSetCircleResolution(100);

	scale = 80;

	//mCam.cacheMatrices(true);
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
	currentMod = MSORT_GATHER; //need to change name of this

	mCurrentCopier= 0;
	cSearchPreset = 0;
	cMacroStage = 0;
	mCurrentBank = 0;

	isMouseDown = false;

	loadPresets();
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


void testApp::loadPresets(){

	loadSearchPresets();
	loadCopyPresets();


}

void testApp::loadSearchPresets(){

	ofxXmlSettings XML;

	if(XML.loadFile("searches.xml")){


		if(XML.pushTag("SOUNDLENS")){

			if(XML.pushTag("SEARCHES")){

				int nPresets = XML.getNumTags("PRESET");

				for(int i = 0; i < nPresets; i ++){

					if(XML.pushTag("PRESET", i)){

						searchPreset sp;

						sp.name = XML.getValue("NAME", "default");

						int n_aItems = XML.getNumTags("A_ITEM");

						for(int j = 0; j < n_aItems; j++){

							if(XML.pushTag("A_ITEM", j)){

								string st = XML.getValue("N", "position");
								int si = chimeManager::getSearchIndex(st);
								sp.autoMacro.push_back(si);
								ofVec2f a_set;
								a_set.x = XML.getValue("V1", 0);
								a_set.y = XML.getValue("V2", 0);
								sp.autoSettings.push_back(a_set);

								XML.popTag();
							}

						}


						int n_mItems = XML.getNumTags("M_ITEM");

						for(int j = 0; j < n_mItems; j++){

							string st = XML.getValue("M_ITEM", "position", j);
							int si = chimeManager::getSearchIndex(st);
							sp.manualMacro.push_back(si);


						}


						searchPresets.push_back(sp);

						XML.popTag();
					}


				}


				XML.popTag();
			}


			XML.popTag();

		}


	}else{

		cout << "searches.xml file not found \n";

	}



}

void testApp::loadCopyPresets(){

	ofxXmlSettings XML;

	if(XML.loadFile("copiers.xml")){


		if(XML.pushTag("SOUNDLENS")){

			if(XML.pushTag("COPIERS")){

				int nPresets = XML.getNumTags("PRESET");

				for(int i = 0; i < nPresets; i ++){

					if(XML.pushTag("PRESET", i)){

						copyPreset cp;


						cp.name = XML.getValue("NAME", "default");

						int nItems = XML.getNumTags("ITEM");

						for(int j = 0; j < nItems; j++){

							if(XML.pushTag("ITEM", j)){

								copierSpec cs;

								string cp_t = XML.getValue("CTYPE", "transpose");
								string cp_p = XML.getValue("PARAM", "freq");

								cs.copierType = chimeManager::getCopierIndex(cp_t);
								cs.chParam = chime::getChParamIndex(cp_p);

								if(XML.pushTag("P1")){


									cs.para1.set(XML.getValue("MIN",0.01)
												 ,XML.getValue("MAX",1.0),
												 chimeManager::getSetTypeIndex(XML.getValue("SET", "userB")));

									cs.para1.incr = XML.getValue("INC",0.01);

									XML.popTag();
								}

								if(XML.pushTag("P2")){

									cs.para2.set(XML.getValue("MIN",0.01)
												 ,XML.getValue("MAX",1.0),
												 chimeManager::getSetTypeIndex(XML.getValue("SET", "userB")));

									cs.para2.incr = XML.getValue("INC",0.01);


									XML.popTag();
								}

								cp.copiers.push_back(cs);
								XML.popTag();
							}


						}


						copyPresets.push_back(cp);

						XML.popTag();
					}


				}


				XML.popTag();
			}


			XML.popTag();

		}


	}else{

		cout << "copiers.xml file not found \n";

	}



}




void testApp::setupBanks(){


	bank apb;

	//allPresets
	apb.name = "allPresets";
	apb.copies = copyPresets;
	apb.searches = searchPresets;

	banks.push_back(apb);


	ofxXmlSettings XML;

	if(XML.loadFile("banks.xml")){

		if(XML.pushTag("SOUNDLENS")){

			if(XML.pushTag("BANKS")){

				int numPresets = XML.getNumTags("PRESET");

				for(int i = 0; i < numPresets; i++){

					if(XML.pushTag("PRESET", i)){

						bank tb;

						tb.name = XML.getValue("NAME", "default");

						int nSearches = XML.getNumTags("SEARCH");
						int nCopies = XML.getNumTags("COPY");

						for(int j = 0; j < nSearches; j++){

							string srch = XML.getValue("SEARCH", "",j);
							tb.searches.push_back(getSearchPreset(srch));

						}


						for(int j = 0; j < nCopies; j++){

							string cpy = XML.getValue("COPY", "",j);
							tb.copies.push_back(getCopyPreset(cpy));

						}

						banks.push_back(tb);

						XML.popTag();
					}

				}

				XML.popTag();
			}

			XML.popTag();
		}


	}


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
			chimeManager::drawModEngine(MSORT_SET_MULTI, dragDist, dragAngle);
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
				mDisplayString = chimeManager::continueMod(MSORT_SET_MULTI, mouseDownPos, mouseDragPos, dragDist, dragAngle);
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
				chimeManager::endMod(MSORT_SET_MULTI);
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

		if(key == OF_KEY_UP)currentMod = min(currentMod + 1, (int)MSORT_COUNT -2);
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
	if(key == OF_KEY_ALT)newSearch(true); //ctrl + space
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
	if(key == OF_KEY_TAB)isTab = true;

	for(int i=0; i < 10; i++)if(key == 48 + i)chimeManager::switchToBank(i, isTab);

	switch(key){
		case OF_KEY_F1:chimeManager::saveToBank(1);break;
		case OF_KEY_F2:chimeManager::saveToBank(2);break;
		case OF_KEY_F3:chimeManager::saveToBank(3);break; //£ doesn't work ?
		case OF_KEY_F4:chimeManager::saveToBank(4);break;
		case OF_KEY_F5:chimeManager::saveToBank(5);break;
		case OF_KEY_F6:chimeManager::saveToBank(6);break;
		case OF_KEY_F7:chimeManager::saveToBank(7);break;
		case OF_KEY_F8:chimeManager::saveToBank(8);break;
		case OF_KEY_F9:chimeManager::saveToBank(9);break;
		case OF_KEY_F10:chimeManager::saveToBank(0);break;
	}


	if(key == '[')chimeManager::incrHistory(-1);
	if(key == ']')chimeManager::incrHistory(1);


	if(key == 'D')chimeRenderer::isDrawPivots = !chimeRenderer::isDrawPivots;
	if(key == OF_KEY_BACKSPACE)chimeManager::deleteHiddenChimes();

	if(key == 'F')ofToggleFullscreen();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if(key == ' ' || key == 'n'|| key == 'm' || key == OF_KEY_ALT){
		currentMode = MT_COPY;
	}

	if(key == OF_KEY_TAB)isTab = false;

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
