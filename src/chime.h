/*
 *  chime.h
 *  chimes2
 *
 *  Created by Simon Katan on 30/04/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#include "collisionData.h"
#include "customListener.h"
#include "modifiable.h"
#include <Box2D/Box2D.h>


#define MIDI_RANGE 93
#define MIDI_MIN 28


enum e_chimeParameter {
	
	CH_PHASE,
	CH_SPEED,
	CH_LENGTH,
	CH_FREQ,
	CH_DECAY,
	CH_PIV_NUM,
	CH_PIV_PH_MUL,
	CH_PIV_LGTH,
	CH_PIV_SPD_SKEW,
	CH_FLOAT_COUNT,
	CH_ANCHOR, //non standard types
	CH_COLOR,
	CH_BLUR,
	CH_COUNT,
	
};



struct stemDims{
	
	float iAngle, iHoff;
	ofVec2f cPos;
	
};



class chime{

public:
	
	chime();
	virtual ~chime();
	
	void stepIncrement(int direction);
	void autoIncrement();
	
	//getters and setters
	
	void setWorld(b2World * w);
	b2World * getWorld();
	
	void setHammer(b2Body * h);
	b2Body * getHammer();
	
	void setSensors(b2Body ** s);
	b2Body ** getSensors();
	
	void setStemBody(b2Body * s);
	b2Body * getStemBody();
	
	void setStemDims(stemDims sd);
	stemDims getStemDims();
	
	void setPivotRots(vector<float> vf);
	vector<float> getPivotRots();
	
	void setSensorData(collisionData ** cd);
	collisionData ** getSensorData();
	
	void setCollisionListener(customListener & l);
	
	void setSensorHeight(float tf);
	float getSensorHeight();
	
	float getSensorAlpha(int i);
	void setSensorAlpha(int i, float a);
	
	ofColor getSensorColor();
	void setSensorColor(ofColor c);
	
	void setReactTotal(int t);
	int getReactTotal();
	
	void setReactCount(int i, int c);
	int getReactCount(int i);
	
	void setAnchorPos(ofVec2f t);
	ofVec2f getAnchorPos();
	void setAnchorTarget(ofVec2f t, float increment, bool isAuto);
	
	void setModParam(int p, float val);
	float getModParam(int p);
	void setModParamTarget(int p, float val, float increment, bool isAuto);
	bool getModParamChanged(int p);
	void resetModParam(int i);
	
	
	void setBlur(float f);
	float getBlur();
	
	void setSpIndex(int i);
	int getSpIndex();

	void setZpos(float f);
	float getZpos();
	
	void setIsSelected(bool b);
	bool getIsSelected();
	
	void setIsTmpSelected(bool b);
	bool getIsTmpSelected();
	
	int getIndex();
	
	static string getChParamString(int i);
	
	static int cIndex;
	
private:
	
	int index;
	
	b2World * mWorld;
	
	b2Body  * mStemBody;
	stemDims mStemDims;
	
	b2Body * mHammer;
	b2Body * mSensors[2];
	
	collisionData * mSensorData[2];
	customListener mListener;

	int reactCount[2], reactTotal;
	
	ofColor mSensorColor;
	
	float mSensorAlphas[2];
	float mSensorHeight;
	
	float mBlur;
	int spIndex;
	
	vector<float> pivotRots;
	
	modifiable<ofVec2f> anchorPos;
	vector<modifiable<float> >modParams;
	
	float zPos;
	bool isSelected, isTmpSelected;

};