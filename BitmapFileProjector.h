#pragma once

#include "WindowsBitmapEncoder.h"
#include "CodecLibrary.h"
#include "BasicCanvas.h"
#include "IProjector.h"

class BitmapFileProjector : public IProjector
{
public:
	BitmapFileProjector(const std::string&, const CodecLibrary&);
	void projectCanvas(const HCanvas& canvas);
private:
	std::string myFilename;
	CodecLibrary myCodecLibrary;
};