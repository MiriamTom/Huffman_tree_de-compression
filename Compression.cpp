// Compression.cpp
#include "Compression.h"
#include "Huffman.h"
#include<bitset>

/**
* @brief
*
* @file Compression.cpp
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

//! Funkcia ktora kompresne subor do Huffmanovho kodu.
void Compression::compress(const string& inputFile, const string& outputFile) {
    //Otvor vstupne a vystupne subory.
    ifstream input(inputFile, ios::binary);
    ofstream output(outputFile, ios::binary);

    //Zacne ratat frekvencie kazdeho znaku vo vstupnom subore.
    map<char, unsigned> frequencies;
    readFrequenciesFromFile(input, frequencies);

    //Zostavi vstupny Huffmanov strom na zaklade poctu zratanych frekvencii.

    HuffmanTree huffmanTree(frequencies);

    //Pre kazdy znak vytvori huffmanov kode.
    map<char, string> codes = huffmanTree.buildHuffmanCodes(); 


    //Zapise do vystupneho suboru 
    writeHuffmanCodesToFile(output, codes);
    encodeAndWriteToFile(inputFile, output, codes);

    input.close();
    output.close();
    cout << "Compression was succesfull" << endl;
}
//! Funkcia pre zistovanie frekvencii zo vstupneho suboru a zaznamenávanie do mapy.
void Compression::readFrequenciesFromFile(ifstream& input, map<char, unsigned>& frequencies) {
    char ch;
    while (input.get(ch)) {
        frequencies[ch]++;
    }

    input.clear();
    input.seekg(0, ios::beg);
}
//! Funkcia pre zapis Huffmanovho kodu do vystupného suboru.
void Compression::writeHuffmanCodesToFile(ofstream& output, const map<char, string>& codes) {
    // Write the number of Huffman nodes
    output << codes.size() << "\n";
    // Print Huffman codes to console for debugging
    for (const auto& pair : codes) {
        //cout << "Huffman Code: " << pair.first << "=" << pair.second << endl;
    }
    // Write Huffman codes
    for (const auto& pair : codes) {
        output << pair.first << "=" << pair.second << " ";
    }
    output << "\n";
}
//! Funkcia pre konverziu retazca bitov na jeden bajt.
char Compression::bitsToByte(const string& bits) {
    char byte = 0;
    for (size_t i = 0; i < 8 && i < bits.length(); ++i) {
        if (bits[i] == '1') {
            byte |= (1 << (7 - i));
        }
    }
    return byte;
}
//! Funkcia pre zakodovanie a zapis bitov do vystupneho suboru na zaklade Huffmanovych kódov.
void Compression::encodeAndWriteToFile(string inputfile, ofstream& output, const map<char, string>& codes) {
    ifstream inputFile(inputfile, ios::binary);

    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << inputfile << endl;
        return;
    }

    char ch;
    string line;
    string bits;
    while (inputFile.get(ch)) {
        line += ch;
    }

    for (size_t i = 0; i < line.length(); ++i) {
        auto it = codes.find(line[i]);
        if (it != codes.end()) {
            // Convert Huffman code to binary
            string binaryCode = it->second;

            // Write binary code to the output file
            for (char bit : binaryCode) {
                //output.put(bit);
                bits += bit;
            }
        }
        else {
            cerr << "Error: No Huffman code found for character '" << line[i] << "'" << endl;
        }
        
    }
    ////////cout << bits;
    // Pad the last byte with zeros if needed
    size_t padding = 8 - bits.length() % 8;
    bits += string(padding, '0');

    // Write bytes to the output file
    for (size_t i = 0; i < bits.length(); i += 8) {
        bitset<8> byte(bits.substr(i, 8));
        output.put(static_cast<char>(byte.to_ulong()));
    }

    inputFile.close();
}