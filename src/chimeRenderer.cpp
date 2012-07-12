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
vector<vector<ofPtr<ofImage> > >chimeRenderer::mAlphaSensorSprite(3);
vector<vector<ofPtr<ofImage> > >chimeRenderer::mEmptySensorSprite(3);
vector<vector<ofPtr<ofImage> > >chimeRenderer::mFilledSensorSprite(3);
vector<ofPtr<ofImage> > chimeRenderer::mEmptyHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mFilledHammerSprite;
vector<ofPtr<ofImage> > chimeRenderer::mPivotSprite;

void chimeRenderer::loadSprites(){

	string filePath = "images/";
	string spriteNames[12] = {
						"stemSprite0","pivotSprite0", 
						"comboHammerSprite0",
						"comboSensorSprite0", 
						"comboSensorSprite1", 
						"comboSensorSprite2", 
						"filledSensorSprite0",
						"filledSensorSprite1",
						"filledSensorSprite2",
						"emptySensorSprite0",
						"emptySensorSprite1",
						"emptySensorSprite2"
						};
	
	
	for(int s = 0; s < 12; s++){
		
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
					case 3: case 4: case 5:mAlphaSensorSprite[s - 3].push_back(img);break;
					case 6: case 7: case 8:mFilledSensorSprite[s - 6].push_back(img);break;
					case 9: case 10: case 11:mEmptySensorSprite[s - 9].push_back(img);break;
	
				}
			}
			
		}else{
			cout << "directory not found \n";
	
		}
	}
	

}

void chimeRenderer::draw(ofPtr<chime> c){
	
	//drawAnchor(c);
	//drawPivots(c);
	drawStem(c);
	drawSensors(c);
	drawHammer(c);


}

void chimeRenderer::drawAnchor(ofPtr<chime> c){
	
	ofVec2f ap(c->getAnchorPos());
	
	ofNoFill();
	ofCircle(ap.x,ap.y, 0.03);
	
	
}

void chimeRenderer::drawPivots(ofPtr<chime> c){
	
	vector<float> pivRots(c->getPivotRots());
	ofVec2f ap(c->getAnchorPos());
	
	float l = c->getModParam(CH_PIV_LGTH)/c->getModParam(CH_PIV_NUM);
	
	ofSetColor(150);
	
	ofPushMatrix();
	
	ofTranslate(ap.x, ap.y, 0);
	
	for(int i = 0; i < c->getModParam(CH_PIV_NUM); i++){
		
		ofRotate(ofRadToDeg(pivRots[i]),0,0,1);
		ofTranslate(0, l/2, 0);
		mPivotSprite[c->getSpIndex()]->draw(0,0,mPivotSprite[c->getSpIndex()]->getWidth()/80, l * 1.25);
		ofTranslate(0, l/2, 0);
		
	}
	
	ofPopMatrix();

}

void chimeRenderer::drawStem(ofPtr<chime> c){

	//if(c->getSpIndex() >= 99)return;
	
	b2Body * b = c->getStemBody();
	stemDims sd = c->getStemDims();
	float zt = c->getBlur()-(1.0 - 0.1);
	zt = (zt > 0) ? zt/0.1 * -25.0: 0;
	
	ofVec2f sp(sd.cPos);
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
		glPushMatrix();
		glTranslatef(b->GetPosition().x, b->GetPosition().y, zt);
		glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
		ofSetColor(100);
		mStemSprite[c->getSpIndex()]->draw(0,0,mStemSprite[c->getSpIndex()]->getWidth()/80, c->getModParam(CH_LENGTH) * 1.25);
		glPopMatrix();
	ofPopMatrix();
	
}

void chimeRenderer::drawHammer(ofPtr<chime> c){
	
	//if(c->getSpIndex() >= 99)return;
	
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
	
	//if(c->getSpIndex() >= 99)return;
	
	b2Body ** b = c->getSensors();
	float zt = c->getBlur()-(1.0 - 0.1);
	zt = (zt > 0) ? zt/0.1 * -25.0: 0;
	stemDims sd = c->getStemDims();
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y, 0);
	
	
	for(int i = 0; i < 2; i++){
		
		
		 float sAlpha = c->getSensorAlpha(i);	
		 glPushMatrix();
		 glTranslatef(b[i]->GetPosition().x, b[i]->GetPosition().y, zt);
		 glRotatef(ofRadToDeg(b[i]->GetAngle()), 0, 0, 1);
		
		 ofColor col = c->getSensorColor();
		 
		 float frq =  0.5 + (1 - c->getSensorHeight()) * 3.0;
		 
		 int imgIndex = (frq < 0.75) ? 0 : (frq > 1.5) ? 2 : 1;
		 
		 float y_off = 0.1 * frq - 0.1;
		 y_off *= (i == 0)? 1 : -1;
		 
		 frq *= (imgIndex == 0) ? 2.0 : (imgIndex == 2) ? 0.5 : 1;
		 
		 ofVec2f dim_f(mFilledSensorSprite[imgIndex][c->getSpIndex()]->getWidth()/80.0f,
					   mFilledSensorSprite[imgIndex][c->getSpIndex()]->getHeight()/80.0f);
		 
		 ofVec2f dim_e(mAlphaSensorSprite[imgIndex][c->getSpIndex()]->getWidth()/80.0f,
					   mAlphaSensorSprite[imgIndex][c->getSpIndex()]->getHeight()/80.0f);
		 
		 dim_f.y *= frq;
		 dim_e.y *= frq;
		 

		 
		 ofFill();

		 
		 if(sAlpha > 0){
		 ofSetColor(col.r,col.g,col.b,sAlpha);
		 mFilledSensorSprite[imgIndex][c->getSpIndex()]->draw(0,y_off,dim_f.x,dim_f.y);
		 }
		 
		 
		 ofSetColor(255);
		 mAlphaSensorSprite[imgIndex][c->getSpIndex()]->draw(0,y_off,dim_e.x,dim_e.y);
		 glPopMatrix();
		 
		 
		
	}
	ofPopMatrix();
	
}

void chimeRenderer::drawHighlight(ofPtr<chime> c, ofColor col){
	
	b2Body * b = c->getStemBody();
	stemDims sd = c->getStemDims();

	ofFill();
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
		glPushMatrix();
		glTranslatef(b->GetPosition().x, b->GetPosition().y, 0);
		glRotatef(ofRadToDeg(b->GetAngle()), 0, 0, 1);
		
	ofSetColor(col);
	ofRect(0,0, 0.1,c->getModParam(CH_LENGTH) * 1.25);

		
		glPopMatrix();
	ofPopMatrix();
	


}

void chimeRenderer::drawOutline(ofPtr<chime> c, ofColor col){
	
	b2Body * stem = c->getStemBody();
	stemDims sd = c->getStemDims();
	b2Body ** sens = c->getSensors();
	
	ofVec2f sens_pos[2];
	float sens_ang[2];
	
	float st_ang = (stem)? stem->GetAngle() : sd.iAngle;
		
	
	ofPushMatrix();
	ofTranslate(sd.cPos.x,sd.cPos.y,0);
	
		glPushMatrix();
		glRotatef(ofRadToDeg(st_ang), 0, 0, 1);
		

	ofSetColor(col);
	mStemSprite[min(c->getSpIndex(),10)]->draw(0,0,mStemSprite[0]->getWidth()/80, c->getModParam(CH_LENGTH) * 1.25);
		
		glPopMatrix();
	
	
		for(int i = 0; i < 2; i++){
			
			
				
				if(sens[i]){
					sens_pos[i].set(sens[i]->GetPosition().x, sens[i]->GetPosition().y);
					sens_ang[i] = sens[0]->GetAngle();
				}else{
					
					sens_pos[i].set(0, 0); 
					sens_pos[i].y += (i == 0)? c->getModParam(CH_LENGTH)/2 : -c->getModParam(CH_LENGTH)/2;
					sens_pos[i].rotateRad(st_ang); 
					sens_ang[i] = st_ang;
				
				}
				
				glPushMatrix();
				glTranslatef(sens_pos[i].x,sens_pos[i].y, 0);
				glRotatef(ofRadToDeg(sens_ang[i]), 0, 0, 1);
				
				float frq =  0.5 + (1 - c->getSensorHeight()) * 3.0;
				
				int imgIndex = (frq < 0.75) ? 0 : (frq > 1.5) ? 2 : 1;
				
				float y_off = 0.1 * frq - 0.1;
				y_off *= (i == 0)? 1 : -1;
				
				frq *= (imgIndex == 0) ? 2.0 : (imgIndex == 2) ? 0.5 : 1;
				
				
				ofVec2f dim_e(mAlphaSensorSprite[imgIndex][0]->getWidth()/80.0f,
							  mAlphaSensorSprite[imgIndex][0]->getHeight()/80.0f);

				dim_e.y *= frq;
				
				ofSetColor(col);
				mEmptySensorSprite[imgIndex][0]->draw(0,y_off,dim_e.x,dim_e.y);
				glPopMatrix();
				
			
			
		}
	ofPopMatrix();

}



