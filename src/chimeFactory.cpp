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
		
		for(int i = 0; i < 2; i++){
			c->setSensorFreq(i, cd.freq[i]);
			c->setReactSecs(i, cd.decay[i]);
			c->setSensorColor(i, cd.colors[i]);
			c->setSensorOn(i, cd.sensOn[i]);
		}
		
		c->setAnchorPos(cd.anchorPos);
		c->setPivotDims(cd.pivots);
		
		stemDims sd;
		
		sd.length = cd.length;
		sd.offset = cd.offset;
		sd.iAngle = cd.iAngle;
		sd.rSpeed = cd.rSpeed;
		sd.cum_rSpeed = sd.rSpeed;
		
		
		for(int i = 0; i < cd.pivots.size(); i++){
			sd.cum_rSpeed += cd.pivots[i].rSpeed;
			sd.iAngle += cd.pivots[i].iAngle;
		}
		
		c->setStemDims(sd);
		c->setSpIndex(100);
		
		createStem(c);
		createSensors(c);
		createHammer(c);
		joinStemBodies(c);
		
		return c;
		
	}


	void createStem(ofPtr<chime> c){
		
		stemDims sd = c->getStemDims();
		
		b2BodyDef bd;
		bd.type = b2_kinematicBody;
		bd.position = b2Vec2(0,0);  
		bd.fixedRotation = false;
		bd.angle = sd.iAngle;
		
		b2Body * stem = c->getWorld()->CreateBody(&bd);
		stem->SetSleepingAllowed(true);
		stem->SetAngularVelocity(sd.cum_rSpeed); 
		
		b2PolygonShape stemShape;
		stemShape.SetAsBox(0.01,sd.length/2, b2Vec2(0,sd.offset),0); // needs to include offset and angle
		b2FixtureDef fd;
		fd.shape = &stemShape;
		fd.density = 0.25;
		fd.friction = 0;
		fd.restitution = 0.01;
		
		stem->CreateFixture(&fd);
		
		c->setStemBody(stem); 
		
	}

	void createHammer(ofPtr<chime> c){
		
		stemDims sd = c->getStemDims();
		
		ofVec2f o(0,sd.offset * sd.length/2);
		o.rotateRad(sd.iAngle);
		
		b2BodyDef hd;
		hd.type = b2_dynamicBody;
		hd.position.Set(o.x,o.y); // needs to include offset and angle
		hd.angle = sd.iAngle;
		hd.fixedRotation = false;
		
		b2Body * hammer = c->getWorld()->CreateBody(&hd);
		hammer->SetSleepingAllowed(true);
		
		b2PolygonShape hShape;
		hShape.SetAsBox(0.05,0.05);
		
		b2FixtureDef fd;
		
		fd.shape = &hShape;
		fd.density = 1.0;
		fd.friction = 0.05;
		fd.restitution = 0.3;
		hammer->CreateFixture(&fd);
		
		c->setHammer(hammer);
		
	}

	void createSensors(ofPtr<chime> c){
		
		stemDims sd = c->getStemDims();
		
		b2Body * sensors[2] = {NULL,NULL};
		collisionData * sensorData[2] = {NULL,NULL};
		
		
		for(int i = 0; i < 2; i ++){
			
			if(c->getSensorOn(i)){
			
				ofVec2f tmp(0, 0); //will need to be set to offset
				tmp.y += (i == 0)? sd.length/2 : -sd.length/2;
				tmp.y += sd.offset * sd.length/2;
				tmp.rotateRad(sd.iAngle); //will need to pivot around offsetPoint
				
				b2BodyDef sdef;
				sdef.type = b2_dynamicBody;
				sdef.position.Set(tmp.x,tmp.y);
				sdef.angle = sd.iAngle;
				sdef.fixedRotation = false;
				
				sensors[i] = c->getWorld()->CreateBody(&sdef);
				sensors[i]->SetSleepingAllowed(true);
				
				b2PolygonShape sShape;
				sShape.SetAsBox(0.1,0.1);
				b2FixtureDef sfd;
				sfd.shape = &sShape;
				sfd.density = 1.0;
				sfd.restitution = 0.3;
				//sfd.isSensor = true;
				
				b2Fixture * b  = sensors[i]->CreateFixture(&sfd);
				
				sensorData[i] = new collisionData();
				sensorData[i]->mIndex = i;
				sensorData[i]->cIndex = c->getIndex();
				b->SetUserData(sensorData[i]);
			}
			
		}
		
		c->setSensors(&sensors[0]);
		c->setSensorData(&sensorData[0]);
		
	}




	void joinStemBodies(ofPtr<chime> c){
		
		stemDims sd = c->getStemDims();
		
		b2World * tw = c->getWorld();
		
		//stem
		
		b2Body * stem = c->getStemBody();
		
		//sensors
		
		b2Body * sensors[2];
		sensors[0] = c->getSensors()[0];
		sensors[1] = c->getSensors()[1];
		
		for(int i = 0; i < 2; i++){
			if(sensors[i]){
				b2WeldJointDef wd;
				wd.Initialize(sensors[i], stem,  sensors[i]->GetPosition());
				tw->CreateJoint(&wd);
			}
		}
		
		
		//hammer
		
		b2Body * hammer = c->getHammer();
		
		ofVec2f axis(0,1);
		axis.rotateRad(hammer->GetAngle());
		axis.normalize();
		
		b2PrismaticJointDef hjd;
		hjd.Initialize(hammer, stem,  hammer->GetPosition(), b2Vec2(-axis.x,-axis.y));
		hjd.lowerTranslation = -sd.length/2;
		hjd.upperTranslation = sd.length/2; 
		hjd.enableLimit = true;
		
		hjd.maxMotorForce = 0.07; //ofRandom(0,0.5);
		hjd.motorSpeed = 0.0f;
		hjd.enableMotor = true;
		
		tw->CreateJoint(&hjd);
		
	}
	
}
