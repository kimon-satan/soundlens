/*
 *  chime.cpp
 *  chimes1
 *
 *  Created by Simon Katan on 30/04/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "chime.h"

int chime::cIndex = 1;

chime::chime(){
	
	index = cIndex;
	cIndex += 1;

	mWorld = NULL;
	mHammer = NULL;
	mStem = NULL;
	
	for(int i = 0; i < 2; i++){
		mSensors[i] = NULL;
		mSensorData[i] =NULL;
	}
	
	reactCount = 0;
	reactSecs = ofRandom(0.25,1.0);
	isContact = false;

	freq = ofRandom(0,1);
	
}


//getters and setters

int chime::getIndex(){return index;}

void chime::setWorld(b2World * w){mWorld = w;}
b2World * chime::getWorld(){return mWorld;}

void chime::setCollisionListener(customListener & l){
	mListener = l;
	mWorld->SetContactListener(&mListener);
	
}

void chime::setHammer(b2Body * h){mHammer = h;}
b2Body * chime::getHammer(){return mHammer;}

void chime::setSensors(b2Body ** s){
	mSensors[0] = s[0];
	mSensors[1] = s[1];
}
b2Body ** chime::getSensors(){return &mSensors[0];}

void chime::setStem(b2Body * s){mStem = s;}
b2Body * chime::getStem(){return mStem;}

void chime::setSensorData(collisionData ** cd){
	mSensorData[0] = cd[0];
	mSensorData[1] = cd[1];
}
collisionData ** chime::getSensorData(){return &mSensorData[0];}

void chime::setFreq(float tf){freq = tf;}
float chime::getFreq(){return freq;}

void chime::addPivotBody(b2Body * b){mPivotBodies.push_back(b);}
vector<b2Body *> chime::getPivotBodies(){return mPivotBodies;}

void chime::addPivotBodyDim(float f){mPivotBodyDims.push_back(f);}
vector<float> chime::getPivotBodyDims(){return mPivotBodyDims;}

void chime::addPivotJoint(b2RevoluteJoint * j){mPivotJoints.push_back(j);}


b2Body * chime::getFinalBody(){
	
	return(mPivotBodies.size() > 0)? mPivotBodies.back() : mAnchor;
	
}

void chime::setStemLength(float l){mStemLength = l;}
float chime::getStemLength(){return mStemLength;}

void chime::setAnchorBody(b2Body * b){mAnchor = b;}
b2Body * chime::getAnchor(){return mAnchor;}

float chime::getHammerAlpha(){return mHammerAlpha;}
void chime::setHammerAlpha(float f){mHammerAlpha = f;}

bool chime::getIsContact(){return isContact;}
void chime::setIsContact(bool b){isContact = b;}

void chime::setReactSecs(float f){reactSecs = f;}
float chime::getReactSecs(){return reactSecs;}

void chime::setReactTotal(int i){reactTotal  = i;}
int chime::getReactTotal(){return reactTotal;}

void chime::setReactCount(int i){reactCount = i;}
int chime::getReactCount(){return reactCount;}

chime::~chime(){

	if(mWorld)delete mWorld;
	for(int i = 0; i < 2; i ++)if(mSensorData[i])delete mSensorData[i];

}