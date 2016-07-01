#ifndef parseQRInfo_h__
#define parseQRInfo_h__

#include <iostream>
#include <fstream>
#include <string>
#include <zxing/ImageReaderSource.h>
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <exception>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/multi/GenericMultipleBarcodeReader.h>

std::vector<zxing::Ref<zxing::Result>> decode(zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints);

std::vector<zxing::Ref<zxing::Result>> decode_multi(zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints);

int read_image(zxing::Ref<zxing::LuminanceSource> source, bool hybrid, std::string expected,std::string &QRResult);

int read_image(zxing::Ref<zxing::LuminanceSource> source, bool hybrid, std::string expected,std::string &QRResult);

std::string read_expected(std::string imagefilename);

bool parseQRInfo(int width,int height,unsigned char* buffer,std::string &QRResult);

bool parseQRInfo(std::string filename, std::string& QRResult);

#endif 
/*end parseQRInfo_h__*/