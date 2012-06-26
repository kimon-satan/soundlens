/*
 *  pivot.cpp
 *  chimes1
 *
 *  Created by Simon Katan on 30/04/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "pivot.h"

pivot::pivot(){
	
	rotSpeed = 0.3;

}


void pivot::createBody(b2World * tw){
	
	b2BodyDef bd;
	bd.type = b2_kinematicBody;
	bd.position.Set(0,0); //(ofRandom(-2,2), ofRandom(-2,2));
	mBody = tw->CreateBody(&bd);
	mBody->SetSleepingAllowed(true);
	mBody->SetAngularVelocity(rotSpeed);
	
}


void pivot::update(){


	float a = mBody->GetAngle();
	a =  fmod(a, (float)PI * 2.0f);
	float incr = (rotSpeed * 1.0)/(PI * 2.0f * ofGetFrameRate());
	//isNewCycle = (a <= incr);
	
	

}

void pivot::draw(){

	if(!mBody)return;

	ofSetColor(0);
	ofNoFill();
	glPushMatrix();
	glRotatef(ofRadToDeg(mBody->GetAngle()), 0, 0, 1);
	ofLine(-0.2, 0, 0.2, 0);
	ofLine(0,-0.2, 0, 0.2);
	ofCircle(0, 0, 0.1);
	glPopMatrix();
	
}

//getters and setters


b2Body * pivot::getBody(){return mBody;}

