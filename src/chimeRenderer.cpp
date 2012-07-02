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
vector<vector<ofPtr<ofImage> > >chimeRenderer::mEmptySensorSprite(3);
vector<vector<ofPtr<ofImage> > >chimeRenderer::mFilledSensorSprite(3);
vector<ofPtr<ofImage> > chimeRenderer::mEmptyHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mFilledHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mPivotSprite;

void chimeRenderer::loadSprites(){

	string filePath = "images/";
	string spriteNames[9] = {
						"stemSprite0","pivotSprite0", 
						"comboHammerSprite0",
						"comboSensorSprite0", 
						"comboSensorSprite1", 
						"comboSensorSprite2", 
						"filledSensorSprite0",
						"filledSensorSprite1",
						"filledSensorSprite2"
						};
	
	
	for(int s = 0; s < 9; s++){
		
		string path = filePath + spriteNames[s] + "/";
		ofDirectory dir(path);
		if(dir.exists()){
			
			int numFiles = dir.listDir();
			
			for(int i = 0; i < numFiles; i++){
				ofPtr<ofImage> img = ofPtr<ofImage>(new ofImage(path + spriteNames[s] + "_" + ofToString(i,0) + ".png"));
				switch(s){
					case 0:mStemSprite.push_back(img);break;
					case 1:mPivotSprite.push_back(img);break;
					case 2:mEmptyHammerSprite.push_back(img);
					case 3: case 4: case 5:mEmptySensorSprite[s - 3].push_back(img);break;
					case 6: case 7: case 8:mFilledSensorSprite[s - 6].push_back(img);break;
	
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

	if(c->getSpIndex() >= 99)return;
	
	b2Body * b = c->getStemBody();
	stemDims sd = c->getStemDims();
	float zt = c->getBlur()-(1.0 - 0.1);
	zt = (zt > 0) ? zt/0.1 * -25.0: 0;
	
	ofVec2f sp(sd.cPos);
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, zt); //maybe not needed (depends on offset)
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	glTranslatef(0, sd.offset * sd.length/2, 0);
	ofSetColor(100);
	mStemSprite[c->getSpIndex()]->draw(0,0,mStemSprite[c->getSpIndex()]->getWidth()/80, sd.length * 1.25);
	glPopMatrix();
	ofPopMatrix();
	
}

void chimeRenderer::drawHammer(ofPtr<chime> c){
	
	if(c->getSpIndex() >= 99)return;
	
	b2Body * b = c->getHammer();
	stemDims sd = c->getStemDims();
	float zt = c->getBlur()-(1.0 - 0.1);
	zt = (zt > 0) ? zt/0.1 * -25.0: 0;
	
	ofVec2f dim(mEmptyHammerSprite[c->getSpIndex()]->getWidth()/80.0f,
				mEmptyHammerSprite[c->getSpIndex()]->getHeight()/80.0f);
				
	dim *= 1.1;
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	glPushMatrix();
	glTranslatef(b->GetPosition().x, b->GetPosition().y, zt);
	glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	
	ofSetColor(255);
	mEmptyHammerSprite[c->getSpIndex()]->draw(0,0,dim.x,dim.y);
	
	glPopMatrix();
	ofPopMatrix();


}

void chimeRenderer::drawSensors(ofPtr<chime> c){
	
	if(c->getSpIndex() >= 99)return;
	
	b2Body ** b = c->getSensors();
	float zt = c->getBlur()-(1.0 - 0.1);
	zt = (zt > 0) ? zt/0.1 * -25.0: 0;
	stemDims sd = c->getStemDims();
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y, 0);
	

	
	for(int i = 0; i < 2; i++){
		
		 if(c->getSensorOn(i)){
			 
			 float sAlpha = c->getSensorAlpha(i);	
		 	 glPushMatrix();
			 glTranslatef(b[i]->GetPosition().x, b[i]->GetPosition().y, zt);
			 glRotatef(ofRadToDeg(b[i]->GetAngle()), 0, 0, 1);
			
			 ofColor col = c->getSensorColor(i);
			 
			 float frq =  0.5 + (1 - c->getSensorFreq(i)) * 3.0;
			 
			 int imgIndex = (frq < 0.75) ? 0 : (frq > 1.5) ? 2 : 1;
			 
			 float y_off = 0.1 * frq - 0.1;
			 y_off *= (i == 0)? 1 : -1;
			 
			 frq *= (imgIndex == 0) ? 2.0 : (imgIndex == 2) ? 0.5 : 1;
			 
			 ofVec2f dim_f(mFilledSensorSprite[imgIndex][c->getSpIndex()]->getWidth()/80.0f,
						   mFilledSensorSprite[imgIndex][c->getSpIndex()]->getHeight()/80.0f);
			 
			 ofVec2f dim_e(mEmptySensorSprite[imgIndex][c->getSpIndex()]->getWidth()/80.0f,
						   mEmptySensorSprite[imgIndex][c->getSpIndex()]->getHeight()/80.0f);
			 
			 dim_f.y *= frq;
			 dim_e.y *= frq;
			 
	
			 
			 ofFill();

			 
			 if(sAlpha > 0){
			 ofSetColor(col.r,col.g,col.b,sAlpha);
			 mFilledSensorSprite[imgIndex][c->getSpIndex()]->draw(0,y_off,dim_f.x,dim_f.y);
			 }
			 
			 
			 ofSetColor(255);
			 mEmptySensorSprite[imgIndex][c->getSpIndex()]->draw(0,y_off,dim_e.x,dim_e.y);
			 glPopMatrix();
		 
		 }
		
	}
	ofPopMatrix();
	
}


