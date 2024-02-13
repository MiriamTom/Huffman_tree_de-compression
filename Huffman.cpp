// Huffman.cpp
#include "Huffman.h"
#include<iomanip>
#include <string>  // Include the <string> header for stoul
/**
* @brief
*
* @file Huffman.cpp
* @author TOM0468
* @date 2023-11-26
* @version 1.0
*
*/

HuffmanNode::HuffmanNode()
{
    this->data = NULL;
    this->frequency = NULL;
    this->left = nullptr;
    this->right = nullptr;
}

//! Konstruktor pre inicializaciu uzla Huffmanovho stromu pre list stromu.
HuffmanNode::HuffmanNode(char data, unsigned frequency) {
    this->data = data;
    this->frequency = frequency;
    this->left = nullptr;
    this->right = nullptr;
}

//! Konstruktor pre inicializaciu vnutorneho uzla Huffmanovho stromu.
HuffmanNode::HuffmanNode(unsigned frequency, HuffmanNode* left, HuffmanNode* right) {
    this->data = '\0';
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

//! Konstruktor Huffmanovho stromu pre zostrojenie stromu na zaklade frekvencii znakov.
HuffmanTree::HuffmanTree(const map<char, unsigned>& frequencies) {
    buildHuffmanTree(frequencies);
}

//! Destruktor Huffmanovho stromu na odstranenie stromu z pamati.
HuffmanTree::~HuffmanTree() {
    deleteHuffmanTree(root);
}

//! Privatna metoda pre zostrojenie Huffmanovho stromu na zaklade frekvencii znakov.
void HuffmanTree::buildHuffmanTree(const map<char, unsigned>& frequencies) {
    auto compare = [](HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    };

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(compare)> pq(compare);

    // Initialization of priority queue with leaf nodes based on frequencies
    for (auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Creating Huffman tree from priority queue
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* internalNode = new HuffmanNode(left->frequency + right->frequency, left, right);
        pq.push(internalNode);
    }

    // The root of the Huffman tree is the last element in the priority queue
    root = pq.top();
    // Print the Huffman tree to the console
    //cout << "Huffman Tree Structure:" << endl;
    //root->printNode(0);
}
void HuffmanTree::printTreeStructure() {
    root->printNode(0);
}

//! Privatna metoda pre rekurzivne odstranenie uzlov Huffmanovho stromu.
void HuffmanTree::deleteHuffmanTree(HuffmanNode* node) {
    if (node != nullptr) {
        deleteHuffmanTree(node->left);
        deleteHuffmanTree(node->right);
        delete node;
    }
}

//! Metoda pre zostrojenie a ziskanie mapy Huffmanovych kodov pre kazdy znak.
map<char, string> HuffmanTree::buildHuffmanCodes() {
    map<char, string> codes;
    string code;
    buildHuffmanCodes(root, code, codes);
    return codes;
}

//! Privatna rekurzivna metoda pre zostrojenie Huffmanovych kodov rekurzivnym prechodom stromu.
void HuffmanTree::buildHuffmanCodes(HuffmanNode* node, string& code, map<char, string>& codes) {
    if (node != nullptr) {
        // Ak sme v listovom uzle, priradime Huffmanov kod danej hodnote.
        if (node->left == nullptr && node->right == nullptr) {
            
            codes[node->data] = code;
        }

        // Rekurzivne prechadzame lavym potomkom s pridanim '0' do kodu.
        code.push_back('1');
        buildHuffmanCodes(node->left, code, codes);
        code.pop_back();

        // Rekurzivne prechadzame pravym potomkom s pridanim '1' do kodu.
        code.push_back('0');
        buildHuffmanCodes(node->right, code, codes);
        code.pop_back();
    }
    /* Debug print statement
    cout << "Constructed Huffman Codes:" << endl;
    for (const auto& pair : codes) {
        cout << "Character: " << pair.first << ", Code: " << pair.second << endl;
    }*/
}

//! Metoda pre ziskanie korena Huffmanovho stromu.
HuffmanNode* HuffmanTree::getRoot() {
    return root;
}
//! Metoda na vypis struktury stromu do suboru.
void HuffmanNode::printNode(int indent) {
    if (right != nullptr) {
        right->printNode(indent + 4);
    }
    cout << setw(indent) << " \\ " << data << "(" << data << ")" << endl;
    if (left != nullptr) {
        left->printNode(indent + 4);
    }
}
//! Verejna metoda pre zostrojenie Huffmanovych kodov rekurzivnym prechodom stromu na zaklade frequencii po compressi.
void HuffmanTree::buildTreeFromFrequencies(const map<char, string>& frequencies) {
     
    this->root = new HuffmanNode();
    HuffmanNode* current = this->root;
    int counter;

    for (const auto& pair : frequencies) {
        counter = pair.second.length();
        current = this->root;
        for (char c : pair.second) {
            
            if (c == '0')
            {
                if (current->left==nullptr)
                {
                    HuffmanNode* nov = new HuffmanNode();
                    current->left = nov;

                }
                current = current->left;
                counter--;
            }
            else
            {
                if (current->right==nullptr)
                {
                    HuffmanNode* nov = new HuffmanNode();
                    current->right = nov;
                }
                current = current->right;
                counter--;
            }
            if (counter == 0)// jsem na konci
            {
                current->data = pair.first;
                
                current->frequency = NULL;
                current->left = nullptr;
                current->right = nullptr;
            }
        }
    }
}