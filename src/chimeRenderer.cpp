/*
 *  chimeRenderer.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeRenderer.h"

void chimeRenderer::draw(ofPtr<chime> c){
	
	drawAnchor(c);
	drawStem(c);
	drawPivots(c);
	drawSensors(c);
	drawHammer(c);


}

void chimeRenderer::drawAnchor(ofPtr<chime> c){
	
	b2Body *  b = c->getAnchor();
	
	ofFill();
	ofCircle(b->GetPosition().x, b->GetPosition().y, 0.025);
	
	
}

void chimeRenderer::drawPivots(ofPtr<chime> c){
	
	
	vector<b2Body*>b = c->getPivotBodies();
	vector<float> f = c->getPivotBodyDims();
	ofNoFill();
	
	for(int i =0; i < b.size(); i++){
	 
		 ofPushMatrix();
		 ofTranslate(b[i]->GetPosition().x,b[i]->GetPosition().y,0);
		 ofRotate(ofRadToDeg(b[i]->GetAngle()),0,0,1);
		 
		 ofRect(0,0,0.03,f[i]);
		 ofPopMatrix();
		
	}
	
}

void chimeRenderer::drawStem(ofPtr<chime> c){

	b2Body * b = c->getStem();
	float l = c->getStemLength();
	
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0);
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	ofSetColor(100);
	ofLine(0, -l/2, 0, l/2);
	glPopMatrix();
	
	
}

void chimeRenderer::drawHammer(ofPtr<chime> c){
	
	b2Body * b = c->getHammer();
	float a = c->getHammerAlpha();	
		
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0);
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	
	ofSetColor(255);
	ofFill();
	ofRect(0,0, 0.2, 0.2);
	
	ofEnableAlphaBlending();
	ofFill();
	ofSetColor(255,0,0, a);
	ofRect(0,0, 0.2, 0.2);
	ofDisableAlphaBlending();
	
	
	ofSetColor(0);
	ofNoFill();
	ofRect(0,0, 0.2, 0.2);
	glPopMatrix();
	
	

}

void chimeRenderer::drawSensors(ofPtr<chime> c){
	
	b2Body ** b = c->getSensors();
	
	ofSetColor(0);
	
	for(int i = 0; i < 2; i++){
		
		 if(b[i]){
		 
			 ofFill();
			 glPushMatrix();
			 glTranslatef(b[i]->GetPosition().x, b[i]->GetPosition().y, 0);
			 glRotatef(ofRadToDeg(b[i]->GetAngle()), 0, 0, 1);
			 ofRect(0,0, 0.1, 0.1);
			 glPopMatrix();
		 
		 }
		
	}
	
}


