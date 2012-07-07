/*
 *  dataElement.h
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

enum e_setType{
	
	SET_FIXED,
	SET_USER_A,
	SET_USER_B,
	
};

template <class T>

class dataElement{
	
public:
	
	dataElement(){
		
		setType = e_setType(0);
		
	}
	
	void set(T t_ab){
		
		abs_val = t_ab;
		setType = e_setType(0);
		
	};
	
	void set(T t_mi, T t_ma, int s){
		
		min_val = t_mi;
		max_val = t_ma;
		setType = e_setType(s);
		
	};
	
	string setUserValues(float ua, float ub){
		
		if(setType != SET_FIXED){
			abs_val = ofMap((setType == SET_USER_A)? ua:ub,0,1,min_val, max_val);
			if(name != ""){
				return name + " " + ofToString(abs_val,2) + ", ";
			}else{
				return ofToString(abs_val,2);
			}
			
		}else{
			
			return "";
		}
	};
	
	e_setType setType;
	T abs_val;
	T min_val;
	T max_val;
	string name;
	
};



