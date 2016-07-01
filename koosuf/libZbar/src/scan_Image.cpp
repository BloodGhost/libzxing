#include <iostream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

using namespace zbar;
using namespace std;
using namespace cv;

#define RES(s) #s
#pragma comment(lib,"../Debug/libzbar-0.lib")

// ���ν��н���
string ZbarDecoder(Mat img)
{
	string result="0";
	// ����һ����ȡ��
	ImageScanner scanner;
	// ��ȡͼ������
	const void *raw = (&img)->data;
	// ���������ȡ��
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	// ��װͼ������
	Image image(img.cols, img.rows, "Y800", raw, (img.cols)*(img.rows));
	// ɨ������ͼ��
	int n = scanner.scan(image);
	// ��ȡ���
	result = image.symbol_begin()->get_data();
	// ��ȡ���
	for(Image::SymbolIterator symbol = image.symbol_begin();symbol != image.symbol_end();++symbol) 
	{
			cout << "decoded " << symbol->get_type_name()
				<< " symbol \"" << symbol->get_data() << '"' << endl;
	}
	image.set_data(NULL, 0);
	return result;
}
//�Զ�ֵͼ�����ʶ�����ʧ����������ж���ʶ��
string GetQRInBinImg(Mat binImg)
{
	string result = ZbarDecoder(binImg);
	if(result.empty())
	{
		Mat openImg;
		// ��ȡ���õĽṹԪ�ص���״
		cout<<"������̬ѧ���㣡����"<<endl;
		Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
		// ����ָ����̬ѧ����
		morphologyEx(binImg, openImg, MORPH_OPEN, element);
		result = ZbarDecoder(openImg);
	}
	return result;
}

//��ȡһ��ʼ�ⲻ���Ľ�����Ϣ
string GetQR(Mat img)
{
	Mat binImg;
	//��otsu��ֵ����Ļ����ϣ�����������ֵ������ʶ��ģ��ͼ��
	int thre = (int)threshold(img, binImg, 0.0, 255.0, cv::THRESH_OTSU);
	string result;
	while(result.empty() && thre<255)
	{
		threshold(img, binImg, thre, 255, cv::THRESH_BINARY);
		result = GetQRInBinImg(binImg);
		thre += 20;//��ֵ������Ϊ20������Խ��ʶ����Խ�ͣ��ٶ�Խ��
	}
	return result;
}
int main()
{
	Mat srcImage = imread("12.png",1);//barcode.png
	Mat dstImage ;
	if(srcImage.empty())
	{
		cout<<"��ͼƬʧ��,��鿴·���Ƿ���ȷ��������"<<endl;
		return -1;
	}
	imshow("GG",srcImage);
	dstImage.create(srcImage.size(),CV_8UC1);
	// ���ж�ֵ��
	cvtColor(srcImage,dstImage,CV_BGR2GRAY);
	//ZbarDecoder(dstImage);
	GetQRInBinImg(dstImage);
	//imshow("����ͼ",srcImage);
	waitKey(0);
	return 1;
}