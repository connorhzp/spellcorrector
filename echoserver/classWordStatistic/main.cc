 ///
 /// @file    main.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-02-28 21:44:30
 ///

#include "class_WordStatistic.h"
#include <iostream>
using std::cout;
using std::endl;


int main(){
	WordStatistic theHolyBible("The_Holy_Bible.txt");
	theHolyBible.statistic();
	theHolyBible.ofsout();
//	WordStatistic test("test.txt");
//	test.statistic();
//	test.ofsout();
}

