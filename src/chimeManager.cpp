/*
 *  chimeManager.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeManager.h"

vector<ofPtr<chime> > chimeManager::mChimes;
vector<ofPtr<chime> > chimeManager::mSelected;
vector<vector<ofPtr<chime> > > chimeManager::mOldGroups;
vector<vector<ofPtr<chime> > > chimeManager::renderList;
ofxOscSender * chimeManager::iSender = NULL;

int chimeManager::selCGroup = 0;
float chimeManager::mMaxZ = 0.0f;
customListener chimeManager::mListener;

void chimeManager::setup(ofxOscSender & s, ofxOscSender & i_s){

	chimeUpdater::setOscSender(&s);
	chimeRenderer::loadSprites();
	
	iSender = &i_s;
	
	for(int i = 0; i < 100; i++){
		vector<ofPtr<chime> > tc;
		renderList.push_back(tc);
	}
	
	setupChimes();

}

void chimeManager::setupChimes(){
	
	vector<ofPtr<chime> > tc;
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; 
		cd.anchorPos =  ofVec2f(0,-1);//ofVec2f(-5,0) + ofVec2f(0.4,0)* (float)i;
		cd.offset = 0;					
		cd.midi[0] = MIDI_MIN + ((float)(i+1)/NUM_CHIMES) * MIDI_RANGE;
		cd.midi[1] = MIDI_MIN + (1 - (float)(i+1)/NUM_CHIMES) * MIDI_RANGE;
		cd.decay[0] = 1.8;
		cd.decay[1] = 1.8;
		cd.rSpeed = 0.2;
		cd.colors[0] = ofColor(255,0,0);
		cd.colors[1] = ofColor(255,0,0);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		cd.zPos = 0;
		
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
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	
	mOldGroups.push_back(tc);
	
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle = b2_pi * (float)i/NUM_CHIMES; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.midi[0] = MIDI_MIN + ofRandom(0.15 * MIDI_RANGE,0.2 * MIDI_RANGE);
		cd.midi[1] = cd.midi[0];
		cd.decay[0] = 1.0;
		cd.decay[1] = 1.0;
		cd.rSpeed = 0.4;
		cd.colors[0] = ofColor(0,0,100);
		cd.colors[1] = ofColor(0,0,100);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		cd.zPos = 0.25;
		
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
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	mOldGroups.push_back(tc);
	
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 3.0;
		cd.iAngle =  ((float)i/NUM_CHIMES) * b2_pi; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.midi[0] =  MIDI_MIN + ofRandom(0.5 * MIDI_RANGE,0.6 * MIDI_RANGE);
		cd.midi[1] = cd.midi[0];
		cd.decay[0] = 1.5;
		cd.decay[1] = 1.5;
		cd.rSpeed = 0.25;
		cd.colors[0] = ofColor(0,100,0);
		cd.colors[1] = ofColor(100,0,0);
		cd.sensOn[0] = true; ////(ofRandomf() > 0.05);
		cd.sensOn[1] = true; //(ofRandomf() > 0.05);
		cd.zPos = 0.5;
		
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
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	mOldGroups.push_back(tc);
	
	tc.clear();
	
	for(int i = 0; i < NUM_CHIMES; i ++){
		
		chimeDef cd;
		cd.length = 2.0;
		cd.iAngle =  ((float)i/NUM_CHIMES) * b2_pi; 
		cd.anchorPos =  ofVec2f(0,0);
		cd.offset = 0;					
		cd.midi[0] =  MIDI_MIN + ofRandom(0.7 * MIDI_RANGE,0.9 * MIDI_RANGE);
		cd.midi[1] = cd.midi[0];
		cd.decay[0] = 1.5;
		cd.decay[1] = 1.5;
		cd.rSpeed = 0.25;
		cd.colors[0] = ofColor(0,255,255);
		cd.colors[1] = ofColor(0,255,255);
		cd.sensOn[0] = true; ////(ofRandomf() > 0.05);
		cd.sensOn[1] = true; //(ofRandomf() > 0.05);
		cd.zPos = 0.75;
		
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
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	mOldGroups.push_back(tc);
	
	rePopulateRenderList();
	
}

void chimeManager::rePopulateRenderList(){
	
	for(int i = 0; i < 100; i++)renderList[i].clear();
	
	
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		
		chimeUpdater::updateSpIndex(*it);
		int bin = (*it)->getSpIndex();
		if(bin < renderList.size()){
			renderList[bin].push_back(*it);
		}
		
		mMaxZ = max((*it)->getZpos(), mMaxZ);
		
	}
	
	
}


void chimeManager::shiftFocalPoint(float direction){
	
	float f = chimeUpdater::getFocalPoint();
	
	f =(direction > 0.1)? min(f + 0.005f, mMaxZ) : max(f - 0.005, 0.0);
	
	chimeUpdater::setFocalPoint(f);
	rePopulateRenderList();
	
	ofxOscMessage m;
	m.setAddress("/depthMeter");
	m.addFloatArg(f/mMaxZ);
	
	iSender->sendMessage(m);
	
	
}

void chimeManager::shiftZPos(float direction){
	
	float fp = chimeUpdater::getFocalPoint();
	
	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++){
		
		float d = fp - (*it)->getZpos();
		
		if(direction < 0.1){ //move twd focal point
			
			float a = (d != 0.0) ?((d > 0)? 0.005: -0.005) : 0.0;
			(*it)->setZpos((*it)->getZpos() + a);
			
		}else{
			
			//you can only move it just out of range
			//however could make this a delete trigger
			
			float a = (d > 0)? -0.005: 0.005;
			(*it)->setZpos(min(max((*it)->getZpos() + a, 0.0f), fp + 1.0f )); 
			
		}
		
	}
	
	rePopulateRenderList();
}


void chimeManager::selectNewGroup(){
	
	selCGroup = (selCGroup +1)%mOldGroups.size();
	mSelected.clear();
	mSelected = mOldGroups[selCGroup];
	
}


void chimeManager::update(){

	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++)chimeUpdater::update(*it);
	
	chimeUpdater::step();

}


void chimeManager::draw(){
	
	for(int i = renderList.size()-1; i > -1; i--){
		
		for(vector<ofPtr<chime> >::iterator it = renderList[i].begin(); it != renderList[i].end(); it++)chimeRenderer::draw(*it);
		
	}
	

}