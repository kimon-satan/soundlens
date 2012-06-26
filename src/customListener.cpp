/*
 *  customListener.cpp
 *  chimes1
 *
 *  Created by Simon Katan on 01/05/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "customListener.h"

void customListener::BeginContact(b2Contact * contact){


	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	collisionData * aData = (collisionData *)fixtureA->GetUserData();
	collisionData * bData = (collisionData *)fixtureB->GetUserData();
	
	if(aData){
	
		aData->initContact = true;
	
	}else if(bData){
	
		bData->initContact = true;
		
	}
	

}

void customListener::EndContact(b2Contact* contact){

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	collisionData * aData = (collisionData *)fixtureA->GetUserData();
	collisionData * bData = (collisionData *)fixtureB->GetUserData();
	
	if(aData){

		aData->initContact = false;
	
	}else if(bData){
		
		bData->initContact = false;
	}
	
	
	
}