#include "testApp.h"


bool compareZpos(ofPtr<chime> a, ofPtr<chime> b){return (a->getZpos() < b->getZpos());}

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(TARGET_FRAME);

	scale = 80;
	
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

	ofEnableSmoothing();
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	ofSetRectMode(OF_RECTMODE_CENTER);
		

	
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



//--------------------------------------------------------------
void testApp::draw(){
	
	GLfloat fogColor[4]= {1.0f, 1.0f, 1.0f, 1.0f}; 
	
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
		
	ofDisableBlendMode();
	
	glPopMatrix();
	
	glDisable(GL_FOG);    
	
	mCam.end();
	
	
	ofSetColor(0);
	ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate(),2), 20,20);

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
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
	
	if(key == ' ')chimeManager::selectNewGroup();
	
	
	if(key == 'x')chimeManager::shiftFocalPoint(0.0f);
	if(key == 'z')chimeManager::shiftFocalPoint(1.0f);
		
	
	if(key == 'a')chimeManager::shiftZPos(0.0f);
	if(key == 's')chimeManager::shiftZPos(1.0f);
		

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

	ofxOscMessage m;
	m.setAddress("/exit");
	sender.sendMessage(m);

}