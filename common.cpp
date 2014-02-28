#include "common.h"

void infoPrint(const string &info) {
#ifdef iDEBUG_INFO
	cout << info << "\n\n";
#endif

#ifdef iDEBUG_INFO_LOG
	//ofstream ofs;
	//ofs.open("RayTracingLog.txt", ofstream::out || ofstream::app);
	//ofs << info << endl;
	//ofs.close();
	FILE * f = NULL;
	errno_t ern = fopen_s(&f, "RayTracingLog.txt", "a+");
	fprintf_s(f, "[%s]: %s", getCurrentTime().c_str(), (info + '\n').c_str());
	fclose(f);
#endif
}

string getCurrentTime() {
	time_t rawTime;
	tm * timeInfo = new tm;

	time ( &rawTime );
	errno_t ern = localtime_s(timeInfo, &rawTime);
	char buff[100];
	asctime_s(buff, timeInfo);
	string buff_s = string(buff);
	return buff_s.substr(0, buff_s.length() - 1);
}