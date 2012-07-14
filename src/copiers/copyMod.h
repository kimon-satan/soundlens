/*
 *  copyMod.h
 *  testBed1
 *
 *  Created by Simon Katan on 14/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "baseMod.h"

class copyMod : public baseMod{


	public:
	
	copyMod(bool g_i, bool p_i, vector<int> params);
	vector<ofPtr<chime> > makeMod(vector<ofPtr<chime> > chimes);
	void drawControl( float dragDist, float dragAngle);
	
	private:
	
	vector<bool> mMuteParams;
	bool isGroupInd;
	bool isParamInd;
	
};