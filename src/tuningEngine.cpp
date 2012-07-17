/*
 *  tuningEngine.cpp
 *  testBed1
 *
 *  Created by Simon Katan on 17/07/2012.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "tuningEngine.h"

string const tuningEngine::scaleNames[] = {

	"aeolian",	
	"ahirbhairav", 	
	"ajam", 
	"atharKurd", 	
	"augmented", 	
	"augmented2", 	
	"bartok", 	
	"bastanikar", 	
	"bayati", 	
	"bhairav", 	
	
	"chinese", 
	"chromatic", 	
	"chromatic24", 	
	"diminished", 	
	"diminished2",	
	"dorian", 	
	"egyptian",	
	"enigmatic", 
	"farahfaza", 
	"gong",		
	
	"harmonicMajor",	
	"harmonicMinor", 
	"hexAeolian", 	
	"hexDorian",
	"hexMajor6", 
	"hexMajor7",	
	"hexPhrygian", 	
	"hexSus", 	
	"hijaz",	
	"hijazDesc", 
	
	"hindu", 	
	"hirajoshi", 	
	"hungarianMinor", 	
	"husseini", 	
	"huzam", 	
	"indian", 	
	"ionian",	
	"iraq", 	
	"iwato", 	
	"jiao",	
	
	"jiharkah", 	
	"karjighar", 	
	"kijazKarKurd", 	
	"kumoi", 	
	"kurd",	
	"leadingWhole", 
	"locrian", 
	"locrianMajor", 	
	"lydian", 
	"lydianMinor", 
	"mahur", 	
	
	"major", 	
	"majorPentatonic", 
	"marva", 	
	"melodicMajor", 	
	"melodicMinor",	
	"melodicMinorDesc",	
	"minor", 
	"minorPentatonic", 
	"mixolydian", 	
	"murassah", 	
	
	"mustar", 	
	"nahawand", 	
	"nahawandDesc",	
	"nairuz", 	
	"nawaAthar", 	
	"neapolitanMajor", 	
	"neapolitanMinor", 	
	"nikriz", 	
	"partch_o1", 	
	"partch_o2", 	
	
	"partch_o3", 	
	"partch_o4", 
	"partch_o5", 
	"partch_o6",	
	"partch_u1", 	
	"partch_u2", 	
	"partch_u3", 	
	"partch_u4",
	"partch_u5",	
	"partch_u6",
	"pelog", 
	
	"phrygian", 	
	"prometheus", 	
	"purvi", 	
	"rast", 	
	"rastDesc", 	
	"ritusen", 	
	"romanianMinor", 	
	"saba", 
	"scriabin", 	
	"shang", 	
	"shawqAfza", 	
	
	"sikah", 	
	"sikahDesc", 	
	"spanish", 
	"superLocrian", 
	"suznak",	
	"todi",	
	"ushaqMashri",	
	"whole", 	
	"yakah", 	
	"yakahDesc", 	
	"yu",	
	
	"zamzam",	
	"zanjaran",	
	"zhi"

};

int tuningEngine::cScale = 0;

ofxOscSender * tuningEngine::mSender;
ofxOscReceiver * tuningEngine::mReceiver;
vector<float> tuningEngine::mMidiNotes;


void tuningEngine::setSender(ofxOscSender * s){

	mSender = s;
}

void tuningEngine::setReciever(ofxOscReceiver * r){


	mReceiver = r;
}

string tuningEngine::getCScaleName(){
	
	return scaleNames[cScale];

}

void tuningEngine::changeCScale(int i){

	cScale = min(NUM_SCALES -1, max(cScale + i, 0));
	
}

void tuningEngine::requestScale(){

	ofxOscMessage m;
	m.setAddress("/reqScl");
	m.addStringArg(scaleNames[cScale]);
	
	mSender->sendMessage(m);
	

}

void tuningEngine::handleMessages(){

	while (mReceiver->hasWaitingMessages()) {
	 
		 ofxOscMessage m;
		 mReceiver->getNextMessage(&m);
		 
		 if ( m.getAddress() == "/newScale" ){
			 
			 mMidiNotes.clear();
			 
			 int numDegrees = m.getArgAsInt32(0); //
			 
			 /*for(int i = 0; i < numDegrees; i++){
				 mMidiNotes.push_back(m.getArgAsFloat(i));
			 }*/
			 
			 cout << "newScale\n";
		 }
	 
	 
	}

}