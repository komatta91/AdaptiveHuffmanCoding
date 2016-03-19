//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_DECODER_H
#define ADAPTIVEHUFFMANCODING_DECODER_H

#include <boost/filesystem.hpp>

#include "CodeTree.h"

class Decoder {
    boost::filesystem::path mPath;
    CodeTree mCodeTree;

public:
    Decoder(boost::filesystem::path path);
    void decompressAndSave();

private:
    void readAndSave(boost::filesystem::ifstream &inFile, boost::filesystem::ofstream &outFile);
    void saveEnd(boost::filesystem::ofstream &outFile, char& data, char& usableBits);

};


#endif //ADAPTIVEHUFFMANCODING_DECODER_H
