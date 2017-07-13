#include "ucDmx.h"
#include "ofMain.h"

#include "pro_util.h"
#define CHANNEL_MUN_MIN 24
#define CHANNEL_MUN_MAX 512

ucDmx::ucDmx()
:connected(false)
,needsUpdate(false)
{
	uint8_t Num_Devices =0;
	Num_Devices = FTDI_ListDevices(); 
	printf("\n Looking for dmx Devices: %d Found \n", Num_Devices);
}

ucDmx::~ucDmx() {
	disconnect();
	connected = false;
}

bool ucDmx::connect(int device, unsigned int channels) {
	connected = FTDI_OpenDevice(device);
	setChannels(channels);

	return connected;
}

// bool ofxDmx::connect(string device, unsigned int channels) {
// 	serial.enumerateDevices();
// 	connected = serial.setup(device.c_str(), 57600);
// 	setChannels(channels);
// 	return connected;
// }

bool ucDmx::isConnected() {
	return connected;
}

void ucDmx::disconnect() {
	if (device_handle != NULL)
	{
		printf("closing DMX device...\n");
		FT_Close(device_handle);
	}
    connected = false;
}

void ucDmx::setChannels(unsigned int channels) {
	levels.resize(ofClamp(channels+1, CHANNEL_MUN_MIN, CHANNEL_MUN_MAX));
	levels[0] = 0;
}

void ucDmx::update(bool force) {
	if(needsUpdate || force) {
		needsUpdate = false;
		BOOL res = 0;
		unsigned int dataSize = levels.size();
		res = FTDI_SendData(SET_DMX_TX_MODE, (unsigned char*)&levels[0], dataSize);
		// check response from Send function
		if (res < 0)
		{
			printf("FAILED: Sending DMX to PRO \n");
			disconnect();
		}
		else
		{
			printf("SUCCESS: Sending DMX to PRO \n");
		}
	}
}

bool ucDmx::badChannel(unsigned int channel) {
	if(channel >= levels.size()) {
		ofLogError() << "Channel " + ofToString(channel) + " is out of bounds. Only " + ofToString(levels.size()) + " channels are available.";
		return true;
	}
	if(channel == 0) {
		ofLogError() << "Channel 0 does not exist. DMX channels start at 1.";
		return true;
	}
	return false;
}

void ucDmx::setLevel(unsigned int channel, unsigned char level) {
	if(badChannel(channel)) {
		return;
	}
	if(level != levels[channel]) {
		levels[channel] = level;
		needsUpdate = true;
	}
}

void ucDmx::clear() {
	for (int i = 0; i < levels.size(); i++) {
		levels[i] = 0;
	}
}

unsigned char ucDmx::getLevel(unsigned int channel) {
	if(badChannel(channel)) {
		return 0;
	}
	return levels[channel];
}

void ucDmx::flush()
{
	FTDI_PurgeBuffer();
}
