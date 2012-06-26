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
ofxOscSender * chimeUpdater::mSender = NULL;


void chimeUpdater::setOscSender(ofxOscSender * s){mSender = s;}

void chimeUpdater::update(ofPtr<chime> c){
	
	b2World * w = c->getWorld();
	w->Step(timeStep, vel_i, pos_i);
	w->ClearForces();
	
	collisionData ** cd = c->getSensorData();
	
	if(c->getIsContact()){
				
		if(!cd[0]->initContact && !cd[1]->initContact){
			c->setIsContact(false);
		}
		
	}else{
		
		if(cd[0]->initContact || cd[1]->initContact){
			
			c->setReactTotal(ofGetFrameRate() * c->getReactSecs());
			c->setReactCount(c->getReactTotal());
			c->setIsContact(true);
		
			if(mSender){
				
				ofxOscMessage m;
				m.setAddress("/chime");
				m.addIntArg(c->getIndex());
				m.addFloatArg(c->getFreq());
				m.addFloatArg(c->getReactSecs());
				mSender->sendMessage(m);
			}
			
		}
		
	}
	
	if(c->getReactCount() > 0){
		
		c->setReactCount(c->getReactCount() - 1);
		c->setHammerAlpha(255.0f * (float)c->getReactCount()/c->getReactTotal());
		
	}else{
		
		c->setHammerAlpha(0);
	}
	
	

}