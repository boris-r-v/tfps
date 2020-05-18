#ifndef TFPS_FPS_CALC_H
#define TFPS_FPS_CALC_H
/**
    @brief 

*/

#include <string>
#include <vector>
#include <map>
namespace TFPS
{
    struct capture;
/**
    @brief 
*/
    class fps_calc
    {
	    std::map <std::string, std::vector<int > > fps_;
	public:
	    fps_calc() = default;
	    ~fps_calc() = default;

	    static fps_calc& instance();

	    void add_captur( std::pair <std::string, capture> const& );

    	    std::string calc_fps( );
    };
}






#endif // TFPS_FPS_CALC_H