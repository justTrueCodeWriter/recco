#include <iostream>

#include <json/json.h>
#include <fstream>

#include <boost/format.hpp>
#include <ctime>

tm *get_time() {
	time_t now = time(0);
	tm *localTime = localtime(&now);
	
	return localTime;
}

void get_devices();
void record();

using namespace std;

int main() {

	get_devices();

	record();
}

void get_devices() {

	system("pactl --format=json list sources | jq '.[] | {name: .name, desc: .description, monitor_src: .monitor_source}' > ~/.config/recco/devices.json");

}
void record() {

	tm *time = get_time();

	string defaultFilename = (boost::format("%d-%d-%d_%d-%d")%time->tm_mday%(1+time->tm_mon)%(1900+time->tm_year)%time->tm_hour%time->tm_min).str();

	string recCommand = (boost::format("parecord --channels=2 --file-format=flac --device alsa_input.pci-0000_00_1f.3.analog-stereo %s.flac")%defaultFilename).str();

	cout << defaultFilename << endl;
	system(recCommand.c_str());

}
