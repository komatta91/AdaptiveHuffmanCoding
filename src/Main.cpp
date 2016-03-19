#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#include <Core.h>
#include "HuffmanCode.h"

int main(int argc, const char* argv[]){
    boost::program_options::options_description description("AdaptiveHuffmanCoding Usage");

    description.add_options()
            ("help,h", "Display this help message")
            ("rename,r", "Add \"_dec\" to decoded file (default false)")
            ("input-files", boost::program_options::value<std::vector<std::string>>(), "Input files to encode/decode. Input file will be encode and save with \"kf\" extension. If input file has \"kf\" extension will be decodes.")
            ("version,v", "Display the version number");

    boost::program_options::positional_options_description p;
    p.add("input-files", -1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    boost::program_options::notify(vm);

    if(vm.count("help")){
        std::cout << description;

        return 0;
    }

    if(vm.count("version")){
        std::cout << "AdaptiveHuffmanCoding version " << CORE_VERSION << std::endl;

        return 0;
    }

    bool rename = false;
    if(vm.count("rename")){
        rename = true;
    }

    if(vm.count("input-files")){
        std::vector<std::string> files = vm["input-files"].as<std::vector<std::string>>();
        for(std::string file : files){
            HuffmanCode h(file, rename);
            h.run();

        }
    }

    return 0;
}