/*
 *  copyMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "copyMod.h"

copyMod::copyMod(bool g_i, bool p_i, vector<int> params){

	name = "normal - ";
	if(!g_i)name += "gLinked ";
	if(!p_i)name += "pLinked ";
	
	for(int i = 0; i < params.size(); i++)name += chime::getChParamString(params[i]) + ",";
	
	
	dataElement <float> rng;
	rng.name = "range";
	rng.set(0,1.0,SET_USER_A); //will need adjusting according to parameter
	
	dataElement <float> dev;
	dev.name = "deviation";
	dev.set(0.01,0.4,SET_USER_B);
	
	floatParameters.push_back(rng);
	floatParameters.push_back(dev);
	
	for(int i = 0; i < 5; i++){
		bool b = false;
		for(int j = 0; j < params.size(); j++){
			if(params[j] == i){
				b = true;
				break;
			}
		}
		mMuteParams.push_back(b);
	}
	
	isGroupInd = g_i;
	isParamInd = p_i;
	
}


vector<ofPtr<chime> >copyMod::makeMod(vector<ofPtr<chime> > chimes){

	vector<ofPtr<chime> >::iterator it;
	
	vector<ofPtr<chime> > nChimes;
	
	//make the coefficient values
	
	vector<vector<float > > mutateCoeffs;
	
	distributionDef <float> dDef;
	dDef.setDType(DT_NORMAL);
	dDef.setInitVal(0);
	dDef.setVal( DD_RNG, floatParameters[0].abs_val);
	dDef.setVal( DD_DEV, floatParameters[1].abs_val);
	dDef.setNumVals( (isGroupInd) ? chimes.size() : 1);
	
	int pBins = (isParamInd) ? 5 : 1;
	
	for(int i = 0; i < pBins; i++){
	
		vector<float> coeffs;
		distributionEngine::makeValues(coeffs, dDef);
		mutateCoeffs.push_back(coeffs);
	}
	
	
	int count = 0;
	
	// copy and assign
	float ranges[] = {b2_pi, 1.0, 1.0, 3.0, 1.0};
	
	//freq can eventually be set by tuning coefficient
	
	
	for(it = chimes.begin(); it != chimes.end(); it++){
	
		ofPtr<chime> c = ofPtr<chime>(new chime());
		
		for(int i = 0; i < 5; i++){
			
			if(!mMuteParams[i]){
				c->setModParam(i, (*it)->getModParam(i));
			}else{
				
				//assign bins according to independence
				
				int pBin = (isParamInd) ? i : 0;
				int cBin = (isGroupInd) ? count : 0;
				
				c->setModParam(i, (*it)->getModParam(i) + ranges[i] * mutateCoeffs[i][count]);
				
				
			}
		}
		
		for(int i = 6; i < CH_FLOAT_COUNT; i++)c->setModParam(i, (*it)->getModParam(i));
			
		c->setAnchorPos((*it)->getAnchorPos());
		c->setAnchorTarget((*it)->getAnchorPos() + 8.0, 0.01, false);
		(*it)->setAnchorTarget((*it)->getAnchorPos() - 8.0, 0.01, false);
		c->setSensorColor((*it)->getSensorColor());
		c->setZpos((*it)->getZpos()); //potentially not
	
		nChimes.push_back(c);
		count ++;
	}
	
	//returns unInitialisedCopies
	
	return nChimes;
	
}

void copyMod::drawControl( float dragDist, float dragAngle){
	
	ofNoFill();
	ofSetColor(150);
	ofCircle(mDown,0.5);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);


}