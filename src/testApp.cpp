#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(TARGET_FRAME);

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
	
	selCGroup = 0;

	for(int i = 0; i < 100; i++){
		vector<ofPtr<chime> > tc;
		renderList.push_back(tc);
	}
	
	setupChimes();
	
}

void testApp::setupChimes(){
	
	vector<ofPtr<chime> > tc;
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; 
		cd.anchorPos =  ofVec2f(0,-1);//ofVec2f(-5,0) + ofVec2f(0.4,0)* (float)i;
		cd.offset = 0;					
		cd.freq[0] = 0 + ((float)(i+1)/NUM_CHIMES) * 1.0;
		cd.freq[1] = 0 + (1 - (float)(i+1)/NUM_CHIMES) * 1.0;
		cd.decay[0] = 1.8;
		cd.decay[1] = 1.8;
		cd.rSpeed = 0.2;
		cd.colors[0] = ofColor(255,0,0);
		cd.colors[1] = ofColor(255,0,0);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		
		
		int p = 0; //ofRandom(1,6);
		
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
		
		tc.push_back(c);
	}
	
	
	mChimes.push_back(tc);
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.freq[0] = ofRandom(0.15,0.2);
		cd.freq[1] = cd.freq[0];
		cd.decay[0] = 1.0;
		cd.decay[1] = 1.0;
		cd.rSpeed = 0.4;
		cd.colors[0] = ofColor(0,0,100);
		cd.colors[1] = ofColor(0,0,100);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		
		
		int p = 0;//ofRandom(1,6);
		
		for(int j = 0; j < p; j++){
			
			pivotDims pd;
			
			pd.d = 1;
			pd.iAngle = ofRandom(0.1,0.25) * b2_pi;
			pd.rSpeed = 0.05 * (j+1);
			pd.cRot = pd.iAngle;			
			cd.pivots.push_back(pd);
			
		}
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		tc.push_back(c);
	}

	mChimes.push_back(tc);
	
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle =  ((float)i/NUM_CHIMES) * b2_pi; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.freq[0] = ofRandom(0.5,0.6);
		cd.freq[1] = cd.freq[0];
		cd.decay[0] = 1.5;
		cd.decay[1] = 1.5;
		cd.rSpeed = 0.25;
		cd.colors[0] = ofColor(0,100,0);
		cd.colors[1] = ofColor(100,0,0);
		cd.sensOn[0] = true; ////(ofRandomf() > 0.05);
		cd.sensOn[1] = true; //(ofRandomf() > 0.05);
		
		
		int p = 1;//ofRandom(1,6);
		
		for(int j = 0; j < p; j++){
			
			pivotDims pd;
			
			pd.d = 4;
			pd.iAngle = ((float)i/NUM_CHIMES) * 2 * b2_pi ;
			pd.rSpeed = 0.25; //0.05 * (j+1);
			pd.cRot = pd.iAngle;			
			cd.pivots.push_back(pd);
			
		}
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		tc.push_back(c);
	}
	
	mChimes.push_back(tc);
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 2.0;
		cd.iAngle =  ((float)i/NUM_CHIMES) * b2_pi; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.freq[0] = ofRandom(0.7,0.9);
		cd.freq[1] = cd.freq[0];
		cd.decay[0] = 1.5;
		cd.decay[1] = 1.5;
		cd.rSpeed = 0.25;
		cd.colors[0] = ofColor(0,255,255);
		cd.colors[1] = ofColor(0,255,255);
		cd.sensOn[0] = true; ////(ofRandomf() > 0.05);
		cd.sensOn[1] = true; //(ofRandomf() > 0.05);
		
		
		int p = 2;//ofRandom(1,6);
		
		for(int j = 0; j < p; j++){
			
			pivotDims pd;
			
			pd.d = 1;
			pd.iAngle = ((float)i/NUM_CHIMES) * 2 * b2_pi ;
			pd.rSpeed = 0.05 * (j+1);
			pd.cRot = pd.iAngle;			
			cd.pivots.push_back(pd);
			
		}
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		tc.push_back(c);
	}
	
	mChimes.push_back(tc);
	
	rePopulateRenderList();
	
}

void testApp::rePopulateRenderList(){
	
	for(int i = 0; i < 100; i++)renderList[i].clear();
	
	for(int i = 0; i < mChimes.size(); i++){
		for(vector<ofPtr<chime> >::iterator it = mChimes[i].begin(); it != mChimes[i].end(); it++){
			
			chimeUpdater::updateSpIndex(*it);
			int bin = (*it)->getSpIndex();
			if(bin < renderList.size())renderList[bin].push_back(*it);
			
		}
	}

}

//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(255);
	
	for(int i = 0; i < mChimes.size(); i++){
		for(vector<ofPtr<chime> >::iterator it = mChimes[i].begin(); it != mChimes[i].end(); it++){
			chimeUpdater::update(*it);
		}
	}
	
	chimeUpdater::step();
	
	
}


//--------------------------------------------------------------
void testApp::draw(){
	
	GLfloat fogColor[4]= {1.0f, 1.0f, 1.0f, 1.0f}; 
	
	mCam.begin();
	
	glFogi(GL_FOG_MODE, GL_LINEAR);      
	glFogfv(GL_FOG_COLOR, fogColor);            
	glFogf(GL_FOG_DENSITY, 0.25f);              
	glHint(GL_FOG_HINT, GL_NICEST);       
	glFogf(GL_FOG_START, 800.0f);           
	glFogf(GL_FOG_END, 825.0f);               
	glEnable(GL_FOG);     
	

	
	glPushMatrix();
	glScalef(scale, scale, 1);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	//ofEnableAlphaBlending();
	
	for(int i = renderList.size() - 1; i > -1; i--){
		
		//for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeRenderer::drawAnchor(*it);
		//for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::drawPivots(*it);
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::drawStem(*it);
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::drawHammer(*it);
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::drawSensors(*it);
	
	
	
	}
	
	//ofDisableAlphaBlending();
	ofDisableBlendMode();
	
	glPopMatrix();
	
	glDisable(GL_FOG);    
	
	mCam.end();
	
	
	ofSetColor(0);
	ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate(),2), 20,20);

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'x'){
		
		int count = 0;
		for(vector<ofPtr<chime> >::iterator it = mChimes[selCGroup].begin(); it != mChimes[selCGroup].end(); it++){
			ofVec2f v(0.005,0); 
			v *= count;
			v += ofVec2f(-0.005,0) * NUM_CHIMES/2;
			chimeUpdater::moveView(*it, v);
			count += 1;
		}
	}
	
	if(key == 'z'){
		
		int count = 0;
		for(vector<ofPtr<chime> >::iterator it = mChimes[selCGroup].begin(); it != mChimes[selCGroup].end(); it++){
			ofVec2f v(-0.005,0); 
			v *= count;
			v += ofVec2f(0.005,0) * NUM_CHIMES/2;
			chimeUpdater::moveView(*it, v);
			count += 1;
		}
	}
	
	if(key == ' '){selCGroup = (selCGroup +1)%mChimes.size();}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	


	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	float b = ofMap(x, 0, ofGetScreenWidth(), 0,1, true);
	
	for(vector<ofPtr<chime> >::iterator it = mChimes[selCGroup].begin(); it != mChimes[selCGroup].end(); it++){
		
		(*it)->setBlur(b);
		
	}
	
	rePopulateRenderList();
	
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