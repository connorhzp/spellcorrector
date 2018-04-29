
#include "Task.h"

#include "EchoServer.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "class_WordStatistic.h"
//#include "editDistance.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

WordStatistic* g_WordStatistic = NULL;


/*
std::string Task::fromquery()	{
		std::string fromquery;
		return fromquery;
}
*/
void Task::process()
{
	cout << "> task is processing" << endl;
//	_conn->sendInLoop(_query);



	std::vector<Node>& vecNode = g_WordStatistic->getVecNode();
//	cout << vecNode[0].word << endl;
//	_conn->sendInLoop(vecNode[1].word);



	for(auto ch : _query) {
		std::unordered_set<int>& setInt = g_WordStatistic->getIndex()[ch];
		
		for(auto intN : setInt) {
//			cout << intN << " " << vecNode[intN].word << endl;
			
			MyResult myResult(_query, vecNode[intN]);
//			cout << myResult.print() << endl;
//			_conn->sendInLoop(myResult.print());
			_priorityQue.push(myResult);
//			cout << (_priorityQue.top().print()+" ");
		}
	}



#if 1
	for (int i = 0; i != 10; ++i) {

		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		_conn->sendInLoop("\n");
		_conn->sendInLoop(_priorityQue.top().print());
		std::string topMyResultCondidate = _priorityQue.top().print();
		_priorityQue.pop();
		while(_priorityQue.top().print() == topMyResultCondidate)
			_priorityQue.pop();
//		_conn->sendInLoop("\n");
	}
		_conn->sendInLoop("\n");
		
#endif
}


int main(int argc, char const *argv[])
{
	WordStatistic theHolyBible("The_Holy_Bible.txt");
	theHolyBible.ofsOut();
//	std::vector<Node> vecNode = theHolyBible.getVecNode();
/*	cout << vecNode[0].word << endl;
	cout << vecNode[1].word << endl;
	cout << vecNode[2].word << endl;
	cout << vecNode[3].word << endl;
	cout << vecNode[4].word << endl;
	cout << vecNode[5].word << endl;
*/	

//	cout << theHolyBible.getVecNode()[0].word << endl;
	g_WordStatistic = &theHolyBible;

	EchoServer echoserver("192.168.245.128", 9999);
//	EchoServer echoserver(INADDR_ANY, 9999);
    return 0;
}
/*
#include "Task.h"

#include "EchoServer.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "class_WordStatistic.h"
//#include "editDistance.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
WordStatistic* g_WordStatistic = NULL;


std::string Task::fromquery()	{
		std::string fromquery;
		return fromquery;
}
void Task::process()
{
	cout << "> task is processing" << endl;
	_conn->sendInLoop(_query);



	std::vector<Node>& vecNode = g_WordStatistic->getVecNode();
	for(auto ch : _query) {
		std::unordered_set<int>& setInt = g_WordStatistic->getIndex()[ch];
		
		for(auto intN : setInt) {
			MyResult myResult(_query, vecNode[intN]);
			_priorityQue.push(myResult);
		}
	}


#if 0
	for (int i = 0; i != 10; ++i) {

		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		_conn->sendInLoop(_priorityQue.top().print());
		_priorityQue.pop();
		_conn->sendInLoop("\n");
		
	}
#endif
}


int main(int argc, char const *argv[])
{
	WordStatistic theHolyBible("the_Holy_Bible.txt");

	g_WordStatistic = &theHolyBible;



	EchoServer echoserver("192.168.245.128", 9999);
    return 0;
}
*/
