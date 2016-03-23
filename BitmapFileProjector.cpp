#include "BitmapFileProjector.h"
#include <fstream>

BitmapFileProjector::BitmapFileProjector(const std::string& filename, const CodecLibrary& codecLibrary) : myFilename(filename), myCodecLibrary(codecLibrary)
{
}

void BitmapFileProjector::projectCanvas(const HCanvas& canvas)
{
	HBitmapIterator canvasIterator = canvas->createBitmapIterator();
	HBitmapEncoder encoder = myCodecLibrary.createEncoder("image/x-ms-bmp",canvasIterator);
	std::ofstream ofs(myFilename.c_str(), std::ios::binary);
	encoder->encodeToStream(ofs);
}