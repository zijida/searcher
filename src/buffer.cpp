#include "vars.h"
#include "define_buffer.h"

namespace http
{
    buffer::buffer()
    {
        _data = 0;
        _size = 0;
        _curr = 0;
    }

    buffer::buffer(size_t len)
    {
        balloc(len);
    }

    buffer::~buffer()
    {
        bfree();
    }

    bool buffer::valid() { return (_data!=NULL&&_size>0); }
    void buffer::clean()
    {
        if(valid())
        {
            memset(_data,0,_size);
            _curr = 0;
        }
    }

    void buffer::bassign(void* data,size_t len)
    {
        bool bv = valid();
        if(!bv ||(bv && _size<len))
        {
            balloc(len);
        }
        memcpy(_data,data,len);
    }

    void buffer::bappend(void* data,size_t len)
    {
        bool bv = valid();
        if(!bv ||(_size-_curr<len))
        {
            balloc(len);
        }
        memcpy(_data+_curr,data,len);
    }

    bool buffer::balloc(size_t l)
    {
        size_t nl = 0;
        while(nl<l) nl += MIN_BUFFER_SIZE;

        if(valid())
        {
            if(_size>nl &&(_size-nl)<=MAX_BUFFER_SIZE)
            {
                return true;
            }
            else bfree();
        }

        _data = malloc(nl);
        if(_data!=NULL)
        {
            _size = nl;
        }

        return (_data != NULL);
    }

    void buffer::bfree()
    {
        if(valid())
        {
            free(_data);
            _data = 0;
            _size = 0;
            _curr = 0;
        }
    }

}
