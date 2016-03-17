//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_DECODER_H
#define ADAPTIVEHUFFMANCODING_DECODER_H

#include <boost/filesystem.hpp>

class Decoder {
    boost::filesystem::path mPath;
public:
    Decoder(boost::filesystem::path path);

    void decompressAndSave();

};


#endif //ADAPTIVEHUFFMANCODING_DECODER_H
