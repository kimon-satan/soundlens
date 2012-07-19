/*
 *  arrangeCopy.h
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseCopy.h"

class arrangeCopy : public baseCopy{
	
	
public:
	
	arrangeCopy(copierSpec cSpec);
	vector<ofPtr<chime> > getCopies(vector<ofPtr<chime> > chimes);
	string setUserData(ofVec2f mD, ofVec2f mDr, float ua, float ub);
	
private:
	
	
	
};


