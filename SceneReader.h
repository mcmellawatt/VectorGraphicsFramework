#pragma once

#include <string>
namespace Xml { class Element; }
namespace Framework { class Scene; }
class Color;

namespace Framework
{
    class SceneReader
    {
    public:
        static Framework::Scene readScene(const Xml::Element& rootElement);
		static Color toColor(const std::string& color);
    };
}
