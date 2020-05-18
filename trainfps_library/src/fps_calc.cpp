#include <fps_calc.h>

TFPS::fps_calc& TFPS::fps_calc::instance()
{
    static TFPS::fps_calc inst;
    return inst;
}

void TFPS::fps_calc::device( std::string const& _s )
{
    devices_.insert( _s );
}

std::set <std::string> const& TFPS::fps_calc::device()
{
    return devices_;
}
