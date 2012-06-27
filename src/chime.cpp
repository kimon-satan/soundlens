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
	mStemBody = NULL;
	
	for(int i = 0; i < 2; i++){
		mSensors[i] = NULL;
		mSensorData[i] =NULL;
	}
	
	reactCount = 0;
	reactSecs = ofRandom(0.25,1.0);

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

void chime::setStemBody(b2Body * s){mStemBody = s;}
b2Body * chime::getStemBody(){return mStemBody;}

void chime::setStemDims(stemDims sd){mStemDims = sd;}
stemDims chime::getStemDims(){return mStemDims;}

void chime::setPivotDims(vector<pivotDims> pd){mPivotDims = pd;}
vector<pivotDims> chime::getPivotDims(){return mPivotDims;}

void chime::setSensorData(collisionData ** cd){
	mSensorData[0] = cd[0];
	mSensorData[1] = cd[1];
}
collisionData ** chime::getSensorData(){return &mSensorData[0];}

void chime::setFreq(float tf){freq = tf;}
float chime::getFreq(){return freq;}


float chime::getHammerAlpha(){return mHammerAlpha;}
void chime::setHammerAlpha(float f){mHammerAlpha = f;}

void chime::setReactSecs(float f){reactSecs = f;}
float chime::getReactSecs(){return reactSecs;}

void chime::setReactTotal(int i){reactTotal  = i;}
int chime::getReactTotal(){return reactTotal;}

void chime::setReactCount(int i){reactCount = i;}
int chime::getReactCount(){return reactCount;}

void chime::setAnchorPos(ofVec2f t){anchorPos.set(t);}
ofVec2f chime::getAnchorPos(){return anchorPos;}

chime::~chime(){

	if(mWorld)delete mWorld;
	for(int i = 0; i < 2; i ++)if(mSensorData[i])delete mSensorData[i];

}