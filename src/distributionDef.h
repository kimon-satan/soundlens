/*
 *  distributionDef.h
 *  testBed1
 *
 *  Created by Simon Katan on 02/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "dataElement.h"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

enum e_distributionType{
	
	DT_NONE,
	DT_STEP,
	DT_SLICE,
	DT_FLAT,
	DT_NORMAL,
	DT_CHOOSE,
	DT_SEQ,
	DT_COUNT,
	
};


enum e_distDefParam{

	DD_UNIT,
	DD_RNG,
	DD_DEV,
	DD_COUNT,
		
};


template <class T>

class distributionDef{
	
public:
	
	distributionDef(){
	
		
		for(int i = 0; i < DD_COUNT; i++){
			dataElement<float> fp;
			fp.abs_val = 0;
			switch (i) {
				case DD_UNIT:
					fp.name = "unit";
					break;
				case DD_RNG:
					fp.name = "rng";
					break;
				case DD_DEV:
					fp.name = "dev";
					break;
			}
			
			floatParams.push_back(fp);
		}
	
		dType = DT_NONE;
		name = "";
		numVals = 1;
	
		
	};	
	
	string setUserValues(float ua, float ub){
		
		string pString = "";
		
		pString += initVal.setUserValues(ua,ub);
		
		for(int i = 0; i < floatParams.size(); i++)pString += floatParams[i].setUserValues(ua,ub);
		
		if(pString != ""){return name + ": " + pString + "\n";}else{return "";}
	
	};
	
	
	float getVal(int param){return floatParams[param].abs_val;};
	void setVal(int param, float val){floatParams[param].set(val);};
	void setVal(int param, float mnV, float mxV, int setType){floatParams[param].set(mnV, mxV, setType);};
	
	void setRngVec(ofVec2f val){rngVec.set(val);};
	ofVec2f getRngVec(){return rngVec;};
	
	T getInitVal(){return initVal.abs_val;};
	void setInitVal(T val){initVal.set(val);};
	void setInitVal(T mnV, T mxV, int setType){initVal.set(mnV, mxV, setType);};
	
	int getNumVals(){return numVals;};
	void setNumVals(int i){numVals = i;};
	
	vector<T> getLocalVals(){return localVals;};
	void setLocalVals(vector<T> lv){localVals = lv;};
	
	int getDType(){return dType;};
	void setDType(int i){dType = i;};
	
	string getName(){return name;}
	void setName(string s){name = s;}
	
	private:
	
	int numVals;
	
	dataElement<T> initVal;
	vector<dataElement<float> >floatParams; 
	ofVec2f rngVec;
	
	string name;
	vector<T> localVals;
	int dType;
	
};


