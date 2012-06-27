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
	
	ofVec2f ap(c->getAnchorPos());
	
	ofNoFill();
	ofCircle(ap.x,ap.y, 0.03);
	
	
}

void chimeRenderer::drawPivots(ofPtr<chime> c){
	
	vector<pivotDims> pds(c->getPivotDims());
	ofVec2f ap(c->getAnchorPos());
	
	ofSetColor(70);
	
	ofPushMatrix();
	
	ofTranslate(ap.x, ap.y, 0);
	
	for(int i = 0; i < pds.size(); i++){
		
		ofRotate(ofRadToDeg(pds[i].cRot),0,0,1);
		ofTranslate(0, pds[i].d/2, 0);
		ofRect(0,0,0.02,pds[i].d);
		ofTranslate(0, pds[i].d/2, 0);
		
	}
	
	ofPopMatrix();

}

void chimeRenderer::drawStem(ofPtr<chime> c){

	b2Body * b = c->getStemBody();
	stemDims sd = c->getStemDims();
	
	ofVec2f sp(sd.cPos);
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0); //maybe not needed (depends on offset)
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	ofSetColor(150);
	ofLine(0, -sd.length/2, 0, sd.length/2);
	glPopMatrix();
	ofPopMatrix();
	
}

void chimeRenderer::drawHammer(ofPtr<chime> c){
	
	b2Body * b = c->getHammer();
	stemDims sd = c->getStemDims();
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0);
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	
	ofSetColor(0);
	ofFill();
	ofRect(0,0, 0.1, 0.1);
	
	glPopMatrix();
	ofPopMatrix();


}

void chimeRenderer::drawSensors(ofPtr<chime> c){
	
	b2Body ** b = c->getSensors();
	float a = c->getHammerAlpha();	
	
	ofSetColor(0);
	
	stemDims sd = c->getStemDims();
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	
	for(int i = 0; i < 2; i++){
		
		 if(b[i]){
			 
			 
		 	 glPushMatrix();
			 glTranslatef(b[i]->GetPosition().x, b[i]->GetPosition().y, 0);
			 glRotatef(ofRadToDeg(b[i]->GetAngle()), 0, 0, 1);
			
			 
			 ofPushStyle();
			 ofFill();
			 ofSetColor(255,0,0,a);
			 ofEnableAlphaBlending();
			 ofRect(0,0, 0.2, 0.2);
			 ofPopStyle();
			 
			 
			 ofNoFill();
			 ofRect(0,0, 0.2, 0.2);
			 glPopMatrix();
		 
		 }
		
	}
	ofPopMatrix();
	
}


