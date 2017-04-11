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

    private:
        //绘画骨骼
        void paintPointBones(QCustomPlot *customPlot);
        //绘画连线的骨骼
        void paintLineBones(QCustomPlot *customPlot);


    private:
      Ui::MainWindow *ui;

      QString demoName;
      QTimer dataTimer;
      QCPItemTracer *itemDemoPhaseTracer;
      int currentDemoIndex;

      //数据
      CModel m_model_;
};

#endif // MAINWINDOW_H
