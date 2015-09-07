#ifndef URI_H
#define URI_H

#include "vars.h"
#include "define_buffer.h"


using namespace std;

static const char* host_ext[] =
{
    "com",
    "net",
    "org",
    "gov",
    "edu",
    "cc",
    "tv",
    "cn",
    "tw",
    "hk",
    "jp",
    "kr",
    ""
};

static bool ext_valid(const char* s)
{
    int i = 0;

    while(_stricmp(host_ext[i],"")!=0)
    {
        if(_stricmp(host_ext[i],s)==0)
        {
            return true;
        }
        i++;
    }
    return false;
}

namespace http
{
    enum
    {
        SCHEME=0,
        HOST,
        PORT,
        PATH,
        QUERY,
        FRAGMENT
    };

    class uri
    {
        public:

            uri();
            virtual ~uri();

            void set(short type,const char* s);
            const char* get(short type);

            const char* whole();
            bool parse(const char* s);
            const char* convert(const char* b,const char* u);
        protected:

            bool valid_host();
            bool valid_scheme();

        public:
            string scheme;
            string host;
            string path;
            string query;
            string port;
            string fragment;
            string url;

            bool is_url;        // 是否符合URL格式
            bool is_absolute;   // 是否绝对路径URL
        private:
    };

}

#endif // URI_H
