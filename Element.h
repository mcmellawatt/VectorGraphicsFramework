#pragma once

#include "SharedPtr.h"

#include <string>
#include <vector>
#include <map>

namespace Xml
{
    class Element;
    typedef Cst::SharedPtr<Element> HElement;
    typedef std::map<std::string, std::string> AttributeMap;
    typedef std::vector<HElement> ElementList;
    
    class Element
    {
    public:
        Element(const std::string& name);
        std::string getName() const;
        
        void setAttribute(const std::string& name,
                          const std::string& value);
        
        std::string getAttribute(const std::string& name) const;
        
        ElementList getChildElements() const;
        AttributeMap getAttributes() const;
        
        void appendChild(const HElement& child);
        
    private:
        std::string myName;
        AttributeMap myAttributes;
        ElementList myElements;
    };
}
