#include <parcer.h>
#include <data_structs.h>
#include <fps_calc.h>

#include <fstream>	//for ifstream	
#include <iostream>	//for cout
#include <opencv2/opencv.hpp>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>


namespace fs = boost::filesystem;

static void read_calc( std::string const& s, std::string const& file );
static int get_episode( std::string const& str );
static bool handle_this_file( TFPS::CF const& cf, std::string const& s );

static std::stringstream out_str;

int TFPS::parce( TFPS::CF cf )
{
    out_str << "file;device1;fps_device1;device2;fps_device2;device3;fps_device3;device4;fps_device4;device5;fps_device5;device6;fps_device6"<< std::endl;;
    if ( fs::is_directory ( cf.yaml_ ) )
    {
	for( auto& entry : boost::make_iterator_range(fs::directory_iterator( cf.yaml_ ), {} ) )
	{
	    if ( handle_this_file( cf, entry.path().filename().string() ) )
	    {
		read_calc( entry.path().string(), entry.path().filename().string() );
	    }
	}
	if ( cf.csv_.empty() )
	{
	    std::cout << out_str.str() << std::endl;
	}
	else
	{
	    std::ofstream os ( cf.csv_ );
	    os << out_str.str();
	    os.close();
	}

        return 0;
    }
    return 1;
}

bool handle_this_file( TFPS::CF const& cf, std::string const& s )
{
    int episode = get_episode( s );
    return episode > cf.begin_ and cf.end_ > episode;
}

void read_calc( std::string const& s, std::string const& file )
{
    out_str << file << ";";
    cv::FileStorage fs2( s, cv::FileStorage::READ);    
    TFPS::header h( fs2["header"] );
    
    std::vector <TFPS::shot> sh;
    fs2["shots"] >> sh;

    for ( auto & d : sh ) 
    {
        for ( auto & c : d.captures ) 
	{
	    TFPS::fps_calc::instance().add_captur( c );
	}
    }
    out_str << TFPS::fps_calc::instance().calc_fps();

    out_str << std::endl;
}

int get_episode( std::string const& str )
{
    std::istringstream in ( str );
    std::string name, train, episode;
    std::getline(in, name, '.');
    std::getline(in, train, '.');
    std::getline(in, episode, '.');

    return std::stoi ( episode );    
}


