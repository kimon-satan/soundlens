#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	scale = 80;
	
	mCam.setNearClip(0);
	mCam.setFarClip(2000);
	mCam.setPosition(0,0,800);
	mCam.lookAt(ofVec3f(0,0,0), ofVec3f(0,1,0));
	
	sender.setup(HOST,PORT);
	
	chimeUpdater::setOscSender(&sender);
	chimeRenderer::loadSprites();
	
	ofxOscMessage m;
	m.setAddress("/init");
	sender.sendMessage(m);

	ofEnableSmoothing();
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 5.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; 
		cd.anchorPos =  ofVec2f(-5,0) + ofVec2f(0.4,0)* (float)i;
		cd.offset = 0;					
		cd.freq[0] = (float)(i+1)/NUM_CHIMES;
		cd.freq[1] = 1 - (float)(i+1)/NUM_CHIMES;
		cd.decay[0] = 0.5;
		cd.decay[1] = 1.5;
		cd.rSpeed = 0.2;
		cd.colors[0] = ofColor(255,0,0);
		cd.colors[1] = ofColor(0,255,0);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		
		
		int p = 3; //ofRandom(1,6);
		
		for(int j = 0; j < p; j++){
			
			pivotDims pd;
			
			pd.d = 1;
			pd.iAngle = 0.25 * b2_pi;
			pd.rSpeed = 0.05 * (j+1);
			pd.cRot = pd.iAngle;			
			cd.pivots.push_back(pd);
			
		}


		ofPtr<chime> c = chimeFactory::createChime(cd);

		c->setCollisionListener(mListener);

		mChimes.push_back(c);
	}
	
	
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeUpdater::update(*it);
	chimeUpdater::step();
	
	
}


//--------------------------------------------------------------
void testApp::draw(){
	
	mCam.begin();
	
	glPushMatrix();
	glScalef(scale, scale, 0);
	
	//ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableAlphaBlending();
	//for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawAnchor(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawPivots(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawStem(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawHammer(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawSensors(*it);
	
	//ofDisableBlendMode();
	ofDisableAlphaBlending();
	
	glPopMatrix();
	
	mCam.end();
	
	
	ofSetColor(0);
	ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate(),2), 20,20);

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'x'){
		
		int count = 0;
		for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
			ofVec2f v(0.005,0); 
			v *= count;
			v += ofVec2f(-0.005,0) * NUM_CHIMES/2;
			chimeUpdater::moveView(*it, v);
			count += 1;
		}
	}
	
	if(key == 'z'){
		
		int count = 0;
		for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
			ofVec2f v(-0.005,0); 
			v *= count;
			v += ofVec2f(0.005,0) * NUM_CHIMES/2;
			chimeUpdater::moveView(*it, v);
			count += 1;
		}
	}
	

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	float b = ofMap(x, 0, ofGetScreenWidth(), 0,1, true);
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		
		(*it)->setBlur(b);
		
	}
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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


}