/*
 *  chimeUpdater.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeUpdater.h"

float chimeUpdater::timeStep = 1.0f / TARGET_FRAME;
float chimeUpdater::vel_i = 2;
float chimeUpdater::pos_i = 1;
float chimeUpdater::mFocalPoint = 0.0f;
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
		pds[i].cRot += pds[i].rSpeed * tPassed * ofGetFrameRate()/TARGET_FRAME;
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
	
	
	int sIndex = -1;
	
	for(int i = 0; i < 2; i ++)if(c->getSensorOn(i))if(cd[i]->initContact)sIndex = i;
		
	
	if(sIndex > -1 ){
		
		cd[sIndex]->initContact = false;
		
		c->setReactTotal(sIndex, ofGetFrameRate() * c->getReactSecs(sIndex));
		c->setReactCount(sIndex, c->getReactTotal(sIndex));
		
		if(mSender && c->getBlur() < 0.99){
			
			ofxOscMessage m;
			m.setAddress("/chime");
			m.addIntArg(c->getIndex());
			m.addFloatArg(c->getSensorMidi(sIndex));
			m.addFloatArg(c->getReactSecs(sIndex));
			m.addFloatArg(c->getBlur());
			float p = c->getHammer()->GetPosition().x;
			p += c->getStemDims().cPos.x;
			p = min(8.0f, max(-8.0f, p))/8.0f;
			m.addFloatArg(p);
			mSender->sendMessage(m);
		}
		
	}
	
	for(int i = 0; i < 2; i ++){
	
		if(c->getReactCount(i) > 0){
			
			c->setReactCount(i, c->getReactCount(i) - 1);
			c->setSensorAlpha(i , 255.0f * (float)c->getReactCount(i)/c->getReactTotal(i));
			
		}else{
			
			c->setSensorAlpha(i, 0);
		}
	}
	
	
}

void chimeUpdater::updateSpIndex(ofPtr<chime> c){
	
	float b = max(0.0f,min(1.0f, abs(c->getZpos()- mFocalPoint)));
	c->setBlur(b);
	c->setSpIndex(c->getBlur() * 100); //objects out of range are assigned index 100
									   //so not placed in renderList
	
}

void chimeUpdater::moveView(ofPtr<chime> c, ofVec2f v){

	c->setAnchorPos(c->getAnchorPos() + v);
	
}

void chimeUpdater::step(){
	
	mTimeStamp1 = mTimeStamp2;
	mTimeStamp2 = ofGetSystemTime();
}


void chimeUpdater::setFocalPoint(float f){mFocalPoint = f;}
float chimeUpdater::getFocalPoint(){return mFocalPoint;}