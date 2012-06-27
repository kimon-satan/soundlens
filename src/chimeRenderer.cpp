/*
 *  chimeRenderer.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "chimeRenderer.h"

vector<ofPtr<ofImage> > chimeRenderer::mStemSprite;
vector<ofPtr<ofImage> > chimeRenderer::mEmptySensorSprite;
vector<ofPtr<ofImage> > chimeRenderer::mFilledSensorSprite;
vector<ofPtr<ofImage> > chimeRenderer::mEmptyHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mFilledHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mPivotSprite;

void chimeRenderer::loadSprites(){

	string filePath = "images/";
	string spriteNames[6] = {"stemSprite0", "emptySensorSprite0", "filledSensorSprite0", 
						"emptyHammerSprite0" ,"pivotSprite0", "filledHammerSprite0"};
	
	for(int s = 0; s < 6; s++){
		
		string path = filePath + spriteNames[s] + "/";
		ofDirectory dir(path);
		if(dir.exists()){
			
			int numFiles = dir.listDir();
			
			for(int i = 0; i < numFiles; i++){
				ofPtr<ofImage> img = ofPtr<ofImage>(new ofImage(path + spriteNames[s] + "_" + ofToString(i,0) + ".png"));
				switch(s){
					case 0:mStemSprite.push_back(img);break;
					case 1:mEmptySensorSprite.push_back(img);break;
					case 2:mFilledSensorSprite.push_back(img);break;
					case 3:mEmptyHammerSprite.push_back(img);break;
					case 4:mPivotSprite.push_back(img);break;
					case 5:mFilledHammerSprite.push_back(img);break;
				}
			}
			
		}else{
			cout << "directory not found \n";
	
		}
	}
	

}

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
	
	ofSetColor(150);
	
	ofPushMatrix();
	
	ofTranslate(ap.x, ap.y, 0);
	
	for(int i = 0; i < pds.size(); i++){
		
		ofRotate(ofRadToDeg(pds[i].cRot),0,0,1);
		ofTranslate(0, pds[i].d/2, -3);
		mPivotSprite[c->getSpIndex()]->draw(0,0,mPivotSprite[c->getSpIndex()]->getWidth()/80, pds[i].d * 1.25);
		ofTranslate(0, pds[i].d/2, 0);
		
	}
	
	ofPopMatrix();

}

void chimeRenderer::drawStem(ofPtr<chime> c){

	b2Body * b = c->getStemBody();
	stemDims sd = c->getStemDims();
	
	ofVec2f sp(sd.cPos);
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,-2);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0); //maybe not needed (depends on offset)
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	glTranslatef(0, sd.offset * sd.length/2, 0);
	ofSetColor(100);
	mStemSprite[c->getSpIndex()]->draw(0,0,mStemSprite[c->getSpIndex()]->getWidth()/80, sd.length * 1.25);
	glPopMatrix();
	ofPopMatrix();
	
}

void chimeRenderer::drawHammer(ofPtr<chime> c){
	
	b2Body * b = c->getHammer();
	stemDims sd = c->getStemDims();
	
	float dim = mEmptyHammerSprite[c->getSpIndex()]->getWidth()/80.0f;
	dim *= 1.1;
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,-1);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, 0);
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	
	ofFill();
	ofSetColor(255,255);
	mFilledHammerSprite[c->getSpIndex()]->draw(0,0,dim,dim);
	
	ofSetColor(0);
	mEmptyHammerSprite[c->getSpIndex()]->draw(0,0,dim,dim);
	
	glPopMatrix();
	ofPopMatrix();


}

void chimeRenderer::drawSensors(ofPtr<chime> c){
	
	b2Body ** b = c->getSensors();
	
	
	stemDims sd = c->getStemDims();
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	
	float dim = mFilledSensorSprite[c->getSpIndex()]->getWidth()/80.0f;
	dim *= 1.2;
	
	for(int i = 0; i < 2; i++){
		
		 if(c->getSensorOn(i)){
			 
			 float a = c->getSensorAlpha(i);	
		 	 glPushMatrix();
			 glTranslatef(b[i]->GetPosition().x, b[i]->GetPosition().y, 0);
			 glRotatef(ofRadToDeg(b[i]->GetAngle()), 0, 0, 1);
			
			 ofColor col = c->getSensorColor(i);
			 
			 ofFill();
			 ofSetColor(255,255);
			 mFilledSensorSprite[c->getSpIndex()]->draw(0,0,dim,dim);
			 
			 ofFill();
			 ofSetColor(col.r,col.g,col.b,a);
			 mFilledSensorSprite[c->getSpIndex()]->draw(0,0,dim,dim);
			 
			 
			 ofSetColor(50);
			 mEmptySensorSprite[c->getSpIndex()]->draw(0,0,dim,dim);
			 glPopMatrix();
		 
		 }
		
	}
	ofPopMatrix();
	
}


