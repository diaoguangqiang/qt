#ifndef CMODEL_H
#define CMODEL_H

#include <QVector>
#include <QPointF>

/**
 * @brief 人体散点数据
line 1	Head 头
line 2	Neck 颈
line 3	Right Shoulder 右肩
line 4	Right Elbow 右肘
line 5	Right Hand 右手
line 6	Left Shoulder 左肩
line 7	Left Elbow 左肘
line 8	Left Hand 左手
line 9	Torso 躯干
line 10	Right Hip 右臀
line 11	Right Knee 右膝盖
line 12	Right Foot 右脚
line 13	Left Hip 左臀
line 14	Left Knee 左膝盖
line 15	Left Foot 左脚
 */

//定个关节点数据 15个点构成人体
const int PEOPLE_BONES = 15;

class CModel
{
public:
    CModel();

public:
    inline QVector<QPointF>* getHead(){ return &this->m_head_; }
    inline QVector<QPointF>* getNeck(){ return &this->m_neck_; }
    inline QVector<QPointF>* getRightShoulder(){ return &this->m_right_shoulder_; }
    inline QVector<QPointF>* getRightElbow(){ return &this->m_right_elbow_; }
    inline QVector<QPointF>* getRightHand(){ return &this->m_right_hand_; }
    inline QVector<QPointF>* getLeftShoulder(){ return &this->m_left_shoulder_; }
    inline QVector<QPointF>* getLeftElbow(){ return &this->m_left_elbow_; }
    inline QVector<QPointF>* getLeftHand(){ return &this->m_left_hand_; }
    inline QVector<QPointF>* getTorso(){ return &this->m_torso_; }
    inline QVector<QPointF>* getRightHip(){ return &this->m_right_hip_; }
    inline QVector<QPointF>* getRightKnee(){ return &this->m_right_knee_; }
    inline QVector<QPointF>* getRightFoot(){ return &this->m_right_foot_; }
    inline QVector<QPointF>* getLeftHip(){ return &this->m_left_hip_; }
    inline QVector<QPointF>* getLeftKnee(){ return &this->m_left_knee_; }
    inline QVector<QPointF>* getLeftFoot(){ return &this->m_left_foot_; }

    //校验数据完整性
    bool checkData();

private:
    //读取文件
    bool readTxt(const char*);
    //初始化
    bool initData();
    //根据字符串解析出point
    QPointF getPointF(const QString&);
    //清除数据
    void clearData();    

private:
    QVector<QPointF> m_head_; //头
    QVector<QPointF> m_neck_; //颈
    QVector<QPointF> m_right_shoulder_; //右肩
    QVector<QPointF> m_right_elbow_;// 右肘
    QVector<QPointF> m_right_hand_;// 右手
    QVector<QPointF> m_left_shoulder_;// 左肩
    QVector<QPointF> m_left_elbow_;// 左肘
    QVector<QPointF> m_left_hand_;// 左手
    QVector<QPointF> m_torso_;// 躯干
    QVector<QPointF> m_right_hip_;// 右臀
    QVector<QPointF> m_right_knee_;// 右膝盖
    QVector<QPointF> m_right_foot_;// 右脚
    QVector<QPointF> m_left_hip_;// 左臀
    QVector<QPointF> m_left_knee_;// 左膝盖
    QVector<QPointF> m_left_foot_;// 左脚
};

#endif // CMODEL_H
