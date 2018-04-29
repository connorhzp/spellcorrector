#ifndef __WD_ECHOSERVER_H
#define __WD_ECHOSERVER_H

#include "TcpServer.h"
#include "Threadpool.h"
#include "class_WordStatistic.h"
//#include "editDistance.h"
#include <functional>
#include <queue>

//使用TcpServer和Threadpool的模板
class EchoServer
{
public:
	EchoServer(const string& addr, unsigned short port);
	void onMessage(const wd::TcpConnectionPtr & conn);
	void onConnection(const wd::TcpConnectionPtr & conn);
	void onClose(const wd::TcpConnectionPtr & conn);
private:
	wd::Threadpool _threadpool;
	wd::TcpServer _tcpserver;
};

/*
class MyResult
{
public:
	bool operator<(const MyResult& rhs) const {
		if(_distance < rhs._distance)
			return true;
		if(_frequency < rhs._frequency && _distance == rhs._distance)
			return true;
		return false;
	}
	bool operator>(const MyResult& rhs) const {
		if(_distance > rhs._distance)
			return true;
		if(_frequency > rhs._frequency && _distance == rhs._distance)
			return true;
		return false;
	}

	MyResult(const std::string query, const Node& candidate) 
	:_candidateWord(candidate.word)
	,_frequency(candidate.amount)
	,_distance(editDistance(query, candidate.word))
	{

	}

	std::string print() const{
		return _candidateWord;
	}

private:
	std::string _candidateWord;
	int _frequency;
	int _distance;
};

class Task
{
public:
	Task(const string & query, const wd::TcpConnectionPtr & conn)
	: _query(query)
	, _conn(conn)
	{}
	
	void process();
	std::string fromquery();
private:
	string _query;
	wd::TcpConnectionPtr _conn;
	std::priority_queue<MyResult, std::vector<MyResult>, std::greater<MyResult> > _priorityQue;
//	std::priority_queue<MyResult> _priorityQue;
};
*/

#if 0 
class Task
{
public:
	Task(const string & query, const wd::TcpConnectionPtr & conn)
	: _queury(query)
	, _conn(conn)
	{}
	
	void process()
	{
		cout << "> task is processing" << endl;
		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		_conn->sendInLoop(_queury);
	}
private:
	string _queury;
	wd::TcpConnectionPtr _conn;
};

wd::Threadpool * g_threadpool = NULL;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());

	Task task(s, conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}


int main(int argc, char const *argv[])
{
	wd::Threadpool threadpool(4, 10);
	g_threadpool = &threadpool;
	threadpool.start();

	wd::TcpServer tcpserver("192.168.245.128", 9999);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

    return 0;
}
#endif
#endif
