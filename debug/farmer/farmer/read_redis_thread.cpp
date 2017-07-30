#include "read_redis_thread.h"

#include <assert.h>
#include <QDebug>
#include <QReadWriteLock>

extern QReadWriteLock lock_realtime_data_;

ReadRedisThread::ReadRedisThread(QObject *parent)
	: QThread(parent)
{

}

ReadRedisThread::ReadRedisThread(const char* _ip, const unsigned short _port,
	std::map<std::string, std::string>* ptr, QObject* parent) : QThread(parent),
	port_(_port), ptr_realtime_data_(ptr)
{
	assert(ptr != nullptr);
	memcpy(ip_, ptr, sizeof(ip_));

	start();
}

ReadRedisThread::~ReadRedisThread()
{
	wait();
}

void ReadRedisThread::run()
{
	double limit_max = 40.0;
	double limit_min = -10.0;

	static double real_data_ = 1.0;

	std::string key = "hello";

	while (1){
		sleep(3);

		std::auto_ptr<QMutex> lock_( new QMutex);
		if ( stop_)
			break;
				
		if ( real_data_ <= limit_min )
			real_data_ = limit_min;
		if (real_data_ >= limit_max)
			real_data_ = limit_max;				

		QString strval = QString::number(real_data_, 10, 6);		
		std::string value = strval.toStdString();		

		lock_realtime_data_.lockForWrite();
		if (ptr_realtime_data_)
		{
			auto iter = ptr_realtime_data_->find(key);
			if ( iter != ptr_realtime_data_->end())
			{
				// finded it, change
				iter->second = value;
			} 
			else
			{
				// can't find, insert
				ptr_realtime_data_->insert(make_pair(key, value));
			}
			qDebug() << "write key:" << key.c_str() << "val:" << value.c_str();				
		}
		lock_realtime_data_.unlock();		

		/*
		lock_realtime_data_.lockForRead();
		for (auto iter = ptr_realtime_data_->begin(); iter != ptr_realtime_data_->end(); ++iter)
		{
			//QString qstr = QString::fromStdString(iter->second);
			//double val = qstr.toDouble();
			qDebug() << "read key:" << iter->first.c_str() << ", val:" << iter->second.c_str();
		}
		lock_realtime_data_.unlock();
		*/

		++real_data_;
		
	}
}

void ReadRedisThread::stop(bool flag)
{
	std::auto_ptr<QMutex> lock_(new QMutex);
	stop_ = true;
}