#include "vars.h"
#include "define_buffer.h"
#include "define_mission.h"

namespace http
{
    mission::mission()
    {
        type = type::NONE;
        memset(index,0,16);
    }
}
