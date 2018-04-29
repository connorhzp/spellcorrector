 ///
 /// @file    word_count.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-02-28 14:18:40
 ///
 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
using std::cout;
using std::endl;

struct Node{
	Node()
	:amount(0){}
	std::string word;
	int amount;
};

class WordStatistic{
public:
	WordStatistic(const std::string& filename);
	void statistic();
	void ofsout();
private:
	std::string _filename;
	std::ifstream _ifs;
	std::ofstream _ofs;
	std::vector<Node> _vecNode;
};

WordStatistic::WordStatistic(const std::string& filename)
:_filename(filename)
,_ifs(filename)
,_ofs("word_statistic."+filename){}

void WordStatistic::statistic(){
	std::string word;
	bool newword= true;
	Node node;
//	cout<<node.amount<<endl;
	node.amount= 1;
	while(_ifs>> word){
		newword= true;
//		cout<< node.amount<<endl;
//		cout<< word<<endl;
		for(Node& node : _vecNode){//这里要用Node&,词频才能加得上去，一开始用的Node,测试了半天
			if(node.word == word){
				++node.amount;
//				cout<< node.amount<<endl;
				newword= false;
				break;
			}
		}
		if(newword){
			node.word= word;
			_vecNode.push_back(node);
//			_vecNode.end()->word= word;//一开始用的这个，迭代器指向最末元素的下一个，对其赋值引起了段错误,core dumped
//			++_vecNode.back().amount;
		}
	}
}
void WordStatistic::ofsout(){
	for(Node& node : _vecNode){
		_ofs<< std::setw(20)<<node.word<<":"<<node.amount<<endl;
	}
}
