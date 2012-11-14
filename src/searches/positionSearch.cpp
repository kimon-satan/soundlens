/*
 *  positionSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 07/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "positionSearch.h"

positionSearch::positionSearch(){

	name = "position";
	isSample = false;
}

vector<ofPtr<chime> > positionSearch::getChimes(searchData& sd,ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	ofRectangle searchRect(
		min(mDown.x, mDrag.x),
		min(mDown.y, mDrag.y),
		abs(mDown.x - mDrag.x),
		abs(mDown.y - mDrag.y)
						   
	);
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		if(searchRect.inside((*it)->getStemDims().cPos)){
			(*it)->setIsTmpSelected(true);
			tmp.push_back(*it);
		}else{
			(*it)->setIsTmpSelected(false);
		}
	}
	
	return tmp;

}

void positionSearch::drawPreview(float dragDist, float dragAngle){

	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(100);
	ofNoFill();
	ofRect(mDown.x,mDown.y, mDrag.x - mDown.x, mDrag.y - mDown.y);			  
	ofPopStyle();
}