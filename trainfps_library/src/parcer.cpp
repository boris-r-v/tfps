#include <parcer.h>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <fstream>	//for ifstream	
#include <sstream>	//for stringstream
#include <iostream>	//for cout

#include <yaml-cpp/yaml.h>

namespace fs = boost::filesystem;
namespace bio = boost::iostreams;

int TFPS::parce( TFPS::CF cf )
{
    if ( fs::is_directory ( cf.yaml_ ) )
    {
	std::cout << cf.yaml_ << " is a directory containing:\n";
	    
	for( auto& entry : boost::make_iterator_range(fs::directory_iterator( cf.yaml_ ), {} ) )
	{
	    std::string s ( entry.path().string() );
	    
	    /*decompress*/
	    std::ifstream file(s, std::ios_base::in | std::ios_base::binary);
	    bio::filtering_streambuf<bio::input> in;
	    in.push(bio::gzip_decompressor());
	    in.push(file);
	    std::stringstream ss;
	    boost::iostreams::copy(in, ss );    

	    std::cout << "Parce: " << s << std::endl;

	    /*yaml-parce*/
	    try
	    {
		YAML::Node doc = YAML::Load ( ss );
		std::cout <<" EEE: " << doc << std::endl;	    
	    }
	    catch ( std::exception& e )
	    {
		std::cout << "  - fail to load: " << e.what() << std::endl;
	    }
	}
        return 0;
    }
    return 1;
}
