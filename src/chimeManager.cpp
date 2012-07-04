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


}

void chimeManager::createChimes(groupPreset p, ofVec2f pos){
	
	
	p.pos.initVal =  pos;
	
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
		cd.zPos = chimeUpdater::getFocalPoint() + 1.0; //not for now
		
		
		ofPtr<chime> c = chimeFactory::createChime(cd);
		
		c->setCollisionListener(mListener);
		
		mChimes.push_back(c);
		tc.push_back(c);
	}
	
	
	mOldGroups.push_back(tc);
	mSelected = tc;
	
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

//selection methods

void chimeManager::selectByPos(ofVec2f p, float r){

	mSelected.clear(); //will eventually need a way of storing old groups
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		if(p.distance((*it)->getAnchorPos()) < r){
			mSelected.push_back(*it);
		}
	}

}


void chimeManager::selectByRotSpeed(float rs, float tol){
	
	mSelected.clear(); //will eventually need a way of storing old groups
	for(vector<ofPtr<chime> >::iterator it = mChimes.begin(); it != mChimes.end(); it++){
		if((*it)->getStemDims().cum_rSpeed >= rs - tol &&
		   (*it)->getStemDims().cum_rSpeed <= rs + tol){
			mSelected.push_back(*it);
		}
	}

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


void chimeManager::drawSelected(){
	

	for(vector<ofPtr<chime> >::iterator it = mSelected.begin(); it != mSelected.end(); it++)chimeRenderer::drawSelected(*it);


}