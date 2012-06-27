/*
 *  chimeRenderer.h
 *  testBed1
 *
 *  Created by Simon Katan on 25/06/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "chime.h"

class chimeRenderer{
	
	public:
	
	static void loadSprites();
	static void draw(ofPtr<chime> c);
	static void drawAnchor(ofPtr<chime> c);
	static void drawPivots(ofPtr<chime> c);
	static void drawStem(ofPtr<chime> c);
	static void drawHammer(ofPtr<chime> c);
	static void drawSensors(ofPtr<chime> c);
	
	private:
	
	static vector<ofPtr<ofImage> >  mStemSprite;
	static vector<ofPtr<ofImage> >  mEmptySensorSprite;
	static vector<ofPtr<ofImage> >	mFilledSensorSprite;
	static vector<ofPtr<ofImage> >	mEmptyHammerSprite;
	static vector<ofPtr<ofImage> >	mFilledHammerSprite;
	static vector<ofPtr<ofImage> >	mPivotSprite;
	
	

	
};
