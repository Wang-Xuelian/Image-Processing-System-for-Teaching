#include "DIPtest.h"
//#include "MyCamera.h"


using namespace cv;
using namespace std;


DIPtest::DIPtest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

DIPtest::~DIPtest()
{

}

//本地图像
void DIPtest::on_ImageLocal_clicked()
{
	img = imread("C://Users//wangx//Desktop//Image.jpg");
	cvtColor(img,img, COLOR_BGR2RGB);
	int w = img.cols;   //宽
	int h = img.rows;   //高
	//框 w*h=461*371
	if (w > h)
	{
		float ratio =(float) h / (float)w;
		cv::resize(img, img, Size(450, 450 * ratio));
	}
	else
	{
		float ratio = (float)w / (float)h;
		cv::resize(img, img, Size(350 * ratio, 350));
	}
	QImage src((const unsigned char*)img.data, img.cols, img.rows, img.cols*img.channels(), QImage::Format_RGB888);
	OriginText = new QLabel();
	OriginText->setPixmap(QPixmap::fromImage(src));
	ui.ImageArea->setWidget(OriginText);
}

/*int CMyCamera::Open(MV_CC_DEVICE_INFO* pstDeviceInfo)
{
	if (NULL == pstDeviceInfo)
	{
		return MV_E_PARAMETER;
	}

	int nRet = MV_OK;
	if (m_hDevHandle == NULL)
	{
		nRet = MV_CC_CreateHandle(&m_hDevHandle, pstDeviceInfo);
		if (MV_OK != nRet)
		{
			return nRet;
		}
	}

	nRet = MV_CC_OpenDevice(m_hDevHandle);
	if (MV_OK != nRet)
	{
		MV_CC_DestroyHandle(m_hDevHandle);
		m_hDevHandle = NULL;

		return nRet;
	}

	return MV_OK;
}
int CMyCamera::StartGrabbing()
{
	return MV_CC_StartGrabbing(m_hDevHandle);
}
*/

//拍摄图像
void DIPtest::on_ImageCamera_clicked()
{

}

//缩放
void DIPtest::on_Resize_clicked()
{
	Mat Resize_img;
	double ResizeValue;
	ResizeValue = ui.ResizeSpin->text().toDouble();
	int w = img.cols;   //宽
	int h = img.rows;   //高

						//框 w*h=461*371
	if (w > h)
	{
		float ratio = (float)h / (float)w;
		cv::resize(img, Resize_img, Size((450 * ResizeValue), (450 * ResizeValue) * ratio));
	}
	else
	{
		float ratio = (float)w / (float)h;
		cv::resize(img, Resize_img, Size((350 * ResizeValue) * ratio, (350 * ResizeValue)));
	}

	QImage src((const unsigned char*)Resize_img.data, Resize_img.cols, Resize_img.rows, Resize_img.cols*Resize_img.channels(), QImage::Format_RGB888);
	ProgressText = new QLabel();
	ProgressText->setPixmap(QPixmap::fromImage(src));
	ui.ImageArea_2->setWidget(ProgressText);

}

//亮度和对比度
void DIPtest::on_BrightContrast_clicked()
{
	int w = img.cols;
	int h = img.rows;
	int n = img.channels();
	Mat BC_img;
	BC_img = Mat::zeros(img.size(), img.type()); //创建一个和原图像大小 类型相同的空白图像
	double alpha = ui.ContrastSpin->text().toDouble(); //设置阿尔法值 对比度
	int bata = ui.BrightSpin->text().toInt();    //设置贝塔值 亮度

	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			if (n == 1)  //单通道
			{
				float a = img.at<uchar>(row, col);  //使用at()函数对图像像素值进行遍历
				BC_img.at<uchar>(row, col) = saturate_cast<uchar>(a*alpha + bata);  //公式
			}
			else if (n == 3)  //3通道
			{
				float x = img.at<Vec3b>(row, col)[0];
				float y = img.at<Vec3b>(row, col)[1];
				float z = img.at<Vec3b>(row, col)[2];
				BC_img.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(x*alpha + bata);
				BC_img.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(y*alpha + bata);
				BC_img.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(z*alpha + bata);
			}
		}
	}

	QImage src((const unsigned char*)BC_img.data, BC_img.cols, BC_img.rows, BC_img.cols*BC_img.channels(), QImage::Format_RGB888);
	ProgressText = new QLabel();
	ProgressText->setPixmap(QPixmap::fromImage(src));
	ui.ImageArea_2->setWidget(ProgressText);
}

//阈值化
void DIPtest::on_Threshold_clicked()
{
	Mat Gray_img, Thresh_img, AThresh_img;
	cvtColor(img, Gray_img, COLOR_RGB2GRAY);
	int n = 1;
	int ThreshType;
	ThreshType = ui.ThreshCombo->currentIndex();
	int ThreshValue, ThreshMax;
	ThreshValue = ui.ThreshSpin->text().toInt();
	ThreshMax = ui.ThreshMaxSpin->text().toInt();
	if (n == 1)
	{
		threshold(Gray_img, Thresh_img, ThreshValue, ThreshMax, ThreshType);

		QImage src((const unsigned char*)Thresh_img.data, Thresh_img.cols, Thresh_img.rows, Thresh_img.cols*Thresh_img.channels(), QImage::Format_Grayscale8);  //和直接cv显示不同???
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);
	}
	if(n==0)
	{
		adaptiveThreshold(Gray_img, AThresh_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 1);

		QImage src((const unsigned char*)AThresh_img.data, AThresh_img.cols, AThresh_img.rows, AThresh_img.cols*AThresh_img.channels(), QImage::Format_Indexed8);
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);
	}

}

//滤波
void DIPtest::on_Blur_clicked()
{
	Mat Blur_img;
	int BlurType;
	BlurType = ui.BlurCombo->currentIndex();
	int BlurSizeValue,KernelSize;
	BlurSizeValue = ui.BlurSizeSpin->text().toInt();
	KernelSize = BlurSizeValue * 2 + 1;
	if (BlurType == 0)
	{
		blur(img, Blur_img, Size(KernelSize, KernelSize), Point(-1, -1));
	}
	if (BlurType == 1)
	{
		medianBlur(img, Blur_img, KernelSize);
	}
	if (BlurType == 2)
	{
		GaussianBlur(img, Blur_img, Size(KernelSize, KernelSize), 0, 0);
	}

	QImage src((const unsigned char*)Blur_img.data, Blur_img.cols, Blur_img.rows, Blur_img.cols*Blur_img.channels(), QImage::Format_RGB888);
	ProgressText = new QLabel();
	ProgressText->setPixmap(QPixmap::fromImage(src));
	ui.ImageArea_2->setWidget(ProgressText);
}

//形态学处理
void DIPtest::on_ErodeDilate_clicked()
{
	Mat Morphology_img;
	Mat kernel;
	int MorphologyType;
	MorphologyType = ui.MorphologyCombo->currentIndex();
	int KernelSize;
	KernelSize = ui.MorphologySizeSpin->text().toInt();
	kernel = getStructuringElement(MORPH_RECT, Size(KernelSize, KernelSize), Point(-1, -1));
	if (MorphologyType == 0)
	{
		dilate(img, Morphology_img, kernel);

		QImage src((const unsigned char*)Morphology_img.data, Morphology_img.cols, Morphology_img.rows, Morphology_img.cols*Morphology_img.channels(), QImage::Format_RGB888);
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);
	}
	if (MorphologyType == 1)
	{
		erode(img, Morphology_img, kernel);

		QImage src((const unsigned char*)Morphology_img.data, Morphology_img.cols, Morphology_img.rows, Morphology_img.cols*Morphology_img.channels(), QImage::Format_RGB888);
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);

	}
	if (MorphologyType == 2)
	{
		morphologyEx(img, Morphology_img, MORPH_OPEN, kernel);

		QImage src((const unsigned char*)Morphology_img.data, Morphology_img.cols, Morphology_img.rows, Morphology_img.cols*Morphology_img.channels(), QImage::Format_RGB888);
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);
	}
	if (MorphologyType == 3)
	{
		morphologyEx(img, Morphology_img, MORPH_CLOSE, kernel);

		QImage src((const unsigned char*)Morphology_img.data, Morphology_img.cols, Morphology_img.rows, Morphology_img.cols*Morphology_img.channels(), QImage::Format_RGB888);
		ProgressText = new QLabel();
		ProgressText->setPixmap(QPixmap::fromImage(src));
		ui.ImageArea_2->setWidget(ProgressText);

	}


}