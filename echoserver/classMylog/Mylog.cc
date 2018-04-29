 ///
 /// @file    Mylog.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-02-26 21:37:57
 ///

#include "Mylog.h"

Mylog* Mylog::_pInstance= NULL;
Mylog* Mylog::getInstance(){
	if(NULL==_pInstance)
		_pInstance= new Mylog();
	return _pInstance;
}
void Mylog::destroy(){
	if(_pInstance)
		delete _pInstance;
}


Mylog::Mylog()
: _cate(log4cpp::Category::getRoot()){
	log4cpp::Appender* ostreamAppender= new log4cpp::OstreamAppender("ostreamAppender",&cout);
	log4cpp::Appender* fileAppender= new log4cpp::FileAppender("fileAppender","hzp.log");

	log4cpp::PatternLayout* ptnLyt= new log4cpp::PatternLayout();
	ptnLyt->setConversionPattern("%d [%p] %c %x: %m%n");
	ostreamAppender->setLayout(ptnLyt);
	log4cpp::PatternLayout* ptnLyt2= new log4cpp::PatternLayout();
	ptnLyt2->setConversionPattern("%d [%p] %c %x: %m%n");
	fileAppender->setLayout(ptnLyt2);

	_cate.addAppender(ostreamAppender);
	_cate.addAppender(fileAppender);
	_cate.setPriority(log4cpp::Priority::DEBUG);
}
Mylog::~Mylog(){
	log4cpp::Category::shutdown();
}


void Mylog::error(const char* msg){
	_cate.error(msg);
}
void Mylog::warn(const char* msg){
	_cate.warn(msg);
}
void Mylog::info(const char* msg){
	_cate.info(msg);
}
void Mylog::debug(const char* msg){
	_cate.debug(msg);
}
void logError(const char* msg){
	Mylog::getInstance()->error(msg);
}
void logWarn(const char* msg){
	Mylog::getInstance()->warn(msg);
}
void logInfo(const char* msg){
	Mylog::getInstance()->info(msg);
}
void logDebug(const char* msg){
	Mylog::getInstance()->debug(msg);
}

