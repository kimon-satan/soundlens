
#include "allCopiers.h"

/*
 *  allCopiers.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "allCopiers.h"

allCopiers::allCopiers(){
	
	
}


void allCopiers::beginCopy(copyPreset cp){

	//make the necessary copiers
	
	copiers.clear();
	
	for(int i = 0; i < cp.copiers.size(); i++){
		
		if(cp.copiers[i].copierType == CP_TRANSPOSE){ 
			
			ofPtr<transpose> ncpy = ofPtr<transpose>(new transpose(cp.copiers[i]));
			copiers.push_back((ofPtr<baseCopy>)ncpy);
			
		}else if(cp.copiers[i].copierType == CP_MUTATE){ 
			
			ofPtr<mutate> ncpy = ofPtr<mutate>(new mutate(cp.copiers[i]));
			copiers.push_back((ofPtr<baseCopy>)ncpy);
			
		}else if(cp.copiers[i].copierType == CP_ROTATE){ 
		}else if(cp.copiers[i].copierType == CP_SHUFFLE){ 
		}else if(cp.copiers[i].copierType == CP_INVERT){ 
		}else if(cp.copiers[i].copierType == CP_REVERSE){ 
		}else if(cp.copiers[i].copierType == CP_EXPAND){ 
		}else if(cp.copiers[i].copierType == CP_CONTRACT){ 
		}else if(cp.copiers[i].copierType == CP_SIEVE){ 
		}
		
	}
	
}

vector <ofPtr<chime> > allCopiers::getCopies(vector<ofPtr<chime> > targetGrp){
	
	
	if(targetGrp.size() < 1)return targetGrp;
	
	vector<ofPtr<chime> >::iterator it;
	
	int oldGen = targetGrp[0]->getGeneration();
	
	float fp = chimeUpdater::getFocalPoint();
	
	for(it = targetGrp.begin(); it != targetGrp.end(); it++){
		if((*it)->getGeneration() < oldGen)oldGen = (*it)->getGeneration(); 
		
		float d = fp - (*it)->getZpos();
		
		if(fp > 1){
			if(d < 0)(*it)->setZpos(fp - d);
		}else{
			if(d > 0)(*it)->setZpos(fp + d);
		}
		
	}
	
	//bad access here not sure why 16/07
	vector<ofPtr<chime> > nGrp = targetGrp;
	
	for(int i = 0; i < copiers.size(); i ++){
		nGrp = copiers[i]->getCopies(nGrp);
	}
	
	int nGen = oldGen + 1;
	float hue = 255 - (nGen * 5)%255;
	
	for(it = nGrp.begin(); it != nGrp.end(); it++){
		(*it)->setGeneration(nGen);	
		(*it)->setFixedParam(CH_COLOR,hue);
		(*it)->setZpos((fp > 1) ? fp - 0.5 : fp + 0.5);
	}
	
	
	nGrp = shiftMod::makeMod(nGrp, mDown, 0.03, false);
	
	return nGrp;
	
}


void allCopiers::drawPreview(float dragDist, float dragAngle){
	
	float d = 0.5 + dragDist * 3.0f;
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,d);
	ofVec2f p(mDown + ofVec2f(0,d));
	p.rotate(-360 * dragAngle, mDown);
	ofLine(mDown.x, mDown.y, p.x, p.y);
	
}

string allCopiers::updateUserValues(ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string rs = "";
	
	for(int i = 0; i < copiers.size(); i++){
		string s = copiers[i]->setUserData(mD, mDr, ua, ub);
		
		if(s != "")rs += s + "\n";
	}
	
	mDown.set(mD);
	mDrag.set(mDr);
	
	return rs;
	
}

