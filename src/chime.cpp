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

string chime::getChFixedString(int i){
	
	string fnameList[CH_FIXED_COUNT] = {"phase", "speed", "length", "freq", "decay", "col"};
	return fnameList[i];

}

string chime::getChModString(int i){
	
	string mnameList[CH_MOD_COUNT] = {"numPivots", "pivotPhaseMul", "pivotLngth", "pivotSpdSkew"};
	return mnameList[i];
	
}



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
	}
	
	mSensorHeight = 0.5;
	mSensorColor = ofColor(255,0,0);
	
	for(int i = 0; i < CH_MOD_COUNT; i ++){
		
		modifiable<float> mp;
		modParams.push_back(mp);
	
	}
	
	for(int i = 0; i < CH_FIXED_COUNT; i ++){
		
		float fp;
		fixedParams.push_back(fp);
		
	}
	
	mBlur = 1.0;
	spIndex = 0;
	zPos = 0;
	isSelected = false;
	isTmpSelected = false;
	generation = 0;
	timeToConform = 300;
	
}


void chime::stepIncrement(int direction){
	
	anchorPos.shiftValue(direction);
	
	for(int i =0; i < modParams.size(); i ++){
		modParams[i].shiftValue(direction);
	}
	
}

void chime::autoStepIncrement(){

	if(anchorPos.getIsAuto()){
		anchorPos.shiftValue(1);
	}
		
	
	for(int i =0; i < modParams.size(); i ++){
		if(modParams[i].getIsAuto())modParams[i].shiftValue(1);
	}
	
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

void chime::setPivotRots(vector<float> vf){pivotRots = vf;}
vector<float> chime::getPivotRots(){return pivotRots;}

void chime::setSensorData(collisionData ** cd){
	mSensorData[0] = cd[0];
	mSensorData[1] = cd[1];
}
collisionData ** chime::getSensorData(){return &mSensorData[0];}


void chime::setSensorHeight(float tf){mSensorHeight = tf;}
float chime::getSensorHeight(){return mSensorHeight;}

float chime::getSensorAlpha(int i){return mSensorAlphas[i];}
void chime::setSensorAlpha(int i, float a){mSensorAlphas[i] = a;}

void chime::setReactTotal(int t){reactTotal = t;}
int chime::getReactTotal(){return reactTotal;}

void chime::setReactCount(int i, int c){reactCount[i] = c;}
int chime::getReactCount(int i){return reactCount[i];}

void chime::setAnchorPos(ofVec2f t){anchorPos.set(t);}
ofVec2f chime::getAnchorPos(){return anchorPos.getCVal();}

void chime::setAnchorTarget(ofVec2f t, float increment, bool isAuto){
	anchorPos.setTarget(t,increment,isAuto);
}

void chime::setModParam(int p, float val){
	

	modParams[p].set(val);

}
float chime::getModParam(int p){return modParams[p].getCVal();}

void chime::setModParamTarget(int p, float val, float increment, bool isAuto){
	
	modParams[p].setTarget(val, increment, isAuto);
}

void chime::flagModParam(int i){modParams[i].setFlagChanged(true);}
bool chime::getModParamChanged(int i){return modParams[i].getFlagChanged();}
void chime::resetModParam(int i){modParams[i].setFlagChanged(false);}

void chime::endMods(){
	
	for(int i =0 ; i < CH_MOD_COUNT; i++)modParams[i].end();
	anchorPos.end();

}

void chime::setFixedParam(int p, float val){
	
	if(p == CH_PHASE){
		
		val = fmod(val, b2_pi * 2);
		if(val < 0)val += b2_pi * 2;
		val = fmod(val, b2_pi);
		
	}
	
	if(p == CH_FREQ){
		
		val = min((float)(MIDI_MIN + MIDI_RANGE), max((float)MIDI_MIN, val));
		
	}
	
	if(p == CH_COLOR){
		if(val < 0)val += 255;
		val = fmod(val, 255);
	}
		
	
	fixedParams[p] = val;
	
}

float chime::getFixedParam(int p){ return fixedParams[p];}

void chime::setBlur(float f){mBlur = f;}
float chime::getBlur(){return mBlur;}

void chime::setSpIndex(int i){spIndex = i;}
int chime::getSpIndex(){return spIndex;}

void chime::setZpos(float f){zPos = f;}
float chime::getZpos(){return zPos;}

void chime::setIsSelected(bool b){isSelected = b;}
bool chime::getIsSelected(){return isSelected;}

void chime::setIsTmpSelected(bool b){isTmpSelected = b;}
bool chime::getIsTmpSelected(){return isTmpSelected;}

void chime::setGeneration(int i){generation = i;}
int chime::getGeneration(){return generation;}

bool chime::incrTimeToConform(){ 
	
	timeToConform -= 1;
	if(timeToConform == 0){
		timeToConform = 300;
		return true;
	}else{
		return false;
	}

}



chime::~chime(){

	if(mWorld)delete mWorld;
	for(int i = 0; i < 2; i ++)if(mSensorData[i])delete mSensorData[i];

}