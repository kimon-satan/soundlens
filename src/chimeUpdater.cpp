/*
 *  chimeUpdater.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeUpdater.h"

float chimeUpdater::timeStep = 1.0f / 60.0f;
float chimeUpdater::vel_i = 3;
float chimeUpdater::pos_i = 1;
unsigned long chimeUpdater::mTimeStamp1 = ofGetSystemTime();
unsigned long chimeUpdater::mTimeStamp2 = ofGetSystemTime();

ofxOscSender * chimeUpdater::mSender = NULL;


void chimeUpdater::setOscSender(ofxOscSender * s){mSender = s;}

void chimeUpdater::update(ofPtr<chime> c){
	
	b2World * w = c->getWorld();
	w->Step(timeStep, vel_i, pos_i);
	w->ClearForces();
	
	updateDims(c);
	updateSensors(c);

}

void chimeUpdater::updateDims(ofPtr<chime> c){

	float tPassed = (float)(mTimeStamp2 - mTimeStamp1)/1000.0f;
	
	stemDims sd = c->getStemDims();
	
	sd.cPos.set(c->getAnchorPos()); 
	float cumRot = 0;
	
	vector<pivotDims> pds(c->getPivotDims());
	
	for(int i = 0; i < pds.size(); i++){
		pds[i].cRot += pds[i].rSpeed * tPassed;
		fmod(pds[i].cRot,360.0f);
		
		ofVec2f t(0,pds[i].d);
		
		cumRot += pds[i].cRot;
		t.rotateRad(cumRot);
		sd.cPos += t;
		
	}
	
	c->setPivotDims(pds);
	c->setStemDims(sd);
	
}

void chimeUpdater::updateSensors(ofPtr<chime> c){
	
	collisionData ** cd = c->getSensorData();
	
	
	if(cd[0]->initContact || cd[1]->initContact){
		
		cd[0]->initContact = false;
		cd[1]->initContact = false;
		
		c->setReactTotal(ofGetFrameRate() * c->getReactSecs());
		c->setReactCount(c->getReactTotal());
		
		if(mSender){
			
			ofxOscMessage m;
			m.setAddress("/chime");
			m.addIntArg(c->getIndex());
			m.addFloatArg(c->getFreq());
			m.addFloatArg(c->getReactSecs());
			mSender->sendMessage(m);
		}
		
	}
	
	
	if(c->getReactCount() > 0){
		
		c->setReactCount(c->getReactCount() - 1);
		c->setHammerAlpha(255.0f * (float)c->getReactCount()/c->getReactTotal());
		
	}else{
		
		c->setHammerAlpha(0);
	}
	
}

void chimeUpdater::moveView(ofPtr<chime> c, ofVec2f v){

	c->setAnchorPos(c->getAnchorPos() + v);
	
}

void chimeUpdater::step(){
	
	mTimeStamp1 = mTimeStamp2;
	mTimeStamp2 = ofGetSystemTime();
}