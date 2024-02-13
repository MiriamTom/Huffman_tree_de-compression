// Decompression.h
#pragma once 
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>
#include "Huffman.h"

using namespace std;

/**
* @brief
*
* @file Decompression.h
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

/*! @class Decompression
*/

class Decompression {
public:
    HuffmanTree huffmanTree;  

    Decompression(const map<char, string>& frequencies);
    map<char, unsigned> convertStringFrequenciesToUnsigned(const map<char, string>& frequencies);
    static void decompress(const string& inputFile, const string& outputFile);
    static void readHuffmanCodesFromFile(ifstream& input, map<char, string>& frequencies);
    static void decodeAndWriteToFile(ifstream& input, ofstream& output, HuffmanNode* root);
};


