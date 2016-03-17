#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#include <Core.h>
#include "HuffmanCode.h"


using namespace std;

namespace po = boost::program_options;

int main(int argc, const char* argv[]){
    po::options_description description("AdaptiveHuffmanCoding Usage");

    description.add_options()
            ("help,h", "Display this help message")
            ("input-files", po::value<std::vector<std::string>>(), "Input files")
            ("version,v", "Display the version number");

    po::positional_options_description p;
    p.add("input-files", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        std::cout << description;

        return 0;
    }

    if(vm.count("version")){
        std::cout << "AdaptiveHuffmanCoding version " << CORE_VERSION << std::endl;

        return 0;
    }


    if(vm.count("input-files")){
        std::vector<std::string> files = vm["input-files"].as<std::vector<std::string>>();
        for(std::string file : files){
            HuffmanCode h(file);
            h.run();

        }
    }

    return 0;
}