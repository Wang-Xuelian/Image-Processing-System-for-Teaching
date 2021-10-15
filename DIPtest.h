#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DIPtest.h"
//#include<QGraphicsScene>
//#include<QGraphicsView>                   //graphicsview
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include "opencv2/highgui.hpp"   
#include "opencv2/opencv.hpp"           //opencv申明
//#include <qfiledialog.h>                //getopenfilename 类申明
//#include <qlabel.h>                     //label类
//#include <QTimer>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
//#include "MyCamera.h"

using namespace cv;


class DIPtest : public QMainWindow
{
	Q_OBJECT

public:
	DIPtest(QWidget *parent = Q_NULLPTR);
	~DIPtest();
	
//	static int a;
//	static int b;
//	static int ra;

private:
	Ui::DIPtestClass ui;
	QLabel *OriginText;
	QLabel *ImageArea;
	QLabel *ProgressText;
	QLabel *ImageArea_2;
	Mat img;

private slots:
    void on_ImageLocal_clicked();
	void on_ImageCamera_clicked();
	void on_Resize_clicked();
	void on_BrightContrast_clicked();
	void on_Threshold_clicked();
	void on_Blur_clicked();
	void on_ErodeDilate_clicked(); 




};
