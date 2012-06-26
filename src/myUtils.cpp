/*
 *  myUtils.cpp
 *  targetPractice
 *
 *  Created by Simon Katan on 07/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "myUtils.h"

namespace myUtils{

	float getSinVal(float freq, float phase, float mul, float add){

		float n = ofDegToRad(ofGetFrameNum() * (360.0f/60.0f) * freq);
		n += phase;
		n = fmod(n, 2.0f * (float)PI);
		float s = add + sin(n) * mul; 
		
		return s;

	}
	
	b2Vec2 mul(b2Vec2 b, float mul){
		
		return b2Vec2(b.x * mul, b.y * mul);
	}
	
	
	b2Vec2 mul(b2Vec2 b, b2Vec2 mul){
		
		return b2Vec2(b.x * mul.x, b.y * mul.y);
		
	}
	
	b2Vec2 add(b2Vec2 b, b2Vec2 add){
		
		return b2Vec2(b.x + add.x, b.y + add.y);
	}
	
	b2Vec2 add(b2Vec2 b, float add){
		
		return b2Vec2(b.x + add, b.y + add);
		
	}
	
	
	ofVec2f b2ToOF(b2Vec2 b){return ofVec2f(b.x,b.y);}
	
	b2Vec2 OFTob2(ofVec2f b){return b2Vec2(b.x,b.y);}

}