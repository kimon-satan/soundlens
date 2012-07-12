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
	updateModifiables(c);

}


void chimeUpdater::updateModifiables(ofPtr<chime> c){

	
	for(int i = 0; i < CH_FLOAT_COUNT; i ++){
	
		if(c->getModParamChanged(i)){
			
			switch(i){
			
				case CH_FREQ:
					chimeFactory::mapFreqToSensors(c);
					break;
				
				case CH_PHASE:
					// chimeFactory::conformPhase(c); 
					//need a different method through adjusting speed
					break;
				
				case CH_SPEED:
					//potential for conflict when phase is changing too
					break;
				
				case CH_LENGTH:
					//should be fine
					break;
					
				//decay is fine
			
			}
		
			c->resetModParam(i);
		}
	
	}
	
}

void chimeUpdater::updateDims(ofPtr<chime> c){

	stemDims sd = c->getStemDims();
	
	sd.cPos.set(c->getAnchorPos()); 
	
	b2Body * b = c->getStemBody();
	
	float cumRot = 0;
	
	vector<float> pRots;
	vector<float> sp_props;
	
	float nTot = 0;
	
	for(int i = 0; i < c->getModParam(CH_PIV_NUM) + 1; i++){
		float prop = max(1 - i * abs(pow(c->getModParam(CH_PIV_SPD_SKEW),2)), 0.0f);
		nTot +=  prop;
		sp_props.push_back(prop);
	}
	
	if(c->getModParam(CH_PIV_SPD_SKEW) < 0)reverse(sp_props.begin(), sp_props.end());
	for(int i = 0; i < c->getModParam(CH_PIV_NUM); i++)sp_props[i] /= nTot; //normalisedSum
	
	
	for(int i = 0; i < c->getModParam(CH_PIV_NUM); i++){
		
		//need a better formula here
		float speed = c->getModParam(CH_SPEED) * sp_props[i]; 
		float rot = c->getModParam(CH_PHASE) * c->getModParam(CH_PIV_PH_MUL);
		
		rot += fmod(speed * (float)ofGetFrameNum()/60.0f, b2_pi * 2.0f);
		
		ofVec2f t(0,c->getModParam(CH_PIV_LGTH)/c->getModParam(CH_PIV_NUM));
		
		pRots.push_back(rot);
		cumRot += rot;
		t.rotateRad(cumRot);
		sd.cPos += t;
		
	}
	
	c->setPivotRots(pRots); // just for drawing
	c->setStemDims(sd);
	
}

void chimeUpdater::updateSensors(ofPtr<chime> c){
	
	collisionData ** cd = c->getSensorData();
	
	
	int sIndex = -1;
	
	for(int i = 0; i < 2; i ++){
		if(cd[i]->initContact)
			sIndex = i;
	}
		
	
	if(sIndex > -1 ){
		
		cd[sIndex]->initContact = false;
		
		c->setReactTotal(ofGetFrameRate() * c->getModParam(CH_DECAY));
		c->setReactCount(sIndex, c->getReactTotal());
		
		if(mSender && c->getBlur() < 0.99){
			
			ofxOscMessage m;
			m.setAddress("/chime");
			m.addIntArg(c->getIndex());
			m.addFloatArg(c->getModParam(CH_FREQ));
			m.addFloatArg(c->getModParam(CH_DECAY));
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
			c->setSensorAlpha(i , 255.0f * (float)c->getReactCount(i)/c->getReactTotal());
			
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


void chimeUpdater::step(){
	
	mTimeStamp1 = mTimeStamp2;
	mTimeStamp2 = ofGetSystemTime();
}


void chimeUpdater::setFocalPoint(float f){mFocalPoint = f;}
float chimeUpdater::getFocalPoint(){return mFocalPoint;}