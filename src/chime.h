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
#include <Box2D/Box2D.h>

struct pivotDims{
	
	float d, iAngle, rSpeed, cRot;
	ofVec2f cPos;
	
};

struct stemDims{
	
	float offset, rSpeed, iAngle, cum_rSpeed, length;
	ofVec2f cPos;
	
};



class chime{

public:
	
	chime();
	virtual ~chime();
	
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
	
	void setPivotDims(vector<pivotDims> pd);
	vector<pivotDims> getPivotDims();
	
	void setSensorData(collisionData ** cd);
	collisionData ** getSensorData();
	
	void setCollisionListener(customListener & l);

	bool getSensorOn(int i);
	void setSensorOn(int i, bool b);
	
	void setSensorFreq(int i, float tf);
	float getSensorFreq(int i);
	
	float getSensorAlpha(int i);
	void setSensorAlpha(int i, float a);
	
	ofColor getSensorColor(int i);
	void setSensorColor(int i, ofColor c);
	
	void setReactSecs(int i, float f);
	float getReactSecs(int i);
	
	void setReactTotal(int i, int t);
	int getReactTotal(int i);
	
	void setReactCount(int i, int c);
	int getReactCount(int i);
	
	void setAnchorPos(ofVec2f t);
	ofVec2f getAnchorPos();
	
	void setBlur(float f);
	float getBlur();
	
	void setSpIndex(int i);
	int getSpIndex();
	
	
	int getIndex();
	
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
	
	vector<pivotDims> mPivotDims;

	float reactSecs[2];
	int reactCount[2], reactTotal[2];
	
	ofColor mSensorColors[2];
	
	float mSensorAlphas[2];
	float mSensorFreqs[2];
	
	bool mSensorOn[2];
	
	float mBlur;
	int spIndex;
	
	ofVec2f anchorPos;

};