/*
 *  redistributeMod.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 12/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "redistributeMod.h"

redistributeMod::redistributeMod(int pt, int dt){

	paramType = pt;
	
	distType = dt;
	
	string dNames[7] = {"single", "step", "slice", "flat", "normal", "shuffle", "seq"};
	
	name += "rd_"  + dNames[distType] + "_"+ chime::getChParamString(paramType);
	
	string paramBNames[7] = {"rngMul", "ovrlp", "dev", "unit", "unit", "", "seqSize"};
	
	float paramBRanges[7][2] ={
		{0,1},
		{1,3},
		{0,1},
		{0,0}, //unit will need to change according to parameter type
		{0,0},
		{0,0},
		{2,10}
		
	};
	
	
	dataElement<float> dataA;
	dataElement<float> dataB;
	
	dataA.name = "inc";
	dataA.set(0.01,1.0, SET_USER_A); //might need to be set per param type
	floatParameters.push_back(dataA);
	
	dataB.name = paramBNames[distType];
		
	if(dataB.name != ""){
		
		if(distType == DT_FLAT || distType == DT_NORMAL){
		
			//choose suitable unit ranges and increments
			switch(paramType){
					
				case CH_PHASE:
					dataB.set(1,64, SET_USER_B); 
					dataB.incr = 1;
					 break;
				case CH_SPEED:
					dataB.set(0,1,SET_USER_B); 
					 break;
				case CH_FREQ:
					dataB.set(0.25,6,SET_USER_B); 
					 break;
				case CH_DECAY:
					dataB.set(0.01,0.2, SET_USER_B); 
					 break;
			
			}
			
		}else{
		
			dataB.set(paramBRanges[distType][0],paramBRanges[distType][1], SET_USER_B); 
		}
		
		floatParameters.push_back(dataB);
	}

	
	
	

}


void redistributeMod::makeMod(vector<ofPtr<chime> > chimes){

	if(chimes.size() < 1)return;
	
	vector<ofPtr<chime> >::iterator it;
	
	vector<float> oldVals;
	vector<float> seqVals;
	
	//extreme for param
	float ub = chimes[0]->getModParam(paramType);
	float lb = ub;
	
	for(it = chimes.begin(); it != chimes.end(); it++){
	
		float f = (*it)->getModParam(paramType);
		if(f > ub)ub = f;
		if(f < lb)lb = f;
		oldVals.push_back(f);
	
	}
	
	float rng = ub - lb;
	float median = lb + rng/2;
	
	int numVals = (int) chimes.size();
	
	//set up a seq if necessary
	
	if(distType == DT_SEQ){
		int numSeqVals = min((int)floatParameters[1].abs_val, numVals);
		int seqBegin = floor(ofRandom(0, numVals - numSeqVals));
		for(int i = 0; i < numSeqVals; i++)seqVals.push_back(oldVals[seqBegin + i]);
	}
	
	//single -  congregate on val (b: where in the range 0=>1)
	//step - spread values evenly across the range (b: modulo point - creates a repeating pattern)
	//slice - spread values evenly across range (b: deviation ?)
	//flat - random within range bounds (b: increment - as in min unit)
	//normal - likewise (b: increment)
	//shuffle - choose choose randomly from the old values (with repetition data will be lost)(b: none)
	//seq - choose a contiguous segment and repeat across the whole sample (b: segment size)
	
	//get the new values
	
	distributionDef <float> dDef;
	dDef.setDType(distType);
	dDef.setNumVals(numVals);
	
	switch (distType) {
		case DT_NONE:
			dDef.setInitVal(lb + rng * floatParameters[1].abs_val); 
			break;
		case DT_STEP:
			dDef.setInitVal( lb);
			dDef.setVal(DD_UNIT, rng/chimes.size() * floatParameters[1].abs_val); //determines amount of overlap
			dDef.setVal(DD_RNG,rng);
			break;
		case DT_SLICE:
			dDef.setInitVal( lb);
			dDef.setVal(DD_DEV, floatParameters[1].abs_val);
			dDef.setVal( DD_RNG, rng);
			break;
		case DT_FLAT:
			dDef.setInitVal( median);
			dDef.setVal( DD_UNIT,floatParameters[1].abs_val); //min val
			dDef.setVal( DD_RNG, rng); //nb meaning of rng has changed
			break;
		case DT_NORMAL:
			dDef.setInitVal(median);
			dDef.setVal( DD_UNIT,floatParameters[1].abs_val);
			dDef.setVal( DD_RNG, rng);
			break;
		case DT_CHOOSE:
			dDef.setLocalVals(oldVals);
			break;
		case DT_SEQ:
			dDef.setLocalVals(seqVals);
			break;
		default:
			break;
	}

	vector<float> nVals;
	
	distributionEngine::makeValues(nVals, dDef);
	
	
	//work out the incMuls
	
	
	//assign the new targets



}

void redistributeMod::drawControl(float dragDist, float dragAngle){


	ofSetColor(150);
	ofLine(mDown.x, mDown.y, mDrag.x, mDrag.y);
	ofNoFill();
	ofCircle(mDown, 0.2);
	
}