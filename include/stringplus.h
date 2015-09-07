#pragma once
#include "vars.h"

static std::string string_split(std::string& str,std::string token)
{
    string retstr = "";
    if(!str.empty() && !token.empty())
    {
        unsigned int pos = str.find(token);
        if(pos != std::string::npos && pos > 0)
        {
            retstr = str.substr(0,p-1);
            str = str.substr(p+1);
        }
    }
    return retstr;
}

static void string_lower(std::string& s)
{
    if(s.empty()) return;
    transform(s.begin(),s.end(),s.begin(), std::tolower);
}

static void erase_char(std::string &s,const char ch)
{
    std::string retstr = "";
    if(s.empty()) return retstr;

    std::string::iterator itr = s.begin();
    while(itr != s.end())
    {
        if((*itr)!=ch)
        {
            retstr += (*itr);
        }
        itr++;
    }
    s = retstr;
}

static void string_trim(std::string &s)
{
    erase_char(s,' ');
}
