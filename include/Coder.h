//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_CODER_H
#define ADAPTIVEHUFFMANCODING_CODER_H

#include <boost/filesystem.hpp>
#include <CodeTree.h>

class Coder {
	boost::filesystem::path mPath;
	CodeTree mCodeTree;

public:
	Coder(boost::filesystem::path path);
	void compressAndSave();

private:
	void readAndSave(boost::filesystem::ifstream &inFile, boost::filesystem::ofstream &outFile);
	void savePartial(boost::filesystem::ofstream& outFile, std::string &source);
	void saveEnd(boost::filesystem::ofstream &outFile, std::string &source);
	// void newResult(boost::dynamic_bitset<unsigned char>& result, int numBlocks);
};

#endif //ADAPTIVEHUFFMANCODING_CODER_H
