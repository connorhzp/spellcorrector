 ///
 /// @file    rss.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-03-05 23:43:04
 ///

#include "tinyxml2.h"
#include <boost/regex.hpp>
#include <string>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;


void test(void) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("coolshell.xml");

	cout << "doc.ErrorID():" <<  doc.ErrorID() << endl;

	tinyxml2::XMLElement* pItem = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");

	std::string content = pItem->FirstChildElement("content:encoded")->GetText();
	boost::regex expr("<.+?>");

	std::ofstream ofs("pagelib.dat");
	do {
	ofs << "title:" << pItem->FirstChildElement("title")->GetText() << endl;
	ofs << "link:" << pItem->FirstChildElement("link")->GetText() << endl;
	ofs << "content:" << boost::regex_replace(content, expr, std::string("")) << endl;
	} while (NULL != (pItem = pItem->NextSiblingElement("item")));
}

int main(){

	test();

	return 0;
}
