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
	
	void setStem(b2Body * s);
	b2Body * getStem();
	
	void setSensorData(collisionData ** cd);
	collisionData ** getSensorData();
	
	void setCollisionListener(customListener & l);

	void setFreq(float tf);
	float getFreq();
	
	void setStemLength(float l);
	float getStemLength();
	
	void addPivotBody(b2Body * b);
	void addPivotJoint(b2RevoluteJoint * j);
	void addPivotBodyDim(float f);
	
	b2Body * getFinalBody();
	vector<b2Body *> getPivotBodies();
	vector<float> getPivotBodyDims();
	
	void setAnchorBody(b2Body * b);
	b2Body * getAnchor();
	
	float getHammerAlpha();
	void setHammerAlpha(float f);
	
	bool getIsContact();
	void setIsContact(bool b);
	
	void setReactSecs(float f);
	float getReactSecs();
	
	void setReactTotal(int i);
	int getReactTotal();
	
	void setReactCount(int i);
	int getReactCount();
	
	int getIndex();
	
	static int cIndex;
	
private:
	
	int index;
	
	b2World * mWorld;
	
	b2Body * mAnchor;
	b2Body  * mStem;
	b2Body * mHammer;
	b2Body * mSensors[2];
	
	vector<b2Body *> mPivotBodies;
	vector<float> mPivotBodyDims;
	vector<b2RevoluteJoint *> mPivotJoints;
	
	collisionData * mSensorData[2];
	customListener mListener;
	
	bool isContact;
	bool isActive;

	float reactSecs;
	int reactCount, reactTotal;
	
	float mHammerAlpha;
	
	float freq, mStemLength;

};