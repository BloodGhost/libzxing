#include <iostream>
#include <zxing/parseQRInfo.h>
using namespace std;
 

int main(int argc, char** argv) {
	if (argc <= 1) {
		cout << "�÷���" << argv[0] << "[ѡ��] ... <ͼ��>..."<<endl
			<< "��ͼƬ�ж�ȡ�����롣" << endl
			<< endl
			<< "�÷�ʾ����" << endl
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
		/* ����ǽ��ά��ӿں��� 
		/* filename:��ͼƬ��
		/* BufferName: ���������Ϣ
		/************************************************************************/
		
		parseQRInfo(filename,DstName);


	return 0;
   
}