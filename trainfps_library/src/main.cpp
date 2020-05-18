#include <main.h>
#include <parcer.h>
#include <boost/program_options.hpp>		

namespace po = boost::program_options;


int TFPS::Main::run(int argc, char** argv)
{
    boost::program_options::options_description gen_desc("General options");
    gen_desc.add_options()
    ("dir,d",po::value<std::string>() ,"Specifies the directory with yaml-files from devices")
    ("output,o",po::value<std::string>() ,"Specifies the path to output csv file")
    ("help,h", "Produce help message")
    ("start,s",po::value<int>() , "Specifies begin of episodes")
    ("end,e",po::value<int>() , "Specifies end of episodes")
    ;

    boost::program_options::options_description desc;
    desc.add(gen_desc);

    po::variables_map vm;
    try
    {
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    
    }
    catch (po::error& e )
    {
	std::cout << e.what() << std::endl;
	std::cout << desc << std::endl;
	return 1;
    }

    if ( vm.empty() or vm.count("help") or !vm.count("dir") or !vm.count("output") )
    {
	std::cout << "  Welcome to TFPS - fps calculator  " << std::endl;
	std::cout << "  Author: Boris.R <borisrozhkin@gmail.com>" << std::endl << std::endl;
	std::cout << "  Usage: tfps -d ./bin -o out.csv"  << std::endl;

	std::cout << desc << std::endl;
	return 1;
    }

    std::string yaml_path ( vm["dir"].as<std::string>() );
    std::string csv_path ( vm["output"].as<std::string>() );
    int begin (-1), end(1000);

    try
    {
        begin = vm["start"].as <int>( );
    }
    catch ( std::exception & e )    
    {
    }
    try
    {
        end = vm["end"].as <int>( );
    }
    catch ( std::exception & e )    
    {
    }

    return TFPS::parce ( CF (yaml_path, csv_path, begin, end ) );
}