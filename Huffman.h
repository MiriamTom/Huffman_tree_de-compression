// Huffman.h
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <map> 
#include <queue>
#include <vector>

using namespace std;

/**
* @brief
*
* @file Huffman.h
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

/*! @class HuffmanNode
   Struktura reprezentujuca uzol Huffmanovho stromu.
*/

struct HuffmanNode {
    //! Udaj reprezentujuci znak (pre listy stromu).
    char data;           
    //! Frekvencia daneho znaku v povodnom texte.
    unsigned frequency;    
    //! Ukazovatel na laveho potomka uzla.
    HuffmanNode* left;      
    //! Ukazovatel na praveho potomka uzla.
    HuffmanNode* right;      
    /*!
        Konstruktor pre inicializaciu uzla pre list stromu.
        @return je HuffmanNode tj. vetva stromu.
        @param data znak
        @param frequency je frekvence znaku
    */
    HuffmanNode();
    HuffmanNode(char data, unsigned frequency);
    void printNode(int indent);
    /*!
        Konstruktor pre inicializaciu vnutorneho uzla stromu.
        @return je HuffmanNode tj. vetva stromu.
        @param frekvencia daneho uzla
        @param lavy potomok uzla
        @param pravy potomok uzla
    */
    HuffmanNode(unsigned frequency, HuffmanNode* left, HuffmanNode* right);
};
struct CompareNodes {
    bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

// Trieda predstavujuca Huffmanov strom.
class HuffmanTree {
public:
    //! Koren Huffmanovho stromu.
    HuffmanNode* root;       

    //! Verejna metoda pre zostrojenie Huffmanovho stromu na zaklade frekvencii znakov.
    void buildHuffmanTree(const map<char, unsigned>& frequencies);

    //! Verejna metoda pre rekurzivne odstranenie uzlov Huffmanovho stromu.
    void deleteHuffmanTree(HuffmanNode* node);

    //! Verejna metoda pre zostrojenie Huffmanovych kodov rekurzivnym prechodom stromu.
    void buildHuffmanCodes(HuffmanNode* node, string& code, map<char, string>& codes);
    //! Verejna metoda pre zostrojenie Huffmanovych kodov rekurzivnym prechodom stromu na zaklade frequencii po compressi.
    void buildTreeFromFrequencies(const map<char, string>& frequencies);
    //! Verejna metoda pre vykreslenie huffmanovho stromu do konzole.
    void printTreeStructure();

    /*!
        Konstruktor pre inicializaciu Huffmanovho stromu na zaklade frekvencii znakov.
        @return Huffmanov strom
        @param kontajner map obsahujuci znak a nezaporne cislo.
    */
    HuffmanTree() = default;
    HuffmanTree(const map<char, unsigned>& frequencies);
    //! Destruktor pre odstranenie Huffmanovho stromu.
    ~HuffmanTree();
    /*!
        Metoda pre zostrojenie a ziskanie mapy Huffmanovych kodov pre kazdy znak.
        @param kontajner map obsahujuci znak a nezaporne cislo.
    */
    map<char, string> buildHuffmanCodes();
    /*!
        Metoda pre ziskanie korena Huffmanovho stromu. 
        @return HuffmanNode
    */
    HuffmanNode* getRoot();
};


#endif // HUFFMAN_H
