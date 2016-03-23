#pragma once
#include "Layer.h"

#include <list>

namespace Framework
{
    class Scene
    {
    private:
        typedef std::list<Layer> LayerCollection;
        
    public:
        Scene(const int& width, const int& height);
        
        typedef LayerCollection::const_iterator LayerIterator;
        
        void pushBack(const Layer& layer);
        void remove(const Layer& layer);
        LayerIterator begin() const;
        LayerIterator end() const;
        
        int getWidth() const;
        int getHeight() const;
        
		void Scene::draw(HCanvas& canvas) const;
    private:
        LayerCollection myLayers;
        int myWidth;
        int myHeight;
    };
}
