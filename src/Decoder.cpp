//
// Created by Komatta on 2016-03-12.
//

#include <Decoder.h>
#include <boost/progress.hpp>
#include <bitset>

#define CHAR_BIT 8

Decoder::Decoder(boost::filesystem::path path) : mPath(path) { }

void Decoder::decompressAndSave(bool rename) {
    boost::filesystem::path destPath = mPath;
    destPath.replace_extension();
    if (rename) {
        boost::filesystem::path test = destPath.extension();
        destPath.replace_extension();
        destPath.concat("_dec");
        destPath.replace_extension(test);
    }

    if (boost::filesystem::exists(destPath)) {
        boost::filesystem::remove(destPath);
    }
    boost::filesystem::ifstream inFile(mPath, std::ios::binary);
    boost::filesystem::ofstream outFile(destPath, std::ios::binary);
    readAndSave(inFile, outFile);

    outFile.flush();
    outFile.close();
}

void Decoder::readAndSave(boost::filesystem::ifstream &inFile, boost::filesystem::ofstream &outFile) {
    std::string result;
    uintmax_t inputFileSize = boost::filesystem::file_size(mPath);
    uintmax_t read = 0;
    char data = 0;
    std::string bits;

    boost::progress_display show_progress(inputFileSize);
    while (inputFileSize-1 > read) {
        inFile.read(&data, 1);
        bits = std::bitset<8>(data).to_string();
        result = mCodeTree.getDecoded(bits);
        outFile << result;
        read += 1;
        ++show_progress;
    }

    inFile.read(&data, 1);
    char usableBits = 0;
    inFile.read(&usableBits, 1);
    ++show_progress;

    saveEnd(outFile, data, usableBits);
}

void Decoder::saveEnd(boost::filesystem::ofstream &outFile, char& data, char& usableBits) {
    std::bitset<8> last(data);
    std::string lastBits = last.to_string().substr(0, (unsigned int)usableBits);
    outFile << mCodeTree.getDecoded(lastBits);
}