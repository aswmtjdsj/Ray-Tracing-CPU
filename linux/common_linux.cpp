#include "../common.h"
// linux version

void infoPrint(const string &info) {
#ifdef DEBUG_INFO
	cout << info << "\n\n";
#endif

#ifdef DEBUG_INFO_LOG
    FILE * f = fopen("RayTracingLog.txt", "a+");
	fprintf(f, "[%s]: %s", getCurrentTime().c_str(), (info + '\n').c_str());
	fclose(f);
#endif
}

string getCurrentTime() {
	time_t rawTime;
	tm * timeInfo = new tm;

	time ( &rawTime );
	localtime_r(&rawTime, timeInfo);

	char buff[100];
	asctime_r(timeInfo, buff);
	string buff_str = string(buff);
	return buff_str.substr(0, buff_str.length() - 1);
}
