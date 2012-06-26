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
	
	ofxOscMessage m;
	m.setAddress("/init");
	sender.sendMessage(m);

	ofEnableSmoothing();
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; //ofRandom(0,b2_pi);
		cd.anchorPos = myUtils::add(b2Vec2(0,-4.5), 
									myUtils::mul(b2Vec2(0,0.2), (float)i)
									);
		
		cd.freq = (float)i/NUM_CHIMES;
		
		int p = 6; //ofRandom(1,6);
		
		for(int j = 0; j < p; j++){
			
			cd.pivots.push_back(pivotDef(b2Vec2(0.2,0.5),0.02 * (j+1)));
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
	
	
}




//--------------------------------------------------------------
void testApp::draw(){
	
	mCam.begin();
	
	glPushMatrix();
	glScalef(scale, scale, 0);
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawAnchor(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawPivots(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawStem(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawSensors(*it);
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawHammer(*it);
	
	
	glPopMatrix();
	
	mCam.end();
	
	
	ofSetColor(0);
	ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate(),2), 20,20);

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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