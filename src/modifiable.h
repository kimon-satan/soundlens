/*
 *  modifiable.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

template <class T>

class modifiable{

	public:
	
	modifiable(){
		
		isAuto = false;
		increment  = 0;
		flagChanged = false;
		
	};
	
	void set(T t){
		cVal = t;
		tVal = t;
		increment = 0;
	};
	
	void setTarget(T t, float i, bool b){
		tVal = t;
		increment = i;
		isAuto = b;

	};
	
	T getCVal(){return cVal;}
	
	
	void end(){tVal = cVal; increment = 0;}

	void shiftValue(int direction){
	
		if(abs(increment) > 0){
			
			if(cVal <= tVal - increment || cVal >= tVal + increment){
			
				T vec = tVal - cVal;
				vec /= abs(vec);
				vec *= increment * direction;
				cVal += vec;
				
			}else{
				
				increment = 0;
				cVal = tVal;
				isAuto =false;
			}
		}
	
	};
	
	
	bool getFlagChanged(){return flagChanged;};
	void setFlagChanged(bool b){flagChanged = b;};
	
	bool getIsAuto(){return isAuto;};
	
	private:
	
	T cVal;
	T tVal;
	float increment;
	bool isAuto;
	bool flagChanged;


};

template <>

class modifiable <ofVec2f> {
	
public:
	
	modifiable(){
	
		isAuto = false;
		increment = 0;
	};
	

	
	void set(ofVec2f t){
		cVal.set(t);
		tVal.set(t);
		increment = 0;
	};
	
	void setTarget(ofVec2f t, float i, bool b){
		tVal = t;
		increment = i;
		isAuto = b;
	};
	
	ofVec2f getCVal(){
		return cVal;
	}

	void end(){tVal = cVal; increment = 0;}
	
	void shiftValue(int direction){
		
		if(abs(increment) > 0){
			
			if(cVal.distance(tVal) >= increment){
				
				ofVec2f vec(tVal-cVal);
				vec.normalize();
				vec *= increment * direction;
				cVal += vec;
				
			}else{
				
				increment = 0;
				cVal = tVal;
				isAuto =false;
			}
			
		}
		
	};
	
	bool getIsAuto(){return isAuto;};
	
	private:
	
	ofVec2f cVal;
	ofVec2f tVal;
	float increment;
	bool isAuto;
	
};

