// Decompression.cpp
#include "Decompression.h"
#include "Huffman.h"
#include <sstream>
#include <string.h>

/**
* @brief
*
* @file Decompression.cpp
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

//! Funkcia ktora pri dekompressi zostavi strom z frequencii.
Decompression::Decompression(const map<char, string>& frequencies) {
    this->huffmanTree.buildHuffmanTree(convertStringFrequenciesToUnsigned(frequencies));
}

//! Funkcia ktora meni map obsahujuci stringy na unsigned.
map<char, unsigned> Decompression::convertStringFrequenciesToUnsigned(const map<char, string>& frequencies) {
    map<char, unsigned> unsignedFrequencies;
    for (const auto& pair : frequencies) {
        unsignedFrequencies[pair.first] = stoul(pair.second);
    }
    return unsignedFrequencies;
}
//! Funkcia ktora otvori vstupny subor precita huffmanovu mapu, zostavi strom a zapise do outputu prelozeny text.
void Decompression::decompress(const string& inputFile, const string& outputFile) {
    //Otvori input a output subory.
    ifstream input(inputFile, ios::binary);
    if (!input.is_open()) {
        cerr << "Error opening input file for decompression." << endl;
        return;
    }
    ofstream output(outputFile, ios::binary);
    if (!output.is_open()) {
        cerr << "Error opening output file for decompression." << endl;
        return;
    }
    // Precita si Huffmanov code a zostavi Huffmanov strom na zaklade frekvencii kazdeho znaku a najde koren stromu tj. znak s najvacsimi frekvenciami.
    map<char, string> frequencies;

    readHuffmanCodesFromFile(input, frequencies);

    // Convert string frequencies to unsigned
    map<char, unsigned> unsignedFrequencies;
    for (const auto& pair : frequencies) {
        unsignedFrequencies[pair.first] = stoul(pair.second);
    }

    // Build Huffman tree
    HuffmanTree huffmanTree;
    //huffmanTree.buildHuffmanTree(unsignedFrequencies);
    huffmanTree.buildTreeFromFrequencies(frequencies);
    HuffmanNode* current = huffmanTree.getRoot();

    //Decode input and write to file
    decodeAndWriteToFile(input, output, current);

    input.close();
    output.close();
    cout << "Decompression was succesfull" << endl;
}
//! Funkcia ktora precita huffmanove kody zo vstupneho suboru a zapise ako map<>.
void Decompression::readHuffmanCodesFromFile(ifstream& input, map<char, string>& codes) {
    char ch;
    unsigned numNodes;

    // Read the number of Huffman nodes
    if (!(input >> numNodes)) {
        cerr << "Error reading the number of Huffman nodes." << endl;
        return;
    }
    input.ignore();  // Ignore the newline character

    // Read Huffman codes
    for (unsigned i = 0; i < numNodes; i++) {
        // Read character and code
        char character;
        string code;

        // Read until '='
        while (input.get(ch) && ch != '=') {
            character = ch;
        }

        // Read the Huffman code
        while (input.get(ch) && ch != ' ' && ch != '\n') {
            code += ch;
        }

        // Store the Huffman code in the map
        codes[character] = code;

        //cout << "Read Huffman Code: " << character << "=" << code << endl;
    }

    // Debug: Print decoded Huffman codes to console
    for (const auto& pair : codes) {
        //cout << "Decoded Huffman Code: " << pair.first << "=" << pair.second << endl;
    }
}
//! Funkcia ktora dekoduje binarny kod a zapisuje do suboru text.
void Decompression::decodeAndWriteToFile(ifstream& input, ofstream& output, HuffmanNode* root) {
  char byte;
  HuffmanNode* current = root;

  input.get(byte);

  while (input.get(byte)) {
    for (int i = 7; i >= 0; --i) {
      char bit = ((byte >> i) & 1) ? '1' : '0';

      //cout << "Read Bit: " << bit << endl;

      if (bit == '0') {
        // Move left in the Huffman tree
        current = current->left;
      } else if (bit == '1') {
        // Move right in the Huffman tree
        current = current->right;
      } else {
        // Unexpected bit value
        cerr << "Unexpected bit value: " << bit << endl;
        return;
      }

      // Check if we've reached a leaf node
      if (current->left == nullptr && current->right == nullptr) {
        // Write the decoded character to the output file
        output.put(current->data);

        // Reset the current node to the root
        current = root;

      }
    }
  }

  output.close();
}

