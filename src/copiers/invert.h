/*
 *  invert.h
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "baseCopy.h"

class invert : public baseCopy{
	
	
public:
	
	invert(copierSpec cSpec);
	vector<ofPtr<chime> > getCopies(vector<ofPtr<chime> > chimes);

	
private:
	
	
	
};
