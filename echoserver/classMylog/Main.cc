 ///
 /// @file    Main.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-02-26 23:34:43
 ///
 
#include "Mylog.h"


void test(){
	LogError("msg ERROR msg")
	LogWarn("msg WARN msg")
	LogInfo("msg INFO msg")
	LogDebug("msg DEBUG msg")
}
int main(){
	test();
}
