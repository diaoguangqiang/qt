#include <QFile>
#include <QDebug>

#include "cmodel.h"



CModel::CModel()
{
    this->clearData();
    //读取txt
    this->readTxt(0);
}


/**
 * @brief CModel::readTxt 读取文件
 * @return
 */
bool CModel::readTxt(const char*)
{
    QFile file("F:\\Qt\\smartgraphics\\smartgraphics\\a01_s01_e01_screen.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        return false;
    }

    int line_no = 0;
    QPointF point;
    int mode_no = 0;
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str( line);
        //根据字符串获取坐标
        point = getPointF(str);

        mode_no = line_no % 15;
        switch ( mode_no ) {
            case 0:
                qDebug()<< line_no << ": head :" << str << " : " << point.x() << ", " << point.y();
                this->getHead()->push_back(point);
                break;
            case 1:
                qDebug()<< line_no << ": neck :" << str;
                this->getNeck()->push_back(point);
                break;
            case 2:
                qDebug()<< line_no << ": right shoulder :" << str;
                this->getRightShoulder()->push_back(point);
                break;
            case 3:
                qDebug()<< line_no << ": right elbow :" << str;
                this->getRightElbow()->push_back(point);
                break;
            case 4:
                qDebug()<< line_no << ": right hand :" << str;
                this->getRightHand()->push_back(point);
                break;
            case 5:
                qDebug()<< line_no << ": left shoulder :" << str;
                this->getLeftShoulder()->push_back(point);
                break;
            case 6:
                qDebug()<< line_no << ": left elbow :" << str;
                this->getLeftElbow()->push_back(point);
                break;
            case 7:
                qDebug()<< line_no << ": left hand :" << str;
                this->getLeftHand()->push_back(point);
                break;
            case 8:
                qDebug()<< line_no << ": torso :" << str;
                this->getTorso()->push_back(point);
                break;
            case 9:
                qDebug()<< line_no << ": right hip :" << str;
                this->getRightHip()->push_back(point);
                break;
            case 10:
                qDebug()<< line_no << ": right knee :" << str;
                this->getRightKnee()->push_back(point);
                break;
            case 11:
                qDebug()<< line_no << ": right foot :" << str;
                this->getRightFoot()->push_back(point);
                break;
            case 12:
                qDebug()<< line_no << ": left hip :" << str;
                this->getLeftHip()->push_back(point);
                break;
            case 13:
                qDebug()<< line_no << ": left knee :" << str;
                this->getLeftKnee()->push_back(point);
                break;
            case 14:
                qDebug()<< line_no << ": left foot :" << str;
                this->getLeftFoot()->push_back(point);
                break;
            default:
                qDebug()<< line_no << ": other : error " << str;
                break;
        }

        line_no++;
    }

    return true;
}

/**
 * @brief CModel::getPointF 根据字符串解析出point
 * @return
 */
QPointF CModel::getPointF(const QString& _str)
{
    QPointF p;
    p.setX(0);
    p.setY(0);

    if( _str.length() <= 0 )
        return p;

    QStringList str_list = _str.split(' ');
    p.setX(str_list.at(0).toFloat());
    p.setY(str_list.at(1).toFloat());

    return p;
}

/**
 * @brief CModel::clearData 清除数据
 */
void CModel::clearData()
{
    this->getHead()->clear();
    this->getNeck()->clear();
    this->getRightShoulder()->clear();
    this->getRightElbow()->clear();
    this->getRightHand()->clear();
    this->getTorso()->clear();
    this->getRightHip()->clear();
    this->getRightKnee()->clear();
    this->getRightFoot()->clear();
    this->getLeftHip()->clear();
    this->getLeftKnee()->clear();
    this->getLeftFoot()->clear();
    this->getLeftShoulder()->clear();
    this->getLeftElbow()->clear();
    this->getLeftHand()->clear();

    return;
}

/**
 * @brief CModel::checkData 校验数据完整性
 * @return
 */
bool CModel::checkData()
{
    if( this->getHead()->size() <= 0 ||
        this->getLeftFoot()->size() <= 0
        ){
        qDebug()<< "checkData : error 数据个数不足 ";
        return false;
    }

    if( this->getHead()->size() != this->getLeftFoot()->size() ||
        this->getNeck()->size() != this->getRightShoulder()->size() ||
        this->getRightElbow()->size() != this->getRightHand()->size() ||
        this->getRightHand()->size() != this->getLeftShoulder()->size() ||
        this->getLeftShoulder()->size() != this->getLeftElbow()->size() ||
        this->getLeftHand()->size() != this->getTorso()->size() ||
        this->getTorso()->size() != this->getRightHip()->size() ||
        this->getRightHip()->size() != this->getRightKnee()->size() ||
        this->getRightKnee()->size() != this->getRightFoot()->size() ||
        this->getRightFoot()->size() != this->getLeftHip()->size() ||
        this->getLeftHip()->size() != this->getLeftKnee()->size() ||
        this->getLeftKnee()->size() != this->getNeck()->size()
            ){
        qDebug()<< "checkData : error 数据不一致 ";
        return false;
    }

    return true;
}
