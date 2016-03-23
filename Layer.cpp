#include "Layer.h"

namespace Framework
{
    
    Layer::Layer(const std::string& alias) :
    myAlias(alias)
    {
    }
    
    void Layer::pushBack(const PlacedGraphic& placedGraphic)
    {
        myGraphics.push_back(placedGraphic);
    }
    
    void Layer::remove(const PlacedGraphic& placedGraphic)
    {
        myGraphics.remove(placedGraphic);
    }
    
    Layer::PlacedGraphicIterator Layer::begin() const
    {
        return myGraphics.begin();
    }
    
    Layer::PlacedGraphicIterator Layer::end() const
    {
        return myGraphics.end();
    }
    
    std::string Layer::getAlias() const
    {
        return myAlias;
    }
    
    bool Layer::operator==(const Layer& rhs) const
    {
        if (myAlias != rhs.myAlias)
        {
            return false;
        }
        
        if (myGraphics != rhs.myGraphics)
        {
            return false;
        }
        
        return true;
    }
    
    bool Layer::operator!=(const Layer& rhs) const
    {
        return !operator==(rhs);
    }
    
	void Layer::draw(HCanvas& canvas) const
	{
		for (PlacedGraphicIterator placedgraphic = begin() ; placedgraphic != end() ; ++placedgraphic)
		{
			placedgraphic->draw(canvas);
		}
	}
}
