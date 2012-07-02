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
	
	for(int i = 0; i < 2; i ++){
		reactCount[i] = 0;
		mSensorAlphas[i] = 0;
		mSensorHeights[i] = 0.5;
		reactSecs[i] = 0.5;
		mSensorColors[i] = ofColor(255,0,0);
		mSensorOn[i] = true;
	}
	
	mBlur = 1.0;
	spIndex = 0;
	zPos = 0;
	
	
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

bool chime::getSensorOn(int i){return mSensorOn[i];}
void chime::setSensorOn(int i, bool b){mSensorOn[i] = b;}

void chime::setSensorHeight(int i, float tf){mSensorHeights[i] = tf;}
float chime::getSensorHeight(int i){return mSensorHeights[i];}

void chime::setSensorMidi(int i, float tf){mSensorMidis[i] = tf;}
float chime::getSensorMidi(int i){return mSensorMidis[i];}

float chime::getSensorAlpha(int i){return mSensorAlphas[i];}
void chime::setSensorAlpha(int i, float a){mSensorAlphas[i] = a;}

ofColor chime::getSensorColor(int i){return mSensorColors[i];}
void chime::setSensorColor(int i, ofColor c){mSensorColors[i] = c;}

void chime::setReactSecs(int i, float f){reactSecs[i] = f;}
float chime::getReactSecs(int i){return reactSecs[i];}

void chime::setReactTotal(int i, int t){reactTotal[i]  = t;}
int chime::getReactTotal(int i){return reactTotal[i];}

void chime::setReactCount(int i, int c){reactCount[i] = c;}
int chime::getReactCount(int i){return reactCount[i];}

void chime::setAnchorPos(ofVec2f t){anchorPos.set(t);}
ofVec2f chime::getAnchorPos(){return anchorPos;}

void chime::setBlur(float f){mBlur = f;}
float chime::getBlur(){return mBlur;}

void chime::setSpIndex(int i){spIndex = i;}
int chime::getSpIndex(){return spIndex;}

void chime::setZpos(float f){zPos = f;}
float chime::getZpos(){return zPos;}

chime::~chime(){

	if(mWorld)delete mWorld;
	for(int i = 0; i < 2; i ++)if(mSensorData[i])delete mSensorData[i];

}