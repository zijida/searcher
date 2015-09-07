#ifndef DEFINE_MISSION_INCLUDED
#define DEFINE_MISSION_INCLUDED

namespace http
{
    namespace type
    {
        const short HTML = 0x01;
        const short TEXT = 0x02;
        const short JPEG = 0x03;
        const short PNG  = 0x04;
        const short GIF  = 0x05;
        const short PDF  = 0x06;
        const short AVI  = 0x07;
        const short RMVB = 0x08;
        const short BMP  = 0x09;
        const short WAVE = 0x18;
        const short OTHER = 0x99;
    };

    class mission
    {
    public:
        short     type;
        buffer    url;          // URL´æ´¢Çø
        buffer    data;         // DATA´æ´¢Çø
        char      index[16];    // URLË÷Òý

        mission();
        void release();
    };
}

#endif // DEFINE_MISSION_INCLUDED
