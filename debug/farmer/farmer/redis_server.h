#ifndef REDISSERVER_H
#define REDISSERVER_H

#include "common.h"
#include "qtredis/qtredis.h"

//class QtReids;
class QTimer;

#include <QThread>

class RedisServer : public QThread
{
    Q_OBJECT

public:
    RedisServer();
    ~RedisServer();

    void setMessage(const QString& message);

    void stop();

protected:
    void run();

private:
    void initVar();
    void initConfig();
    void initConnect();
    void initVarRedisForThreadSpace();
    void disConnectRedis();
    void stopTimer();

    void subscribeTags();
    void unSubscribeTags();

public slots:
    void slotMessage(QtRedis::Reply);
    void slotTimer();
    void slotCheckRedisTimer();

private:
    QString str_msg_;

    volatile bool stopped_ = false;

    QMutex mutex_;
    QMutex redis_connect_mutext_;

    std::map<std::string, SPOINTNODE> map_air_temperature_;

    QtRedis *predis_;
    //std::auto_ptr<QtRedis> predis_; // auto_ptr can not send singal to slot, so change to usual pointer

    QTimer *ptimer_;

    bool redis_connected_ = false;

};

#endif // REDISSERVER_H
