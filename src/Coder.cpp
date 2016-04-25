//
// Created by Komatta on 2016-03-12.
//

#include <Coder.h>
#include <iostream>
#include <bitset>
#include <map>
#include <boost/progress.hpp>

#define CHAR_BIT 8

Coder::Coder(boost::filesystem::path path) : mPath(path), outputFileLength(0), numOutputCodeword(0) { }

void Coder::compressAndSave() {
    boost::filesystem::path destPath = mPath;
    destPath.concat(".kf");
    if (boost::filesystem::exists(destPath)) {
        boost::filesystem::remove(destPath);
    }
    boost::filesystem::ifstream inFile(mPath, std::ios::binary);
    boost::filesystem::ofstream outFile(destPath, std::ios::binary);
    readAndSave(inFile, outFile);

    outFile.flush();
    outFile.close();
}

void Coder::printDebugInfo()
{
    std::cout << "Data:" << std::endl;
    std::cout << " - avg codeword length:" << (double)outputFileLength / numOutputCodeword << std::endl;
    std::cout << " - input file length:" << outputFileLength << std::endl;
    std::cout << " - output file length:" << outputFileLength << std::endl;
    std::cout << " - compress ratio:" << outputFileLength / (numOutputCodeword * 8.0) << std::endl;
}

void Coder::readAndSave(boost::filesystem::ifstream &inFile, boost::filesystem::ofstream &outFile) {
    std::string result;
    uintmax_t inputFileSze = boost::filesystem::file_size(mPath);
    uintmax_t read = 0;
    char data = 0;

    std::string temp;
    boost::progress_display show_progress(inputFileSze);
    while (inputFileSze > read) {
        inFile.read(&data, 1);
        numOutputCodeword++;
        temp = mCodeTree.getCode(data);
        outputFileLength += temp.size();
        result += temp;
        savePartial(outFile, result);
        read += 1;
        ++show_progress;
    }
    saveEnd(outFile, result);
}

void Coder::savePartial(boost::filesystem::ofstream &outFile, std::string &source) {
    if (source.size() >= CHAR_BIT) {
        while (source.size() >= CHAR_BIT) {
            std::string first = source.substr(0, CHAR_BIT);
            if (source.size() > 8) {
                source = source.substr(CHAR_BIT, source.size());// 4h spent to find teh problem - redundant +1 :-/
            }
            else {
                source.clear();
            }
            char toWrite = static_cast<char>(std::bitset<8>(first).to_ulong());
            outFile.write(&toWrite, 1);
        }
    }
}

void Coder::saveEnd(boost::filesystem::ofstream &outFile, std::string &source) {
    //TODO Tajniki w ostatnim bajcie maż zapisane ile bitów przedostatniego bajta wchodzi do zakodowanego pliku pozostałe to wyrównane zera
    int lastbits = source.size();
    source += "00000000";
    source = source.substr(0, CHAR_BIT);
    char toWrite = static_cast<char>(std::bitset<8>(source).to_ulong());
    outFile.write(&toWrite, 1);
    toWrite = static_cast<char>(lastbits);
    outFile.write(&toWrite, 1);
}