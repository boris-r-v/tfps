#ifndef TFPS_DATA_STRUCT_H
#define TFPS_DATA_STRUCT_H

/**
    @brief 

*/

#include <opencv2/opencv.hpp>

#include <vector>
#include <map>
#include <string>

namespace TFPS
{

    struct device
    {
	std::string name, type, readFrom, deviceId;
	std::vector <std::string> extDataFileNames;
	device( cv::FileNode s );
    };

    struct header
    {
	std::string appRevision, firstShotDate;
	std::map <std::string, device> devices;
	header( cv::FileNode s );
    };

    std::ostream& operator << ( std::ostream& s, header const& );
    std::ostream& operator << ( std::ostream& s, device const& );


    struct capture
    {	
        int grabNumber, grabMsec, deviceSec, deviceUsec;

	void read ( cv::FileNode const& );
    };
    struct shot
    {
	int grabNumber, grabMsec;
	std::map <std::string, capture> captures;

	void read ( cv::FileNode const& );
    };
    std::ostream& operator << ( std::ostream& s, capture const& );
    std::ostream& operator << ( std::ostream& s, shot const& );

    void read( cv::FileNode const& node, shot& x, shot const& default_value = shot() );
    void read( cv::FileNode const& node, capture& x, capture const& default_value = capture() );
}

#endif // TFPS_DATA_STRUCT_H