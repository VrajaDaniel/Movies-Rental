#pragma once
#include <vector>
#include <cassert>
#include <sstream>

#include "Movie.h"

class MovieValidator
{
public:
    void validate(const Movie& p);
};

class ValidateException
{
    std::vector<std::string> msgs;
public:

    std::string getMsg()
    {
        std::string tmp;
        for (const auto& it : msgs)
        {
            tmp += it + "\n";
        }
        return tmp;
    }

    ValidateException(const std::vector<std::string>& errors) : msgs{errors}
    {
    }

    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
};

std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
void testValidator();
