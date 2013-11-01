/*
 *  myUtils.h
 *  targetPractice
 *
 *  Created by Simon Katan on 07/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include <Box2D/Box2D.h>

namespace myUtils{

	float getSinVal(float freq, float phase, float mul, float add);
	b2Vec2 mul(b2Vec2 b, b2Vec2 mul);
	b2Vec2 mul(b2Vec2 b, float mul);
	b2Vec2 add(b2Vec2 b, float add);
	b2Vec2 add(b2Vec2 b, b2Vec2 add);
	ofVec2f b2ToOF(b2Vec2 b);
	b2Vec2 OFTob2(ofVec2f b);

};
