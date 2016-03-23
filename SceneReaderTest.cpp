#include "XmlReader.h"
#include "Element.h"
#include "Scene.h"
#include "SceneReader.h"
#include "BasicCanvas.h"
#include "BitmapFileProjector.h"
#include "WindowsBitmapDecoder.h"
#include "WindowsBitmapEncoder.h"
#include "CppUnitLite/TestHarness.h"

#define STR(a) #a

const char* const TestXml = STR(
<Scene width="800" height="600">
  <Layer alias="sky">
    <PlacedGraphic x="0" y="0">
      <VectorGraphic closed="true">
        <Point x="1" y="2" />
        <!-- Comment -->
        <Point x="3" y="4" />
        <Point x="5" y="6" />
      </VectorGraphic>
    </PlacedGraphic>
    <!-- Comment -->
    <PlacedGraphic x="700" y="0">
      <VectorGraphic closed="false">
        <Point x="7" y="8" />
        <Point x="9" y="10" />
        <Point x="11" y="12" />
      </VectorGraphic>
    </PlacedGraphic>
  </Layer>
  <Layer alias="mountains">
    <PlacedGraphic x="250" y="250">
      <VectorGraphic closed="false">
        <Point x="13" y="14" />
        <Point x="15" y="19" />
        <Point x="17" y="18" />
        <!-- etc... -->
      </VectorGraphic>
    </PlacedGraphic>
  </Layer>
</Scene>);

const char* const sceneXml = STR(
<Scene width="800" height="800">
  <Layer alias="bottom">
    <PlacedGraphic x="0" y="0">
      <VectorGraphic closed="true">
        <Stroke tip="square" size="7" color="FF0000" />
        <Point x="100" y="500" />
        <Point x="100" y="100" />
        <Point x="500" y="600" />
       </VectorGraphic>
    </PlacedGraphic>
    <PlacedGraphic x="400" y="300">
      <VectorGraphic closed="true">
        <Stroke tip="square" size="5" color="00FF00" />
        <Point x="0" y="0" />
        <Point x="0" y="100" />
        <Point x="100" y="100" />
        <Point x="100" y="0" />
      </VectorGraphic>
    </PlacedGraphic>
  </Layer>
  <Layer alias="top">
    <PlacedGraphic x="250" y="250">
      <VectorGraphic closed="false">
        <Stroke tip="square" size="3" color="0000FF" />
        <Point x="0" y="0" />
        <Point x="0" y="100" />
        <Point x="100" y="100" />
        <Point x="100" y="0" />
      </VectorGraphic>
    </PlacedGraphic>
  </Layer>
</Scene>);


TEST(ReadScene, SceneReader)
{
    std::stringstream xmlStream(TestXml);
    Xml::HElement root = Xml::Reader::loadXml(xmlStream);

    Framework::Scene s = Framework::SceneReader::readScene(*root);

    CHECK_EQUAL(800, s.getWidth());
    CHECK_EQUAL(600, s.getHeight());

    Framework::Scene::LayerIterator pos;
    int iLayer;
    for (iLayer = 0, pos = s.begin(); pos != s.end(); ++iLayer, ++pos)
    {
        const Framework::Layer& layer = (*pos);
        if (iLayer == 0)
        {
            // verify sky layer
            CHECK_EQUAL("sky", layer.getAlias());
            Framework::Layer::PlacedGraphicIterator graphic;
            int iGraphic;
            for (iGraphic = 0, graphic = layer.begin(); graphic != layer.end(); ++iGraphic, ++graphic)
            {
                if (iGraphic == 0)
                {
                    CHECK_EQUAL(VG::Point(0, 0), (*graphic).getPlacementPoint());
                    const VG::VectorGraphic& vg = (*graphic).getGraphic();
                    CHECK_EQUAL(true, vg.isClosed());
                    CHECK_EQUAL(3, vg.getPointCount());
                    CHECK_EQUAL(VG::Point(1, 2), vg.getPoint(0));
                    CHECK_EQUAL(VG::Point(3, 4), vg.getPoint(1));
                    CHECK_EQUAL(VG::Point(5, 6), vg.getPoint(2));

                }
                else if (iGraphic == 1)
                {
                    CHECK_EQUAL(VG::Point(700, 0), (*graphic).getPlacementPoint());
                    const VG::VectorGraphic& vg = (*graphic).getGraphic();
                    CHECK_EQUAL(false, vg.isClosed());
                }
            }

            CHECK_EQUAL(2, iGraphic);
        }
        else if (iLayer == 1)
        {
            // verify mountains layer
            CHECK_EQUAL("mountains", layer.getAlias());

            Framework::Layer::PlacedGraphicIterator graphic;
            int iGraphic;
            for (iGraphic = 0, graphic = layer.begin(); graphic != layer.end(); ++iGraphic, ++graphic)
            {
            }

            CHECK_EQUAL(1, iGraphic);
        }
    }

    // Expect 2 layers
    CHECK_EQUAL(2, iLayer);
}

//////////////////

namespace
{
    CodecLibrary makeCodecLibrary()
    {
        CodecLibrary codecLibrary;
        codecLibrary.registerEncoder(HBitmapEncoder(new WindowsBitmapEncoder));
        codecLibrary.registerDecoder(HBitmapDecoder(new WindowsBitmapDecoder));

        return codecLibrary;
    }
}

TEST(toBitmap, SceneReader)
{
    std::stringstream xmlStream(sceneXml);
    Cst::SharedPtr<Xml::Element> root = Xml::Reader::loadXml(xmlStream);
    Framework::Scene scene = Framework::SceneReader::readScene(*root);
    
    HCanvas canvas(new BasicCanvas(scene.getWidth(), scene.getHeight(), Color(100, 100, 100)));
    scene.draw(canvas);

    HProjector projector(new BitmapFileProjector("output_scene.bmp", makeCodecLibrary()));
    projector->projectCanvas(canvas);
}
