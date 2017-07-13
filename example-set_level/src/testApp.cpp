#include "testApp.h"

#define CHANNELS_NUM_TO_OPEN 256
//--------------------------------------------------------------
void testApp::setup(){
	dmx.connect(0,CHANNELS_NUM_TO_OPEN);

	for (int i = 1; i <= CHANNELS_NUM_TO_OPEN; i++)
	{
		dmx.setLevel(i, i-1);
	}
}

//--------------------------------------------------------------
void testApp::update(){
	for (int i = 1; i <= CHANNELS_NUM_TO_OPEN; i++)
	{
		unsigned char l = dmx.getLevel(i);
		dmx.setLevel(i, l+1);
	}
	dmx.update();
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}