#ifndef DATAGRAM_H
#define DATAGRAM_H

#include "vars.h"
/*
    HTTP Protocol Header Analysis Class
*/
namespace http
{
    class datagram
    {
        public:
            datagram();
            virtual ~datagram();
            datagram(const datagram& other);

            std::string get(std::string key);
            void set(std::string key,std::string value);

        protected:
            std::map<std::string,std::string> params;
    };

    class request : public datagram
    {
    public:
            request();
            ~request();

            std::string assemble();

    protected:
        std::string method;
        std::string uri;
        std::string version;
    };

    class response : public datagram
    {
    public:
        response();
        ~response();

        void parse(std::string str);
        void parse_fixline(std::string str);

    protected:
        std::string version;
        std::string ret_code;
        std::string reason;
    };

}

#endif // DATAGRAM_H
