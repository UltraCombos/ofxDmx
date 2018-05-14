#pragma once

#include "ofMain.h"
#include <ofxImGuiParameter.h>
#include <ofxDmx.h>

class ofApp : public ofBaseApp
{
public:
	enum
	{
		MaxNumChannel = 18,
	};

    void setup();
    void update();
    void draw();
	void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(float x, float y);
    
private:
	void mf_on_ImGui_draw();

	ofParameter< ofColor >	m_background_color;
	ofxImGuiParameter		m_imgui_parameter;
	ofParameterGroup		m_param_group;
	ofParameter< int >		m_param_channels[MaxNumChannel];

	ofxDmx m_dmx;

};
