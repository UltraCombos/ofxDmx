#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetLogLevel(OF_LOG_VERBOSE);
	
	m_background_color.setName("Background Color");
	m_background_color.set(ofColor(114, 144, 154));

	m_param_group.setName("ofxDmx");

	{
		ofxImGuiEnum val;
		val.content = m_dmx.listDevices();
		val.select = 0;
		m_param_device.set("devices", val);
	}

	m_param_group.add(m_param_device);
	m_param_group.add(m_param_device_name.set("device name", ""));
	m_param_group.add(m_param_start_channel_no.set("start channel no", 1, 1, 512));

	for (size_t i = 0; i < MaxNumChannel; ++i)
	{
		m_param_group.add(m_param_channels[i].set(std::string("channel[") + ofToString(i) + std::string("]"), 0, 0, 255));
	}

	ofxImGuiParameter::Initialize();

	m_imgui_parameter.setup("ofxDmxExample", ofRectangle(10, 10, 480, 640));
	m_imgui_parameter.bind(m_background_color);
	m_imgui_parameter.bind(m_param_group);
	m_imgui_parameter.load();

	ofAddListener(ofxImGuiParameter::GetOnDrawEvent(), this, &ofApp::mf_on_ImGui_draw);
	m_param_device.addListener(this, &ofApp::mf_on_changed_device);
	m_param_device_name.addListener(this, &ofApp::mf_on_chnaged_device_name);

	m_need_to_reconnect_device = true;
}

void ofApp::exit()
{
	ofxImGuiParameter::Finalize();
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (m_need_to_reconnect_device)
	{
		mf_reconnect_device();
	}

	if (m_dmx.isConnected()) 
	{
		m_background_color = ofColor::green;
		m_dmx.setStartChannel(m_param_start_channel_no);
		for (unsigned int i = 0; i < MaxNumChannel; ++i) 
		{
			m_dmx.setLevel(i + m_param_start_channel_no, m_param_channels[i]);
		}

		m_dmx.update();
	}
	else 
	{
		m_background_color = ofColor::red;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{   
	ofSetBackgroundColor(m_background_color.get());
	ofxImGuiParameter::Draw();
}

void ofApp::mf_reconnect_device()
{
	m_dmx.disconnect();

	if (m_dmx.connect(m_param_device_name, MaxNumChannel))
	{
		m_dmx.update(true); // black on startup
	}

	m_need_to_reconnect_device = false;
}

void ofApp::mf_on_ImGui_draw()
{
	//You can test any ImGui Code here.
}

void ofApp::mf_on_chnaged_device_name(std::string& name)
{
	m_need_to_reconnect_device = true;
}

void ofApp::mf_on_changed_device(ofxImGuiEnum& val)
{
	m_param_device_name = val.content[val.select];
}

void ofApp::mf_on_changed_channel_value(int& val)
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


void ofApp::mouseScrolled(float x, float y){

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}