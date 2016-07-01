#include <iostream>
#include <zxing/parseQRInfo.h>
using namespace std;
 

int main(int argc, char** argv) {
	if (argc <= 1) {
		cout << "用法：" << argv[0] << "[选项] ... <图像>..."<<endl
			<< "从图片中读取条形码。" << endl
			<< endl
			<< "用法示例：" << endl
			<< "  zxing.exe *.jpg" << endl
			<< endl;
		return 1;
	}
	std::string filename;
	for (int i = 1; i < argc; i++) {
		filename = argv[i];
		}
		std::string DstName;
		/************************************************************************/
		/* 这就是解二维码接口函数 
		/* filename:是图片名
		/* BufferName: 是输出的信息
		/************************************************************************/
		
		parseQRInfo(filename,DstName);


	return 0;
   
}