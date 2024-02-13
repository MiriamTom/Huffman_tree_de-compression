// Compression.h
#include <iostream>
#include <fstream>
#include <map>
#include "Huffman.h"
using namespace std;

/**
* @brief
*
* @file Compression.h
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

/*! @class Compression
*/

class Compression {
public:
    static void compress(const string& inputFile, const string& outputFile);
    static void readFrequenciesFromFile(ifstream& input, map<char, unsigned>& frequencies);
    static void writeHuffmanCodesToFile(ofstream& output, const map<char, string>& codes);
    static void encodeAndWriteToFile(string inputfile, ofstream& output, const map<char, string>& codes);
    static char bitsToByte(const string& bits);
};


