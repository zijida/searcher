#include "datagram.h"
#include "stringplus.h"

typedef std::map<std::string,std::string>::iterator map_itr;

datagram::datagram()
{
    //ctor

}

datagram::~datagram()
{
    //dtor
}

datagram::datagram(const datagram& other)
{
    //copy ctor
}

std::string datagram::get(std::string key)
{
    map_itr mi = params.find(key);
    if(mi == params.end())
    {
        return "";
    }
    return mi.second();
}

void datagram::set(std::string key,std::string value)
{
    map_itr mi = params.find(key);
    if(mi == params.end())
    {
        params->insert(pair<std::string,std::string>(key,value));
    }
    else
    {
        mi[key] = value;
    }
}

void response::parse_fixline(std::string str)
{
    if(str.empty()) return;
    version = string_split(str," ");
    ret_code = string_split(str," ");
    reason = str;
}

void response::parse(std::string str)
{
    if(str.empty()) return;

    /// to lower
    string_lower(str);
    std::string line = string_split(str,"\r\n");
    // split the first line.
    parse_fixline(line);

    do
    {
        line = string_split(str,"\r\n");
        if(!line.empty())
        {
            /// prev string function:
            /// erase black space
            string_trim(line);
            std::string key = string_split(line,":");
            params->insert(pair<std::string,std::string>(key,line));
        }
    }
    while(!str.empty());
}
