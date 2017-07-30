#ifndef READ_REDIS_THREAD_H
#define READ_REDIS_THREAD_H

#include <QThread>
#include <QMutex>

class ReadRedisThread : public QThread
{
	Q_OBJECT

public:
	ReadRedisThread(QObject *parent);
	ReadRedisThread(const char* _ip, const unsigned short _port, 
		std::map<std::string, std::string>*,
		QObject* parent);
	
	~ReadRedisThread();

	void run();
	void stop(bool);
	
	
	bool stop_ = false;

	

private:

	char ip_[33];
	unsigned short port_ = 6379;
	
	//std::uniqu
	std::map<std::string, std::string>* ptr_realtime_data_;

	//QMutex* lock_;
	//std::aut

};

#endif // READ_REDIS_THREAD_H
