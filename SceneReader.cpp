#include "SceneReader.h"
#include "Scene.h"
#include "Element.h"
#include "VectorGraphic.h"
#include <sstream>
#include "Color.h"
#include "SquareStroke.h"

namespace
{
    int toInt(const std::string& s)
    {
        int value;
        std::stringstream ss(s);
        ss >> value;
        
        return value;
    }
    
	void addStroke( VG::VectorGraphic& vg, const std::string& tip, const int& size, const Color& color)
	{
		if(tip == "square")
		{
			vg.setStroke(HStroke(new SquareStroke(size,color)));
		}
		else
		{
			std::stringstream message;
			message << "Invalid tip specified: \"" << tip;
			throw std::runtime_error(message.str());
		}
	}

    VG::HVectorGraphic readVectorGraphic(const Xml::Element& vgElement)
    {
        VG::HVectorGraphic vg(new VG::VectorGraphic());
        
        std::string closed = vgElement.getAttribute("closed");
        if (closed == "true")
        {
            vg->closeShape();
        }
        else if (closed == "false")
        {
            vg->openShape();
        }
        else
        {
            throw std::runtime_error("Invalid VectorGraphic attribute");
        }
        
        Xml::ElementList children = vgElement.getChildElements();
        Xml::ElementList::const_iterator child;
        for (child = children.begin(); child != children.end(); ++child)
        {
			if ((*child)->getName() == "Point")
			{
				int x = toInt((*child)->getAttribute("x"));
				int y = toInt((*child)->getAttribute("y"));
				vg->addPoint(VG::Point(x, y));
			}
			else if ((*child)->getName() == "Stroke")
			{
				std::string tip = (*child)->getAttribute("tip");
				int size = toInt((*child)->getAttribute("size"));
				Color c = Framework::SceneReader::toColor((*child)->getAttribute("color"));
				addStroke(*vg, tip, size, c);
			}
        }
        
        return vg;
    }
    
    void readGraphic(Framework::Scene& scene,
                     Framework::Layer& layer,
                     const Xml::Element& graphicElement)
    {
        if (graphicElement.getName() != "PlacedGraphic")
        {
            throw std::runtime_error("Expected PlacedGraphic");
        }
        
        Framework::PlacedGraphic pg;
        int x = toInt(graphicElement.getAttribute("x"));
        int y = toInt(graphicElement.getAttribute("y"));
        
        if (x < 0 || y < 0 ||
            x > scene.getWidth() || y > scene.getHeight())
        {
            throw std::runtime_error("PlacedGraphic out of bounds");
        }
        
        pg.setPlacementPoint(VG::Point(x, y));
        
        Xml::ElementList vectorGraphics = graphicElement.getChildElements();
        Xml::ElementList::const_iterator vgElement;
        for (vgElement = vectorGraphics.begin(); vgElement != vectorGraphics.end(); ++vgElement)
        {
            // TODO - assert - there should only be one of these
            pg.setGraphic(readVectorGraphic(*(*vgElement)));
        }
        
        layer.pushBack(pg);
    }
    
    void readLayer(Framework::Scene& scene,
                   const Xml::Element& layerElement)
    {
        if (layerElement.getName() != "Layer")
        {
            throw std::runtime_error("Expected Layer");
        }
        
        Framework::Layer layer(layerElement.getAttribute("alias"));
        
        Xml::ElementList graphics = layerElement.getChildElements();
        Xml::ElementList::const_iterator graphic;
        for (graphic = graphics.begin(); graphic != graphics.end(); ++graphic)
        {
            readGraphic(scene, layer, *(*graphic));
        }
        
        scene.pushBack(layer);
    }
}

namespace Framework
{

Scene SceneReader::readScene(const Xml::Element& rootElement)
{
    if (rootElement.getName() != "Scene")
    {
        throw std::runtime_error("Expected Scene");
    }
    
    int width = toInt(rootElement.getAttribute("width"));
    int height = toInt(rootElement.getAttribute("height"));
    Scene theScene(width, height);
    
    Xml::ElementList layers = rootElement.getChildElements();
    Xml::ElementList::const_iterator layer;
    for (layer = layers.begin(); layer != layers.end(); ++layer)
    {
        readLayer(theScene, *(*layer));
    }
    
    return theScene;
}

Color SceneReader::toColor(const std::string& color)
{
	std::string red, green, blue;
	std::stringstream ss;
	int redInt, greenInt, blueInt;

	if (color.length() != 6)
	{
		std::stringstream message;
		message << "Invalid color format: " << color;
		throw std::runtime_error(message.str());
	}
	red = color.substr(0,2);
	green = color.substr(2,2);
	blue = color.substr(4,2);
	ss << std::hex << red;
	ss >> redInt;
	ss.clear();
	ss.str(std::string());
	ss << std::hex << blue;
	ss >> blueInt;
	ss.clear();
	ss.str(std::string());
	ss << std::hex << green;
	ss >> greenInt;
	ss.clear();
	ss.str(std::string());
	Color c(redInt,greenInt,blueInt);
	return c;
}

}