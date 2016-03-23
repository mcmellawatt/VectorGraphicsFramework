#include "Layer.h"
#include "VectorGraphic.h"
#include "CppUnitLite/TestHarness.h"

#include <algorithm>
#include <map>

#define STR(a) #a

TEST(pushBack, Layer)
{
	Framework::Layer layer("Mountains");

    layer.pushBack(Framework::PlacedGraphic(VG::Point(11, 11), VG::HVectorGraphic(new VG::VectorGraphic)));
    layer.pushBack(Framework::PlacedGraphic(VG::Point(22, 22), VG::HVectorGraphic(new VG::VectorGraphic)));
    layer.pushBack(Framework::PlacedGraphic(VG::Point(33, 33), VG::HVectorGraphic(new VG::VectorGraphic)));

    Framework::Layer::PlacedGraphicIterator pos;
    int i;
    for (i = 0, pos = layer.begin(); pos != layer.end(); ++i, ++pos)
    {
    }

    int expectedSize = 3;
    CHECK_EQUAL(expectedSize, i);
}

TEST(getAlias, Layer)
{
	Framework::Layer layer("Sea");

    std::string expected("Sea");
    CHECK_EQUAL(expected, layer.getAlias());
}

TEST(remove, Layer)
{
	Framework::Layer layer("Air");

    layer.pushBack(Framework::PlacedGraphic(VG::Point(11, 11), VG::HVectorGraphic(new VG::VectorGraphic)));
    layer.pushBack(Framework::PlacedGraphic(VG::Point(22, 22), VG::HVectorGraphic(new VG::VectorGraphic)));
    layer.pushBack(Framework::PlacedGraphic(VG::Point(33, 33), VG::HVectorGraphic(new VG::VectorGraphic)));

    layer.remove(Framework::PlacedGraphic(VG::Point(33, 33), VG::HVectorGraphic(new VG::VectorGraphic)));

    Framework::Layer::PlacedGraphicIterator pos;
    int i;
    for (i = 0, pos = layer.begin(); pos != layer.end(); ++i, ++pos)
    {
    }

    int expectedSize = 2;
    CHECK_EQUAL(expectedSize, i);
}
