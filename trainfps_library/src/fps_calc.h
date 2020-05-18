#ifndef TFPS_FPS_CALC_H
#define TFPS_FPS_CALC_H
/**
    @brief 

*/

#include <string>
#include <set>
namespace TFPS
{

/**
    @brief 
*/
    class fps_calc
    {
	    std::set <std::string> devices_;
	public:
	    fps_calc() = default;
	    ~fps_calc() = default;

	    static fps_calc& instance();
	    void device( std::string const& );
	    std::set <std::string> const& device();
    };
}






#endif // TFPS_FPS_CALC_H