#pragma once

#include <iosfwd>
#include <string>

namespace Parse
{
    void trim(std::string& sourceString,
              std::string const& trimmables = " \t\n");
    
    void eat(std::istream& sourceStream,
             std::string const& edibles = " \t\n");
    
    std::string readUntil(std::istream& in, const std::string& delimiters);
};
