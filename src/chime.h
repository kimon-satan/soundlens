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

	void setFreq(float tf);
	float getFreq();
	
	float getHammerAlpha();
	void setHammerAlpha(float f);
	
	void setReactSecs(float f);
	float getReactSecs();
	
	void setReactTotal(int i);
	int getReactTotal();
	
	void setReactCount(int i);
	int getReactCount();
	
	void setAnchorPos(ofVec2f t);
	ofVec2f getAnchorPos();
	
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

	float reactSecs;
	int reactCount, reactTotal;
	
	float mHammerAlpha;
	
	float freq;
	
	ofVec2f anchorPos;

};