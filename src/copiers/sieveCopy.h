/*
 *  sieveCopy.h
 *  testBed1
 *
 *  Created by Simon Katan on 18/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "baseCopy.h"
#include "tuningEngine.h"

class sieveCopy : public baseCopy{
	
	
public:
	
	sieveCopy(copierSpec cSpec);
	vector<ofPtr<chime> > getCopies(vector<ofPtr<chime> > chimes);
	
	
private:
	
	
	
};

