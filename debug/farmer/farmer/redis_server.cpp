#include "redis_server.h"

#include <assert.h>

#include <QTime>
#include <QTimer>

RedisServer::RedisServer()
{
    // init variable
    initVar();

    // init file
    initConfig();

    initConnect();

    subscribeTags();
}

RedisServer::~RedisServer(){

    // close redis connection
    disConnectRedis();

    stopTimer();

    // cannel all subscribe tags
    unSubscribeTags();
}

void RedisServer::run()
{
    char* phost = "111.231.0.65";
    unsigned short port = 6379;

    std::auto_ptr<QtRedis> predis(new QtRedis(phost, port));
    if(!predis->openConnection()){
        qDebug() << "connect redis error! ip:"<< phost <<", port:"<<port;
        //return;
    }
    else{
        redis_connect_mutext_.lock();
        redis_connected_ = true;
        redis_connect_mutext_.unlock();
    }

    QtRedis::Reply reply;

    static int time_out = 1;

    forever{
        // 1 second
        sleep(5);

        QMutexLocker locker(&mutex_);
        if(stopped_)
        {
           stopped_ = false;
           break;
        }

        // check redis
        if(!predis->isConnected())
        {
            sleep(5);

            qDebug("threading arrive, but redis connect error! trying connect ...");

            if(!predis->openConnection())
            {
                redis_connect_mutext_.lock();
                redis_connected_ = false;
                redis_connect_mutext_.unlock();

                qDebug() << "threading arrive, connect redis error! waiting ...";

                // can't ping redis-server
                //throw QString("connect redis error!");

                if(time_out++>5){
                    qDebug() << "threading arrive, connect redis error! timeout > 5, new connect!";
                    //std::auto_ptr<QtRedis> predis(new QtRedis(phost, port));
                    time_out = 0;
                }
            }
            else{
                redis_connect_mutext_.lock();
                redis_connected_ = true;
                redis_connect_mutext_.unlock();
            }

            continue;
        }
        else{

            reply = predis->command("GET 9999");
            //qDebug() << "GET:" << "("<< reply.type << ")" << reply.value.toString();

            qDebug("threading, redis-server is runing ...");
        }

    }// end forever

}

void RedisServer::stop()
{
    QMutexLocker locker(&mutex_);
    stopped_ = true;
}

void RedisServer::setMessage(const QString &message)
{
    str_msg_ = message;
}

// init redis, connect redis
void RedisServer::initVar()
{
    // ------- redis ------------
    char* phost = "111.231.0.65";
    unsigned short port = 6379;

    predis_ = new QtRedis(phost, port);
    if(predis_ == nullptr) {
        throw QString("system error, can not get new(redis) memorry!");
    }

    // begin to connect redis-server!
    if(!predis_->openConnection()){
        qDebug() << "connect redis error! ip:"<< phost <<", port:"<<port;

        // not return, so the gui will be show
        //return;
    }else{
        qDebug() << "connect redis success! ret("<< predis_->isConnected() <<")";
    }


    // ------ timer ------
    ptimer_ = new QTimer(this);
    if(ptimer_ == nullptr) {
        throw QString("system error, can not get new(timer) memorry!");
    }
}


void RedisServer::initConfig()
{

}

void RedisServer::initConnect()
{
    // redis reply
    connect(predis_, SIGNAL(returnData(QtRedis::Reply)),
        this, SLOT(slotMessage(QtRedis::Reply)));

    connect(ptimer_,SIGNAL(timeout()), this, SLOT(slotCheckRedisTimer()) );
    ptimer_->start(5000);
}

// response result of subscribe Channel
void RedisServer::slotMessage(QtRedis::Reply reply)
{
    QTime time;
    qDebug() << time.currentTime();
    qDebug() << "Channel:" << reply.channel << "Pattern:" << reply.pattern;
    qDebug() << reply.value.toString();
}

void RedisServer::slotTimer()
{
    // not connect
    if(!predis_->isConnected()) {
        sleep(5);

        qDebug("timer arrive, but redis connect error! trying connect ...");

        if(!predis_->openConnection()) {
            qDebug() << "timer arrive, connect redis error! waiting ...";

            // can't ping redis-server
            //throw QString("timer arrive, connect redis error!");
        }
        else{
            qDebug() << "timer arrive, try connect redis success! subscribe again!";

            subscribeTags();
        }
    }else{
        qDebug("timer arrive, redis-server is running ...");
    }
}

void RedisServer::slotCheckRedisTimer()
{
    // not connect
    redis_connect_mutext_.lock();
    if(!redis_connected_ || !predis_->isConnected())
    {
        qDebug("timer arrive, but redis connect error! waiting for thread connect result ...");

        if(redis_connected_)
        {
            if(!predis_->openConnection())
            {
                qDebug() << "timer arrive, connect redis error! waiting ...";

                // can't ping redis-server
                //throw QString("timer arrive, connect redis error!");
            }
            else
            {
                qDebug() << "timer arrive, try connect redis success! subscribe again!";

                subscribeTags();
            }

            subscribeTags();
        }
    }else{
        subscribeTags();
        qDebug("timer arrive, redis-server is running ...");
    }
    redis_connect_mutext_.unlock();
}

void RedisServer::disConnectRedis()
{
    assert(predis_);
    if( predis_!=nullptr)
    {
        qDebug("closing  redis connection!");

        emit predis_->disconnected();
        delete predis_;
        predis_ = nullptr;
    }
}

void RedisServer::stopTimer()
{
    assert(ptimer_);
    if (ptimer_->isActive() )
    {
        ptimer_->stop();
    }

    delete ptimer_;
    ptimer_ = nullptr;
}

void RedisServer::subscribeTags()
{
    predis_->subscribe("lczn_100_100001_zt");
}

void RedisServer::unSubscribeTags()
{
    predis_->unsubscribe("lczn_100_100001_zt");
}
