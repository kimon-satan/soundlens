/*
 *  customListener.cpp
 *  chimes1
 *
 *  Created by Simon Katan on 01/05/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "customListener.h"

void customListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	
	float f_impulse = impulse->normalImpulses[0];	

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	collisionData * aData = (collisionData *)fixtureA->GetUserData();
	collisionData * bData = (collisionData *)fixtureB->GetUserData();
	

	
	if(f_impulse > 0.01){
		
		if(aData){
		
			aData->initContact = true;
		
		}else if(bData){
		
			bData->initContact = true;
			
		}
	}
	

}

