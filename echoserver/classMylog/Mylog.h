 ///
 /// @file    Mylog.h
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-02-26 20:38:02
 ///
#ifndef __HZP_MYLOG_H__
#define __HZP_MYLOG_H__

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

class Mylog{
public:
	static Mylog* getInstance();
	static void destroy();

	void error(const char* msg);
	void warn(const char* msg);
	void info(const char* msg);
	void debug(const char* msg);

private:
	Mylog();
	~Mylog();
	static Mylog* _pInstance;

	log4cpp::Category& _cate;
};


void logError(const char* msg);
void logWarn(const char* msg);
void logInfo(const char* msg);
void logDebug(const char* msg);


inline std::string int2str(int num){
	std::ostringstream oss;
	oss<< num;
	return oss.str();
}


#define prefix(msg) std::string("[").append(__FILE__).\
					append(":").append(int2str(__LINE__)).\
					append(":").append(__func__).\
					append("]").append(msg).c_str()

#define LogError(msg) logError(prefix(msg));
#define LogWarn(msg) logWarn(prefix(msg));
#define LogInfo(msg) logInfo(prefix(msg));
#define LogDebug(msg) logDebug(prefix(msg));


#endif
