/*
 *  mappingEngine.h
 *  testBed1
 *
 *  Created by Simon Katan on 08/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "ofMain.h"

enum e_mapType{

	MAP_1_TO_R,
	MAP_R_TO_R,
	MAP_R_TO_EXP,

	//potentially other kinds of mappings later (eg. exp warped)
	
};

struct mapDef{

	int mapType;
	int inMap, outMap;
	float inRange[2];
	float outRange[2];
	float exp;
	
	//position mapping would need to be done in a dedicated mod
	//int posInType
	//int posOutType
	
	

};


class mappingEngine{
	
	public:
	
	static void makeMapping(vector<float> inVals, vector<float> & outVals, mapDef m);


};