//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_HUFMANCODE_H
#define ADAPTIVEHUFFMANCODING_HUFMANCODE_H

#include <string>

class HuffmanCode {
    std::string mFilename;
    bool mRename;

public:
    HuffmanCode(const std::string &filename, bool rename = false);

    void run(bool debug);
};


#endif //ADAPTIVEHUFFMANCODING_HUFMANCODE_H
