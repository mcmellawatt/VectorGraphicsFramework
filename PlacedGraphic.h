#if !defined(PLACED_GRAPHIC_ALREADY_INCLUDED)
#define PLACED_GRAPHIC_ALREADY_INCLUDED

#include "Point.h"
#include "SharedPtr.h"
#include "VectorGraphic.h"

namespace Framework
{
    
    class PlacedGraphic
    {
    public:
        PlacedGraphic(const VG::Point& placement,
                      const VG::HVectorGraphic& graphic);
        
        PlacedGraphic();
        
        void setPlacementPoint(const VG::Point& placement);
        const VG::Point& getPlacementPoint() const;
        
        void setGraphic(const VG::HVectorGraphic& graphic);
        const VG::VectorGraphic& getGraphic() const;
        
		void draw(HCanvas& canvas) const;
    private:
        VG::Point myPlacementPoint;
        VG::HVectorGraphic myGraphic;
    };
    
    bool operator==(const PlacedGraphic& lhs, const PlacedGraphic& rhs);
    bool operator!=(const PlacedGraphic& lhs, const PlacedGraphic& rhs);
}

#endif