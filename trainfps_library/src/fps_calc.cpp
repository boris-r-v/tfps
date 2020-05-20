#include <data_structs.h>
#include <fps_calc.h>
#include <iostream>
#include <sstream>

TFPS::fps_calc& TFPS::fps_calc::instance()
{
    static TFPS::fps_calc inst;
    return inst;
}

void TFPS::fps_calc::add_captur( std::pair <std::string, capture> const& _v)
{
    fps_[_v.first].push_back( _v.second.grabMsec );
}

std::string TFPS::fps_calc::calc_fps( )
{
    std::stringstream ss;
    for ( auto& d : fps_ )
    {

	double max( d.second.front() ), min( d.second.front() ); 
	for  ( auto& ms : d.second )
	{
	    max = max < ms ? ms : max;
	    min = min > ms ? ms : min;
	}
	ss << d.first << ";\t" << ( max - min)/(1000 * d.second.size()) << std::endl;
    }
    return ss.str();
}