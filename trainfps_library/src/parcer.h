#ifndef TFPS_PARCER_H
#define TFPS_PARCER_H
/**
    @brief 

*/

#include <string>
namespace TFPS
{

/**
    @brief Configure struct
*/
    struct CF
    {
	std::string yaml_, csv_;
	int begin_, end_;
	CF (std::string const& y, std::string const& c, int b, int e): yaml_(y), csv_(c), begin_(b), end_(e)
	{
	}
    };


    int parce( CF );
}
#endif //TFPS_PARCER_H
