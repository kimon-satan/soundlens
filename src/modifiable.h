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

	void shiftValue(int direction){
	
		if(abs(increment) > 0){
			if(cVal <= tVal - increment || cVal >= tVal + increment){
			
				T vec = cVal - tVal;
				vec /= abs(vec);
				vec *= increment * direction;
				cVal += vec;
				
			}else{
				
				increment  = 0;
			}
		}
	
	};
	
	
	private:
	
	T cVal;
	T tVal;
	float increment;
	bool isAuto;
	


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

	
	void shiftValue(int direction){
		
		if(abs(increment) > 0){
			
			if(cVal.distance(tVal) >= increment){
				
				ofVec2f vec(tVal-cVal);
				vec.normalize();
				vec *= increment * direction;
				cVal += vec;
				
			}
			
		}
		
	};
	
	private:
	
	ofVec2f cVal;
	ofVec2f tVal;
	float increment;
	bool isAuto;
	
};

