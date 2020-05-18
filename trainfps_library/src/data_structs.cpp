#include <data_structs.h>
#include <fps_calc.h>


TFPS::device::device( cv::FileNode s )
{
    s["name"] >> name;
    fps_calc::instance().device( name );
    s["type"] >> type;
    s["readFrom"] >> readFrom;
    s["deviceId"] >> deviceId;
    //FIX ME - extDataFileNames sequence not read
}

TFPS::header::header( cv::FileNode s )
{
    s["appRevision"] >> appRevision;
    s["firstShotDate"] >> firstShotDate;
    
    int i = 1;
    std::string key = "capture1";
    cv::FileNode fn = s["captures"][key];

    while ( !fn.empty() )
    {
	devices.emplace ( key, device ( fn ) );
	key = "capture" + std::to_string ( ++i );
	fn = s["captures"][key];
    }	
}


std::ostream& TFPS::operator << ( std::ostream& s, header const& h )
{

    s << "appRevision: "<< h.appRevision << std::endl;
    s << "firstShotDate: " << h.firstShotDate << std::endl;
    s << "devices:" << std::endl;
    for ( auto const& c : h.devices )
    {
        s << " " << c.first << std::endl;
	s << c.second << std::endl;
    }
    return s;
}

std::ostream& TFPS::operator << ( std::ostream& s, device const& c )
{
    s << "  name: "<< c.name << std::endl;
    s << "  type: " << c.type << std::endl;
    s << "  readFrom: " << c.readFrom << std::endl;
    s << "  deviceId: " << c.deviceId << std::endl;

    return s;
}

void TFPS::read( cv::FileNode const& node, TFPS::shot& x, TFPS::shot const& default_value )
{
    if ( node.empty() )
	x = default_value;
    else
	x.read( node );	
}
void TFPS::shot::read( cv::FileNode const& n )
{
    n["grabNumber"] >> grabNumber;
    n["grabMsec"] >> grabMsec;
    for ( auto& d : fps_calc::instance().device() )
    {
	cv::FileNode fn = n[d];
	if ( !fn.empty() )
	{
	    capture c;
	    fn >> c;
	    captures.emplace( d, c );
	}
    }
}
std::ostream& TFPS::operator << ( std::ostream& s, shot const& h )
{
    s << "shot: " << std::endl;
    s << " grabNumber: " << h.grabNumber << std::endl;
    s << " grabMsec: " << h.grabMsec << std::endl;
    s << " captures: " << std::endl;
    for ( auto const & a : h.captures )
    {
	s <<"   device: " << a.first << ":" << std::endl;
	s << a.second << std::endl;
    }
    return s;
}

void TFPS::read( cv::FileNode const& node, TFPS::capture& x, TFPS::capture const& default_value )
{
    if ( node.empty() )
	x = default_value;
    else
	x.read( node );	
}
void TFPS::capture::read( cv::FileNode const& n )
{
    n["grabNumber"] >> grabNumber;
    n["grabMsec"] >> grabMsec;
    n["deviceSec"] >> deviceSec;
    n["deviceUsec"] >> deviceUsec;
}
std::ostream& TFPS::operator << ( std::ostream& s, capture const& c)
{
    s << "    grabNumber: " << c.grabNumber << std::endl;
    s << "    grabMsec: " << c.grabMsec << std::endl;
    s << "    deviceSec: "  << c.deviceSec << std::endl;
    s << "    deviceUsec: "  << c.deviceUsec << std::endl;
    return s;
}














