
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
	
	
	int singleMutes[] = {CH_PHASE, CH_SPEED, CH_FREQ};
	
	
	for(int i = 0; i < 3; i ++){
		vector<int> params;
		params.push_back(singleMutes[i]);
		ofPtr<transpose> cpm = ofPtr<transpose>(new transpose(params));
		copiers.push_back((ofPtr<baseMod>)cpm);
	}
	
	
	vector<int> params;
	params.push_back(singleMutes[0]);
	params.push_back(singleMutes[2]);
	ofPtr<transpose> cpm = ofPtr<transpose>(new transpose(params));
	copiers.push_back((ofPtr<baseMod>)cpm);
	

	
	
}


vector <ofPtr<chime> > allCopiers::getCopies(int copyType, vector<ofPtr<chime> > targetGrp){
	
	
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
	vector<ofPtr<chime> > nGrp = copiers[copyType]->makeMod(targetGrp);
	
	int nGen = oldGen + 1;
	float hue = 255 - (nGen * 5)%255;
	
	for(it = nGrp.begin(); it != nGrp.end(); it++){
		(*it)->setGeneration(nGen);	
		(*it)->setFixedParam(CH_COLOR,hue);
		(*it)->setZpos((fp > 1) ? fp - 0.5 : fp + 0.5);
	}
	
	
	return nGrp;
	
}


void allCopiers::drawPreview(int copyType, float dragDist, float dragAngle){
	
	copiers[copyType]->drawControl(dragDist, dragAngle);
	
}

string allCopiers::updateUserValues(int copyType, ofVec2f mD, ofVec2f mDr, float ua, float ub){
	
	string s = "";
	s = copiers[copyType]->setUserData(mD, mDr, ua, ub);
	return s;
	
}

string allCopiers::getCopyName(int i){return copiers[i]->getName();}
