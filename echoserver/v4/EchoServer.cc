#include "Task.h"
#include "EchoServer.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>
#include <functional>

using std::placeholders::_1;
using std::cout;
using std::endl;

wd::Threadpool* g_threadpool = NULL;

EchoServer::EchoServer(const string& addr, unsigned short port) 
:_threadpool(4, 10)
,_tcpserver(addr, port)
{
g_threadpool = &_threadpool;

_tcpserver.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
_tcpserver.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1));
_tcpserver.setCloseCallback(std::bind(&EchoServer::onClose, this, _1));

_threadpool.start();
_tcpserver.start();
}

void EchoServer::onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void EchoServer::onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());
	if(s != "\n") {

	Task task(s, conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
	}
}

void EchoServer::onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}








#if 0
//使用TcpServer和Threadpool的模板
class EchoServer
{
public:
	EchoServer(char*, int);
	void onMessage(const wd::TcpConnectionPtr & conn);
	void onConnection(const wd::TcpConnectionPtr & conn);
	void onClose(const wd::TcpConnectionPtr & conn);
private:
	wd::Threadpool _threadpool;
	wd::TcpServer _tcpserver;
};
#endif

#if 0 

wd::Threadpool * g_threadpool = NULL;



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
