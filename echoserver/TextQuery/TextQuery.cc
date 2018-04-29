 ///
 /// @file    TextQuery.cc
 /// @author  hzp(haozhipeng2018@163.com)
 /// @date    2018-03-12 21:44:23
 ///

#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::vector;
using std::string;

class TextQuery {
public:
	void readFile(const string& filename);
	void query(const string& word);
	
	void linePreprocess(string& line);


private:
	vector<string> _lines;
	map<string, set<int>> _word2lineNos;
	map<string, int> _word2frequrncy;
};

void TextQuery::linePreprocess(string& line) {
	for(size_t idx = 0; idx != line.size(); ++idx) {
		(line[idx]>='A' && line[idx]<='Z') ? line[idx]+=32 : line[idx];
		if(!isalpha(line[idx]))
				line[idx] = ' ';
	}
}

void TextQuery::readFile(const string& filename) {
	std::ifstream ifs(filename);
	if(!ifs) {
		cout << "ifstream open file error!" << endl;
	}

	string line;
	_lines.push_back("line NO.0");
	int count = 1;
	while(getline(ifs, line)) {
		for(size_t idx = 0; idx != line.size(); ++idx) 
			linePreprocess(line);	
		_lines.push_back(line); 
		std::istringstream iss(line);
		string word;
		while(iss >> word) {
			++_word2frequrncy[word];
			_word2lineNos[word].insert(count);
		}
		++count;
	}
}

void TextQuery::query(const string& word) {
	set<int>& numbers = _word2lineNos[word];
	if(numbers.size() > 0) {
		cout << word << " occures " << _word2frequrncy[word] << " times.\n";
		for(auto it = numbers.begin(); it != numbers.end(); ++it) {
			cout << "	[line " << *it << "]" << _lines[*it] << "\n";
		}
	} else {
		cout << word << " not found!" << endl;
	}
}

int main() {
	TextQuery tq;
	tq.readFile("china_daily.txt");

	string word;
	while(std::cin >> word) {
		tq.query(word);
	}
	return 0;
}
