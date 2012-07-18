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
// TWELVE TONES PER OCTAVE
// 5 note scales
"minorPentatonic", 
"majorPentatonic", 
// another mode of major pentatonic
"ritusen",  
// another mode of major pentatonic
"egyptian",  

"kumoi",   
"hirajoshi",   
"iwato",   
"indian",  
"pelog",  

"prometheus", 
"scriabin",  

// han chinese pentatonic scales
"gong",  
"shang",  
"jiao",  
"zhi", 
"yu",  

// 6 note scales
"whole",  
"augmented",  
"augmented2", 

// Partch's Otonalities and Utonalities
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

// hexatonic modes with no tritone
"hexMajor7",  
"hexDorian",  
"hexPhrygian",  
"hexSus",  
"hexMajor6",  
"hexAeolian", 

// 7 note scales
"major",
"ionian",
"dorian",
"phrygian",
"lydian",
"mixolydian",
"aeolian",
"minor",
"locrian",

"harmonicMinor",
"harmonicMajor",

"melodicMinor",
"melodicMinorDesc",
							   
"melodicMajor", 

"bartok" ,
"hindu" ,

// raga modes
"todi" ,
"purvi" ,
"marva" ,
"bhairav" ,
"ahirbhairav" ,

"superLocrian" ,
"romanianMinor" ,
"hungarianMinor" ,
"neapolitanMinor" ,
"enigmatic" ,
"spanish" ,

// modes of whole tones with added note
"leadingWhole" ,
"lydianMinor" ,
"neapolitanMajor" ,
"locrianMajor" ,

// 8 note scales
"diminished" ,
"diminished2" ,   

// 12 note scales
"chromatic" , 

// TWENTY-FOUR TONES PER OCTAVE

"chromatic24" ,   

// maqam ajam
"ajam" , 
"jiharkah" , 
"shawqAfza" , 

// maqam sikah
"sikah" , 
"sikahDesc" , 
"huzam" , 
"iraq" , 
"bastanikar" , 
"mustar" , 

// maqam bayati
"bayati" , 
"karjighar" , 
"husseini" , 

// maqam nahawand
"nahawand" , 
"nahawandDesc" ,
"farahfaza" ,
"murassah" ,
"ushaqMashri" ,

// maqam rast
"rast" ,
"rastDesc" , 
"suznak" ,
"nairuz" ,
"yakah" , 
"yakahDesc", 
"mahur" ,

// maqam hijaz
"hijaz" , 
"hijazDesc" ,
"zanjaran" , 

// maqam hijazKar
"zanjaran" , 

// maqam saba
"saba" , 
"zamzam" , 

// maqam kurd
"kurd" , 
"kijazKarKurd" ,

// maqam nawa Athar
"nawaAthar" , 
"nikriz" ,
"atharKurd" ,


// Ascending/descending scales
"melodicMinor" , 
"sikah" ,
"nahawand" ,


};
	


int tuningEngine::cScale = 0;

ofxOscSender * tuningEngine::mSender;
ofxOscReceiver * tuningEngine::mReceiver;
vector<float> tuningEngine::mMidiNotes;
vector<float> tuningEngine::mOffsetMidiNotes;
float tuningEngine::mOffset = 0;

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
		
		float timeStamp = 0;
		 ofxOscMessage m;
		 mReceiver->getNextMessage(&m);
		 
		 if ( m.getAddress() == "/newScale" ){
			 
			 mMidiNotes.clear();
			 
			 int numDegrees = m.getArgAsInt32(0);			 
			 string toneString = m.getArgAsString(1);
			 
			 stringstream ss(toneString);
			 vector<string> elems;
			 string item;
			 
			 while(getline(ss, item, ',')){
				 elems.push_back(item);
			 }
			 
			 for(int i = 0; i < elems.size(); i++){
				 
				 float f = atof(elems[i].c_str());
				 mMidiNotes.push_back(f + 12);
				 
			 }
			 
			setOffset(0);
		 }
		
		
	 
	}

}



void tuningEngine::setOffset(float f){
	
	mOffsetMidiNotes.clear();
	mOffset = f;
	for(int i = 0; i < mMidiNotes.size(); i++){
		
		mOffsetMidiNotes.push_back(fmod(mMidiNotes[i] + mOffset,12));
	
	}
	
}

bool tuningEngine::checkForMatch(float f, float toll){
	
	for(int i =0; i < mOffsetMidiNotes.size(); i++){
	
		float rmdr = fmod(f, 12);
		float diff = abs(mOffsetMidiNotes[i] - rmdr);
		if(diff <= toll)return true;
		
	}

	return false;
}



float tuningEngine::getNearestNeighbour(float f){
	
	float minDiff = 12;
	float newF;
	
	for(int i =0; i < mOffsetMidiNotes.size(); i++){
		
		float rmdr = fmod(f, 12);
		float diff = mOffsetMidiNotes[i] - rmdr;
		if(abs(diff) < abs(minDiff))minDiff = diff;
	
	}
	
	newF = f - minDiff;
	
	return newF;
	
}