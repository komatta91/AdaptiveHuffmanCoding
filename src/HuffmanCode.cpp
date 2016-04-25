//
// Created by Komatta on 2016-03-12.
//

#include <HuffmanCode.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <Coder.h>
#include <Decoder.h>

HuffmanCode::HuffmanCode(const std::string &filename, bool rename) : mFilename(filename), mRename(rename) {

}

void HuffmanCode::run(bool debug) {
    boost::filesystem::path path(mFilename);
    boost::system::error_code ec;
    if (!boost::filesystem::exists(path, ec)) {
        std::cout << mFilename << ": " << ec.message();
        return;
    }
    if (path.extension() != ".kf") {
        Coder coder(path);
        coder.compressAndSave();
        if (debug)
        {
            coder.printDebugInfo();
        }
    } else {
        Decoder decoder(path);
        decoder.decompressAndSave(mRename);
    }
}
