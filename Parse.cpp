#include "Parse.h"
#include <iostream>

namespace Parse
{
    void trim(std::string& sourceString,
              std::string const& trimmables)
    {
        std::string::size_type first = sourceString.find_first_not_of(trimmables);
        if (first == std::string::npos)
        {
            sourceString.clear();
            return;
        }
        sourceString = sourceString.substr(first);

        std::string::size_type last = sourceString.find_last_not_of(trimmables);
        sourceString = sourceString.substr(0, last + 1);
    }
    
    
    void eat(std::istream& sourceStream,
             const std::string& edibles)
    {
        int ch;
        while ((ch = sourceStream.peek()) != EOF)
        {
            if (edibles.find(ch) != std::string::npos)
            {
                sourceStream.ignore();
            }
            else
            {
                break;
            }
        }
    }

    
    std::string readUntil(std::istream& in, const std::string& delimiters)
    {
        std::string token;
        char ch;
        
        while (in.get(ch))
        {
            if (delimiters.find(ch) == std::string::npos)
            {
                token.push_back(ch);
            }
            else
            {
                in.putback(ch);
                break;
            }
        }
        
        return token;
    }
}