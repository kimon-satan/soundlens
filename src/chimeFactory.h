/*
 *  chimeFactory.h
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "myUtils.h"
#include "chime.h"


struct pivotDef{
	
	pivotDef(b2Vec2 lp, float rs){
		
		localPos = lp;
		rotSpeed = rs;
		
	};
	
	b2Vec2 localPos;
	float rotSpeed;

};

struct chimeDef{
	
	b2Vec2 anchorPos; //local
	float stemOffset; // -1 -> 1
	vector<pivotDef> pivots; 
	float length;
	float freq;
	float iAngle; //radians
	
};

namespace chimeFactory{

	ofPtr<chime> createChime(chimeDef cd);
	
	void createAnchor(ofPtr<chime> c, chimeDef cd);
	void createStem(ofPtr<chime> c, chimeDef cd,b2Vec2 pPos);
	void createHammer(ofPtr<chime> c, chimeDef cd, b2Vec2 pPos);
	void createSensors(ofPtr<chime> c, chimeDef cd, b2Vec2 pPos);
	void createPivot(ofPtr<chime> c, b2Vec2 bPos, b2Vec2 pPos, float speed);
	void joinStemBodies(ofPtr<chime> c, chimeDef cd);


};