#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"
#include "cmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

      void setupDemo(int demoIndex);
      void setupQuadraticDemo(QCustomPlot *customPlot);
      void setupSimpleDemo(QCustomPlot *customPlot);
      void setupSincScatterDemo(QCustomPlot *customPlot);
      void setupScatterStyleDemo(QCustomPlot *customPlot);
      void setupLineStyleDemo(QCustomPlot *customPlot);
      void setupScatterPixmapDemo(QCustomPlot *customPlot);
      void setupDateDemo(QCustomPlot *customPlot);
      void setupTextureBrushDemo(QCustomPlot *customPlot);
      void setupMultiAxisDemo(QCustomPlot *customPlot);
      void setupLogarithmicDemo(QCustomPlot *customPlot);
      void setupRealtimeDataDemo(QCustomPlot *customPlot);
      void setupParametricCurveDemo(QCustomPlot *customPlot);
      void setupBarChartDemo(QCustomPlot *customPlot);
      void setupStatisticalDemo(QCustomPlot *customPlot);
      void setupSimpleItemDemo(QCustomPlot *customPlot);
      void setupItemDemo(QCustomPlot *customPlot);
      void setupStyledDemo(QCustomPlot *customPlot);
      void setupAdvancedAxesDemo(QCustomPlot *customPlot);
      void setupColorMapDemo(QCustomPlot *customPlot);
      void setupFinancialDemo(QCustomPlot *customPlot);

      void setupPlayground(QCustomPlot *customPlot);

    private slots:
      void realtimeDataSlot();
      void bracketDataSlot();
      void screenShot();
      void allScreenShots();
      void OnlineTreeViewDoubleClick(const QModelIndex & index);

    private:
        //绘画骨骼
        void paintPointBones(QCustomPlot *customPlot);
        //绘画连线的骨骼
        void paintLineBones(QCustomPlot *customPlot);
        //绘制单个动作
        void paintPointEveryBone(QCustomPlot *customPlot, int index);
        //绘画连线的骨骼
        void paintLineEveryBone(QCustomPlot *customPlot, int index);
        //初始化树形列表
        void InitTree();

    private:
      Ui::MainWindow *ui;

      QString demoName;
      QTimer dataTimer;
      QCPItemTracer *itemDemoPhaseTracer;
      int currentDemoIndex;

      //数据
      CModel m_model_;

      QStandardItemModel *m_tree_model_;

      QCPItemLine *arrow_head_neck;
      QCPItemLine *arrow_neck_right_shouler ;
      QCPItemLine *arrow_neck_left_shouler ;
      QCPItemLine *arrow_neck_torso ;
      QCPItemLine *arrow_right_shoulder_elbow ;
      QCPItemLine *arrow_right_elbow_hand ;
      QCPItemLine *arrow_left_shoulder_elbow ;
      QCPItemLine *arrow_left_elbow_hand ;
      QCPItemLine *arrow_torso_right_hip ;
      QCPItemLine *arrow_torso_left_hip ;
      QCPItemLine *arrow_right_hip_knee ;
      QCPItemLine *arrow_right_knee_foot ;
      QCPItemLine *arrow_left_hip_knee ;
      QCPItemLine *arrow_left_knee_foot ;

};

#endif // MAINWINDOW_H
