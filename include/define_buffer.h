#ifndef DEFINE_BUFFER_H_INCLUDED
#define DEFINE_BUFFER_H_INCLUDED

namespace http
{
    #define  MIN_BUFFER_SIZE 0x10000  // 页基准： 4kb
    #define  MAX_BUFFER_SIZE 0x80000  // 页基准： 512kb

    class buffer
    {
    public:
        size_t   _size;
        size_t   _curr;
        void*    _data;

        buffer();
        buffer(size_t len);

        ~buffer();

        bool valid();
        void clean();
        void bassign(void* data,size_t len);
        void bappend(void* data,size_t len);
        bool balloc(size_t len);
        void bfree();
    };
}
#endif // DEFINE_BUFFER_H_INCLUDED
