/*
 *  collisionData.h
 *  chimes1
 *
 *  Created by Simon Katan on 01/05/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

class collisionData{

	public:
		
	collisionData(){
		
		initContact = false;
		mIndex = 0;
		cIndex = 0;
		
	};
	
	bool initContact;
	int mIndex, cIndex;

};