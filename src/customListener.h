/*
 *  customListener.h
 *  chimes1
 *
 *  Created by Simon Katan on 01/05/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include <Box2D/Box2D.h>
#include "ofMain.h"
#include "collisionData.h"

class customListener : public b2ContactListener{

	public:
	
	void BeginContact(b2Contact * contact);
	
	void EndContact(b2Contact * contact);
	


};