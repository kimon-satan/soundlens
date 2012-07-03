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
	
	//setupChimes();


}

void chimeManager::createChimes(groupPreset p){
	
	
	vector<ofPtr<chime> > tc;
	
	for(int i = 0; i < p.numChimes; i ++){
		
		chimeDef cd;
		cd.length = p.length.getValue(i);
		cd.iAngle = p.iAngle.getValue(i); 
		cd.anchorPos =  p.pos.getValue(i);
		cd.offset = 0;					
		cd.midi[0] = p.freq.getValue(i);
		cd.midi[1] = p.freq.getValue(i);
		cd.decay[0] = 1.8;
		cd.decay[1] = 1.8;
		cd.rSpeed = p.speed.getValue(i);
		cd.colors[0] = ofColor(255,0,0);
		cd.colors[1] = ofColor(255,0,0);
		cd.sensOn[0] = true; //(i%2 == 0);
		cd.sensOn[1] = true; //(i%2 == 1);
		cd.zPos = chimeUpdater::getFocalPoint(); // + 1.0; //not for now
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	
	mOldGroups.push_back(tc);
	mSelected = tc;
	
	rePopulateRenderList();


}

void chimeManager::addChime(){

	
	groupPreset p;
	p.numChimes = 100;
	p.pos.initVal.set(ofVec2f(0,0));
	p.pos.dType = DT_NONE;
	p.pos.increment.set(ofVec2f(0,0.5));
	p.pos.range = 5;
	p.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p.freq.dType = DT_FLAT;
	p.freq.range = 12;
	p.freq.increment = 3;
	p.iAngle.initVal = 0;
	p.iAngle.dType =  DT_STEP;
	p.iAngle.increment = b2_pi * 0.01;
	p.speed.initVal = -0.2;
	p.length.initVal = 4.0;
	
	createChimes(p);

}

void chimeManager::setupChimes(){
	
	groupPreset p;
	p.numChimes = 10;
	p.pos.initVal.set(ofVec2f(0,0));
	p.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p.iAngle.initVal = 0;
	p.iAngle.dType = DT_STEP;
	p.iAngle.increment = b2_pi/10.0f;
	p.speed.initVal = 0.2;
	p.length.initVal = 2.0;
	
	createChimes(p);
	
	groupPreset p2;
	p2.numChimes = 40;
	p2.pos.initVal.set(ofVec2f(0,0));
	p2.pos.dType = DT_RADIAL;
	p2.pos.radius = 3.0;
	p2.pos.rot = PI * 2.0f/40.0f;
	
	p2.freq.initVal = MIDI_MIN + MIDI_RANGE/2;
	p2.freq.dType = DT_FLAT;
	p2.freq.increment = 1;
	p2.freq.range = 12;
	
	
	p2.iAngle.initVal = 0;
	p2.iAngle.dType = DT_STEP;
	p2.iAngle.increment = b2_pi/5.0f;
	p2.speed.initVal = 0.2;
	
	p2.length.initVal = 2.0;
	p2.length.dType = DT_NORMAL;
	p2.length.increment = 0.05;
	p2.length.range = 20;
	
	createChimes(p2);
	
	
	
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