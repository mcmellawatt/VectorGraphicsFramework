#pragma once

#include "PlacedGraphic.h"
#include <list>
#include <string>

namespace Framework
{
    class Layer
    {
    private:
        typedef std::list<PlacedGraphic> PlacedGraphicCollection;

    public:
        Layer(const std::string& alias);

        typedef PlacedGraphicCollection::const_iterator PlacedGraphicIterator;

        void pushBack(const PlacedGraphic& placedGraphic);
        void remove(const PlacedGraphic& placedGraphic);
        PlacedGraphicIterator begin() const;
        PlacedGraphicIterator end() const;

        std::string getAlias() const;

        bool operator==(const Layer& rhs) const;
        bool operator!=(const Layer& rhs) const;

		void draw(HCanvas& canvas) const;
    private:
        PlacedGraphicCollection myGraphics;
        std::string myAlias;
    };
}
