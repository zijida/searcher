#include "uri.h"

    #define
    static void item_patch(string& ret,string prefix,string item)
    {
        if(!item.empty())
        {
            ret = ret + prefix + item;
        }
    }

    // 拆分字符串为左右两部分，左部输出，右部赋值给原字符串。
    static string str_parse(string& s,string split)
    {
        string ret="";
        if(s.empty() ||split.empty()) return ret;

        try
        {
            unsigned p = s.find(split);
            if(p != string::npos)
            {
                ret = s.substr(0,p);
                s = s.substr(p+split.length(),string::npos);
            }
        }
        catch (const std::out_of_range &oor)
        {
            return ret;
        }
        return ret;
    }

 // 拆分字符串为左右两部分，左部输出，右部赋值给原字符串。
    static string str_rparse(string& s,string split)
    {
        string ret="";
        if(s.empty() ||split.empty()) return ret;

        try
        {
            unsigned p = s.rfind(split);
            if(p != string::npos)
            {
                ret = s.substr(p+split.length(),string::npos);
                s = s.substr(0,p);
            }
        }
        catch (const std::out_of_range &oor)
        {
            return ret;
        }
        return ret;
    }


    // 用同一个分隔符，拆分字符串，结果入栈。
    static deque<string> str_token(const char* s,char d)
    {
        char* p = NULL;
        deque<string> r;

        while((p=strchr(s,d))!=NULL)
        {
            r.push_back(string(s,p-s));
            s = (p+1);
        }
        r.push_back(string(s));
        return r;
    }



namespace http
{
    uri::uri()
    {
        is_url=false;
        is_absolute=false;
    }

    uri::~uri()
    {
        //dtor
    }

    void uri::set(short type,const char* s)
    {
        if(s == NULL) return;

        switch(type)
        {
            case SCHEME:    scheme=s; break;
            case HOST:      host=s; break;
            case PORT:      port=s; break;
            case QUERY:     query=s; break;
            case PATH:      path=s; break;
            case FRAGMENT:  fragment=s; break;
        }
    }

    const char* uri::get(short type)
    {
        switch(type)
        {
            case SCHEME:    return scheme.c_str();
            case HOST:      return host.c_str();
            case PORT:      return port.c_str();
            case QUERY:     return query.c_str();
            case PATH:      return path.c_str();
            case FRAGMENT:  return fragment.c_str();
            default:        return NULL;
        }
    }


    bool uri::valid_host()
    {
        if(host.length()<4) return false;

        // 域名结构
        string ts = host;
        deque<string> part = str_token(ts.c_str(),'.');
        if(part.size()>=1)
        {
            deque<string>::reverse_iterator it = part.rbegin();
            str_parse((*it),":");
            string extension = (*it);
            if(!extension.empty())
            {
                bool nums = true;
                for(size_t i=0;i<extension.length();i++)
                {
                    if(extension[i]<'0' || extension[i]>'9')
                    {
                        nums = false;
                        break;
                    }
                }
                if(nums) return true;
                return ext_valid(extension.c_str());
            }
            return true;
        }

        // IPV6格式（暂略）

        return false;
    }

    bool uri::valid_scheme()
    {
        if(scheme.empty()) return false;
        if(_stricmp(scheme.c_str(),"http")!=0 &&
           _stricmp(scheme.c_str(),"https")!=0 )
       {
           return false;
       }

       return true;
    }

    const char* uri::whole()
    {
        if(!is_url) return NULL;

        url = scheme;
        item_patch(url,"://",host);
        item_patch(url,":",port);
        item_patch(url,"/",path);
        item_patch(url,"?",query);
        item_patch(url,"#",fragment);

        return url.c_str();
    }

    bool uri::parse(const char* s)
    {
        string fs = s;
        // scheme部分
        scheme = str_parse(fs,"://");
        if(!(is_url = valid_scheme()))
        {
        }

        // host部分
        if(fs[0]=='/')
        {
            is_absolute = false;
        }
        else
        {
            host = str_parse(fs,"/");
            if(host.empty())
            {
                host = fs;
            }

            if(!(is_absolute=valid_host()))
            {
                fs = host + "/" + fs;
                host = "";
            }
            else
            {
                /// 此处仅IPV4有效，IPV6地址会出错。
                port = str_rparse(host,":");
                if(scheme.empty())
                {
                    scheme = "http";
                }
                is_url = true;
                is_absolute = true;
            }
        }
        //port = str_parse(host,":");
        path = str_parse(fs,"?");
        if(path.empty())
        {
            path = fs;
        }
        else
        {
            query = str_parse(fs,"#");
            if(query.empty())
            {
                query = fs;
            }
            else
            {
                fragment = fs;
            }
        }
        return true;
    }

    const char* uri::convert(const char* b,const char* u)
    {
        // 默认base_url是完整URL，作为相对路径url的基准存在。
        if( parse(u)  &&  is_absolute)   return whole();
        if(!parse(b)  || !is_absolute)   return NULL;

        deque<string> l = str_token(path.c_str(),'/');
        deque<string> r = str_token(u,'/');

        deque<string>::reverse_iterator itrl = l.rbegin();
        if((*itrl).empty() || (*itrl).find(".") != string::npos)
        {
            l.pop_back();
        }

        deque<string>::iterator itr = r.begin();

        query = "";
        fragment = "";
        path = "";

        if((*itr).empty())
        // 表示相对URL以"/"开头，则完全替换基准URL中的path部分。
        {
            path = u+1;
            return whole();
        }

        while(itr != r.end())
        {
            if((*itr)=="..")
            {
                l.pop_back();
                r.pop_front();
                itr = r.begin();
            }
            else if((*itr)==".")
            {
                r.pop_front();
                break;
            }
            else break;
        }

        std::copy(r.begin(),r.end(), std::back_inserter(l));
        itr = l.begin();
        while(itr != l.end())
        {
            path += (*itr);
            itr ++;

            if(itr != l.end())
            {
                path += "/";
            }
        }
        return whole();
    }
}
