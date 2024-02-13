#include <iostream>
#include <filesystem>
#include "Compression.h"
#include "Decompression.h"
#include <iomanip>
#include <fstream>

using namespace std;

/**
* @brief
*
* @file PROJEKT_5.cpp
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

int main(int argc, char*argv[]) {
    

    string command = argv[2];
    string inputFile = argv[3];
    string compressedFile = argv[4];

    ifstream input(inputFile, ios::binary);
    ofstream output(compressedFile, ios::binary);

    // Check if the files are opened successfully
    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening input or output file." << endl;
        return -1;
    }
    if (command =="c") {
        Compression::compress(inputFile, compressedFile);    
        // Get the size of the input file
    ifstream inputFileStream(inputFile, ios::binary | ios::ate);
    streamsize inputSize = inputFileStream.tellg();
    inputFileStream.close();

    // Get the size of the compressed file
    ifstream compressedFileStream(compressedFile, ios::binary | ios::ate);
    if (!compressedFileStream.is_open()) {
        cerr << "Error opening compressed file." << endl;
        return -1;  
    }

    streamsize compressedSize = compressedFileStream.tellg();
    compressedFileStream.close();

    int compressedSizeInt = static_cast<int>(compressedSize);
    int inputSizeInt = static_cast<int>(inputSize);

    double compressionRatio = (static_cast<double>(compressedSizeInt) / inputSizeInt) * 100;
    // Output results
    cout << "Input file size: " << inputSize << " bytes\n";
    cout << "Compressed file size: " << compressedSize << " bytes\n";
    cout << "Compression ratio: " << setprecision(4) << compressionRatio << "%\n";
    cout << "******************************" << endl;
    }

    if (command == "d") {
        if (!input.is_open()) {
            cerr << "Error opening input or output file." << endl;
            return -1;
        }
        Decompression::decompress(inputFile, compressedFile);
    }



    return 0;
}