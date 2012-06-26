/*
 *  pivot.h
 *  chimes1
 *
 *  Created by Simon Katan on 30/04/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "ofMain.h"
#include <Box2D/Box2D.h>

class pivot{

public:
	
	pivot();
	
	void createBody(b2World * tw);
	void update();
	void draw();
	
	//setters and getters
	
	b2Body * getBody();
	
private:

	b2Body * mBody;
	float rotSpeed;
	
};
