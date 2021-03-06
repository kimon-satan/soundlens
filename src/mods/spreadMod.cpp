/*
 *  spreadMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 07/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "spreadMod.h"

bool chimeSorter::operator()(ofPtr<chime> a, ofPtr<chime> b){
	
	if(param == CH_PHASE){
		return fmod(a->getFixedParam(param),b2_pi) < fmod(b->getFixedParam(param), b2_pi);
	}else{
		return a->getFixedParam(param) < b->getFixedParam(param);
	}
	
}



spreadMod::spreadMod(int i){
	
	
	paramType = i;
	name = "spread";
	

	if(paramType == -1){
		name += "_preserve";
	}else if(paramType == -2){
		name += "_shuffle";
	}else{
		name += "_" + chime::getChFixedString(paramType);
	}
	
	
	dataElement<float> rng;
	rng.name = "rng";
	rng.set(1.0,20.0, SET_USER_A);
	floatParameters.push_back(rng);
	
	dataElement<float> ang;
	ang.name = "ang";
	ang.set(360,0,SET_USER_B);
	floatParameters.push_back(ang);
	
}

vector<ofPtr<chime> > spreadMod::makeMod(vector<ofPtr<chime> > chimes, bool isAuto){
	
	vector<ofPtr<chime> >::iterator it;
	
	if(paramType >= 0){
	
		//sort the chimes according to param
		sort(chimes.begin(), chimes.end(), chimeSorter(paramType));
		
	}else if(paramType == -2){
		
		random_shuffle(chimes.begin(), chimes.end());
		
	}
	
	vector<ofVec2f> nPos;
	
	ofVec2f vec(0, floatParameters[0].abs_val);
	vec.rotate(floatParameters[1].abs_val);
	
	distributionDef <ofVec2f>dDef;
	dDef.setNumVals((int)chimes.size());
	dDef.setDType(DT_SLICE);
	dDef.setRngVec(vec);
	dDef.setInitVal(mDown - vec/2);
	
	distributionEngine::makeValues(nPos, dDef);
	
	//now get the longest distance of travel
	
	float longDist = 0;
	vector<float> distances;
	
	int count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		
		float d = (*it)->getAnchorPos().distance(nPos[count]);
		if(d > longDist)longDist = d;
		distances.push_back(d);
		count++;
		
	}
	
	count = 0;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
		float inc = 0.02 * distances[count]/longDist;
		(*it)->setAnchorTarget(nPos[count], inc, isAuto);
		count ++;
	}
	
	return chimes;
	
}

void spreadMod::drawControl(float dragDist, float dragAngle){

	ofSetColor(150);
	ofPushMatrix();
	ofNoFill();
	ofCircle(mDown, 0.2);
	ofTranslate(mDown.x, mDown.y, 0);
	ofRotate(floatParameters[1].abs_val,0,0,1);
	ofLine(0,-floatParameters[0].abs_val/2 , 0, floatParameters[0].abs_val/2);
	ofPopMatrix();
	
}