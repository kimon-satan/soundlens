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
	SET_USER_A_INV,
	SET_USER_B_INV,
	SET_MAP_X,
	SET_MAP_Y
	
};



		

template <class T>

class dataElement{
	
public:
	
	dataElement(){
		
		setType = e_setType(0);
		incr = 0;
		isActive = true;
	}
	
	void set(T t_ab){
		
		abs_val = t_ab;
		setType = e_setType(0);
		
	};
	
	void set(T t_mi, T t_ma, int s){
		
		if(s == SET_FIXED){
			set(t_mi);
		}else{
			min_val = t_mi;
			max_val = t_ma;
			setType = e_setType(s);
		}
		
	};
	
	string setUserValues(float ua, float ub, ofVec2f pos = ofVec2f(0,0)){ 
		
		if(setType != SET_FIXED){
			
			switch(setType){
			
				case SET_USER_A:
					abs_val = ofMap(ua,0,1,min_val, max_val);
					break;
				case SET_USER_B:
					abs_val = ofMap(ub,0,1,min_val, max_val);
					break;
				case SET_USER_A_INV:
					abs_val = ofMap(ua,0,1,max_val, min_val);
					break;
				case SET_USER_B_INV:
					abs_val = ofMap(ub,0,1,max_val, min_val);
					break;
				case SET_MAP_X:
					abs_val = ofMap(pos.x,-10,10,max_val, min_val,true);
					break;
				case SET_MAP_Y:
					abs_val = ofMap(pos.y,4.5,-4.5,max_val, min_val,true);
					break;
			
			}

			
			
			if(incr > 0)abs_val -= fmod((float)abs_val, incr);
			
			if(displayNames.size() > 0){
				
				if(name != ""){
					return name + ": " + displayNames[abs_val] + ", ";
				}else{
					return displayNames[abs_val];
				}
				
			}else{
				
				if(name != ""){
					return name + " " + ofToString(abs_val,2) + ", ";
				}else{
					return ofToString(abs_val,2);
				}
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
	float incr;
	bool isActive;
	vector<string> displayNames;
	
};


template <>

class dataElement <ofVec2f> {

public:
	
	dataElement(){
		
		setType = e_setType(0);
		
	}
	
	void set(ofVec2f t_ab){
		
		abs_val = t_ab;
		setType = e_setType(0);
		
	};
	
	
	string setUserValues(float ua, float ub){ //not used for ofVec2f
		
		return ""; 
		
	};
	
	e_setType setType;
	ofVec2f abs_val;
	ofVec2f min_val;
	ofVec2f max_val;
	string name;


};



