/*
 *  speedSearch.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 06/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "speedSearch.h"

speedSearch::speedSearch(){

	name = "speed";
}

vector<ofPtr<chime> > speedSearch::getChimes(searchData& sd, ofPtr<chime> sample, vector<ofPtr<chime> > searchGroup){
	
	vector<ofPtr<chime> > tmp;
	
	for(vector<ofPtr<chime> >::iterator it = searchGroup.begin(); it != searchGroup.end(); it++){
		
		if((*it)->getSpeed()  == sample->getSpeed()){
			tmp.push_back(*it);
			(*it)->setIsTmpSelected(true);
		}else{
			(*it)->setIsTmpSelected(false);
		}		
	}
	
	return tmp;

}


void speedSearch::drawPreview(float dragDist, float dragAngle){

	//nothing to draw

}