#ifndef _BufferBitmapSource_h__
#define _BufferBitmapSource_h__



#include <zxing/LuminanceSource.h>
using namespace zxing; 


class BufferBitmapSource : public LuminanceSource {
private:
	typedef LuminanceSource Super;
	int width, height; 
	ArrayRef<char> buffer; 

public:
	BufferBitmapSource(int inWidth, int inHeight, ArrayRef<char> inBuffer); 
	~BufferBitmapSource(); 

	int getWidth() const; 
	int getHeight() const; 
	ArrayRef<char> getRow(int y, ArrayRef<char> row) const; 
	ArrayRef<char> getMatrix() const; 
};

#endif 

