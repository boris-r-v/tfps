#include <parcer.h>
#include <data_structs.h>

#include <fstream>	//for ifstream	
#include <iostream>	//for cout
#include <opencv2/opencv.hpp>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>


namespace fs = boost::filesystem;

int TFPS::parce( TFPS::CF cf )
{
    if ( fs::is_directory ( cf.yaml_ ) )
    {
	std::cout << cf.yaml_ << " is a directory containing:\n";
	    
	for( auto& entry : boost::make_iterator_range(fs::directory_iterator( cf.yaml_ ), {} ) )
	{
	    std::string s ( entry.path().string() );

	    std::cout << "Parce: " << s << std::endl;

	    cv::FileStorage fs2( s, cv::FileStorage::READ);    
	    header h( fs2["header"] );
    
	    //std::cout << h << std::endl;	    	    
    
	    std::vector <shot> sh;
	    fs2["shots"] >> sh;

	    //for ( auto & d : sh ) std::cout << d << std::endl;

	}
        return 0;
    }
    return 1;
}



