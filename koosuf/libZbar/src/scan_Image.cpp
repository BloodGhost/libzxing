#include <iostream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

using namespace zbar;
using namespace std;
using namespace cv;

#define RES(s) #s
#pragma comment(lib,"../Debug/libzbar-0.lib")

// 初次进行解码
string ZbarDecoder(Mat img)
{
	string result="0";
	// 创建一个读取器
	ImageScanner scanner;
	// 获取图像数据
	const void *raw = (&img)->data;
	// 配置这个读取器
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	// 包装图像数据
	Image image(img.cols, img.rows, "Y800", raw, (img.cols)*(img.rows));
	// 扫描条码图像
	int n = scanner.scan(image);
	// 提取结果
	result = image.symbol_begin()->get_data();
	// 提取结果
	for(Image::SymbolIterator symbol = image.symbol_begin();symbol != image.symbol_end();++symbol) 
	{
			cout << "decoded " << symbol->get_type_name()
				<< " symbol \"" << symbol->get_data() << '"' << endl;
	}
	image.set_data(NULL, 0);
	return result;
}
//对二值图像进行识别，如果失败则开运算进行二次识别
string GetQRInBinImg(Mat binImg)
{
	string result = ZbarDecoder(binImg);
	if(result.empty())
	{
		Mat openImg;
		// 获取常用的结构元素的形状
		cout<<"进行形态学运算！！！"<<endl;
		Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
		// 运行指定形态学操作
		morphologyEx(binImg, openImg, MORPH_OPEN, element);
		result = ZbarDecoder(openImg);
	}
	return result;
}

//获取一开始解不开的解码信息
string GetQR(Mat img)
{
	Mat binImg;
	//在otsu二值结果的基础上，不断增加阈值，用于识别模糊图像
	int thre = (int)threshold(img, binImg, 0.0, 255.0, cv::THRESH_OTSU);
	string result;
	while(result.empty() && thre<255)
	{
		threshold(img, binImg, thre, 255, cv::THRESH_BINARY);
		result = GetQRInBinImg(binImg);
		thre += 20;//阈值步长设为20，步长越大，识别率越低，速度越快
	}
	return result;
}
int main()
{
	Mat srcImage = imread("12.png",1);//barcode.png
	Mat dstImage ;
	if(srcImage.empty())
	{
		cout<<"打开图片失败,请查看路径是否正确！！！！"<<endl;
		return -1;
	}
	imshow("GG",srcImage);
	dstImage.create(srcImage.size(),CV_8UC1);
	// 进行二值化
	cvtColor(srcImage,dstImage,CV_BGR2GRAY);
	//ZbarDecoder(dstImage);
	GetQRInBinImg(dstImage);
	//imshow("解码图",srcImage);
	waitKey(0);
	return 1;
}