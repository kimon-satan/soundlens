/*
 *  spreadMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 07/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "baseMod.h"

struct chimeSorter{
	
	int param;
	chimeSorter(int i):param(i){}
	bool operator()(ofPtr<chime> a, ofPtr<chime> b);


};


class spreadMod : public baseMod{
	
public:
	
	spreadMod(int i = -1);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes, bool isAuto);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes){};
	void drawControl(float dragDist, float dragAngle);
	
private:
	
	int paramType;
	
	
};