/*
 *  chimeFactory.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeFactory.h"

namespace chimeFactory {
	

	ofPtr<chime> createChime(chimeDef cd){

		ofPtr<chime> c = ofPtr<chime>(new chime());

		b2Vec2 gravity(0.0f,-10.0f);
		bool doSleep = true;
		b2World * world  = new b2World(gravity, doSleep);
		
		c->setWorld(world);
		c->setFreq(cd.freq);
		
		createAnchor(c, cd);
		
		b2Vec2 pPos = cd.anchorPos;
		
		for(int i = 0; i < cd.pivots.size(); i++){
			
			b2Vec2 bPos = myUtils::mul(cd.pivots[i].localPos, 0.5);
			bPos = myUtils::add(pPos, bPos);
			createPivot(c, bPos ,pPos, cd.pivots[i].rotSpeed);
			pPos = myUtils::add(pPos, cd.pivots[i].localPos);
			
			
		}
		
		createStem(c, cd, pPos);
		createSensors(c, cd, pPos);
		createHammer(c, cd, pPos);
		joinStemBodies(c,cd);
		
		return c;
		
	}


	void createAnchor(ofPtr<chime> c, chimeDef cd){
		
		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = cd.anchorPos;
		
		b2Body * b = c->getWorld()->CreateBody(&bd);
		b->SetSleepingAllowed(true);
		
		b2PolygonShape shape;
		shape.SetAsBox(1.0,1.0);
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.filter.maskBits = 0x0002;
		fd.density = 1.0;
		
		b->CreateFixture(&fd);
		
		c->setAnchorBody(b);
		
	}

	void createPivot(ofPtr<chime> c, b2Vec2 bPos, b2Vec2 pPos, float speed){
		
		b2World * tw = c->getWorld();
		b2Body * prevPb = c->getFinalBody(); //returns either anchor or last pivot
		
		
		ofVec2f vec = myUtils::b2ToOF(pPos) - myUtils::b2ToOF(bPos);
		float angle = vec.angleRad(ofVec2f(0,1));
		
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = bPos;
		bd.angle = -angle;
		bd.fixedRotation = false;
		
		
		b2Body * b = tw->CreateBody(&bd);
		b->SetSleepingAllowed(true);
		
		b2PolygonShape shape;
		
		if(vec.length() > 0){
			shape.SetAsBox(vec.length() + 0.05,0.05,b2Vec2(0,0),angle);
		}else{
			shape.SetAsBox(0.1,0.1,b2Vec2(0,0),angle);
		}
		
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.filter.maskBits = 0x0002;
		fd.density = 1.0;
		
		b->CreateFixture(&fd);
		
		
		c->addPivotBody(b);
		c->addPivotBodyDim(vec.length()*2);
		
		//now join to previous pivot
		b2RevoluteJointDef rjd;
		rjd.Initialize(prevPb, b, pPos);
		
		//something nice could be done with limits later ?...
		
		rjd.maxMotorTorque = 200.0; 
		rjd.motorSpeed = speed;
		rjd.enableMotor = true;
		
		b2RevoluteJoint * rj = (b2RevoluteJoint*)tw->CreateJoint(&rjd);
		
		//chime will need to store joint for later manipulation
		c->addPivotJoint(rj);	
		
	}

	void createStem(ofPtr<chime> c, chimeDef cd, b2Vec2 pPos){
		
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = pPos;  //needs and extra variable for offset
		bd.fixedRotation = false;
		bd.angle = cd.iAngle;
		
		b2Body * stem = c->getWorld()->CreateBody(&bd);
		stem->SetSleepingAllowed(true);
		
		b2PolygonShape stemShape;
		stemShape.SetAsBox(0.02,cd.length/2);
		b2FixtureDef fd;
		fd.shape = &stemShape;
		fd.filter.maskBits = 0x0002;
		fd.density = 0.01;
		
		stem->CreateFixture(&fd);
		
		c->setStem(stem); 
		c->setStemLength(cd.length);
		
	}

	void createHammer(ofPtr<chime> c, chimeDef cd, b2Vec2 pPos){
		
		b2BodyDef hd;
		hd.type = b2_dynamicBody;
		hd.position = pPos; // this isn't right
		hd.angle = cd.iAngle;
		hd.fixedRotation = false;
		
		b2Body * hammer = c->getWorld()->CreateBody(&hd);
		hammer->SetSleepingAllowed(true);
		
		b2PolygonShape hShape;
		hShape.SetAsBox(0.1,0.1);
		
		b2FixtureDef fd;
		
		fd.shape = &hShape;
		fd.density = 0.1;
		fd.friction = 0.05;
		fd.restitution = 0.1;
		fd.filter.maskBits = 0x0002;
		fd.filter.groupIndex = 2;
		hammer->CreateFixture(&fd);
		
		c->setHammer(hammer);
		
	}

	void createSensors(ofPtr<chime> c, chimeDef cd, b2Vec2 pPos){
		
		b2Body * sensors[2];
		collisionData * sensorData[2];
		
		//b2Vec2 iPos = c->getFinalBody()->GetPosition();
		
		for(int i = 0; i < 2; i ++){
			
			ofVec2f tmp(pPos.x, pPos.y);
			tmp.y += (i == 0)? cd.length/2 : -cd.length/2;
			tmp.rotateRad(cd.iAngle, ofVec2f(pPos.x, pPos.y));
			
			b2BodyDef sd;
			sd.type = b2_dynamicBody;
			sd.position.Set(tmp.x,tmp.y);
			sd.angle = cd.iAngle;
			sd.fixedRotation = false;
			
			sensors[i] = c->getWorld()->CreateBody(&sd);
			sensors[i]->SetSleepingAllowed(true);
			
			b2PolygonShape sShape;
			sShape.SetAsBox(0.05,0.05);
			b2FixtureDef sfd;
			sfd.shape = &sShape;
			sfd.density = 0.5;
			sfd.restitution = 0.2;
			sfd.filter.maskBits = 0x0002;
			sfd.filter.groupIndex = 2;
			//sfd.isSensor = true;
			
			b2Fixture * b  = sensors[i]->CreateFixture(&sfd);
			
			sensorData[i] = new collisionData();
			sensorData[i]->mIndex = i;
			sensorData[i]->cIndex = c->getIndex();
			b->SetUserData(sensorData[i]);
			
		}
		
		c->setSensors(&sensors[0]);
		c->setSensorData(&sensorData[0]);
		
	}




	void joinStemBodies(ofPtr<chime> c, chimeDef cd){
		
		b2World * tw = c->getWorld();
		b2Body * hostBody = c->getFinalBody();
		
		//stem
		
		b2Body * stem = c->getStem();
		
		b2WeldJointDef sjd;
		sjd.Initialize(stem, hostBody, stem->GetPosition()); //add in the offset later
		tw->CreateJoint(&sjd);
		
		//sensors
		
		b2Body * sensors[2];
		sensors[0] = c->getSensors()[0];
		sensors[1] = c->getSensors()[1];
		
		for(int i = 0; i < 2; i++){
			b2WeldJointDef wd;
			wd.Initialize(sensors[i], stem,  sensors[i]->GetPosition());
			tw->CreateJoint(&wd);
		}
		
		
		//hammer
		
		b2Body * hammer = c->getHammer();
		
		ofVec2f axis(0,1);
		axis.rotateRad(hammer->GetAngle());
		axis.normalize();
		
		b2PrismaticJointDef hjd;
		hjd.Initialize(hammer, stem,  hammer->GetPosition(), b2Vec2(-axis.x,-axis.y));
		hjd.lowerTranslation = -cd.length/2;
		hjd.upperTranslation = cd.length/2; 
		hjd.enableLimit = true;
		
		hjd.maxMotorForce = 0; //ofRandom(0,0.5);
		hjd.motorSpeed = 0.0f;
		hjd.enableMotor = true;
		
		tw->CreateJoint(&hjd);
		
	}
	
}
