#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdint>

// Node used by the Huffman tree.
// We use unsigned char to represent raw bytes (0..255) and uint64_t for frequencies.
struct HuffmanNode {
    unsigned char ch;     // valid for leaves
    uint64_t freq;        // frequency/count
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(unsigned char c = 0, uint64_t f = 0){
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
    HuffmanNode(HuffmanNode* l, HuffmanNode* r){
        ch = 0;
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }
        // : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
    bool isLeaf(){
        return left == nullptr && right == nullptr; 
    }
};

class Compressor {
public:
    // Compress inputFile into outputFile. Returns true on success.
    // - inputFile: path to file to compress (read as raw bytes)
    // - outputFile: path to write compressed format (binary)
    bool compressFile(const string &inputFile, const string &outputFile);

private:
    // Private helpers implemented in compressor.cpp:
    // - buildHuffmanTree: construct tree from frequency map
    // - buildCodes: traverse tree to produce bitstring codes for each symbol
    // - serializeTree: write tree to an output stream so decompressor can reconstruct it
    // - freeTree: recursive destructor for tree nodes
    HuffmanNode* buildHuffmanTree(const unordered_map<unsigned char, uint64_t> &freqMap);
    void buildCodes(HuffmanNode* node, string &path, unordered_map<unsigned char, string> &codes);
    void serializeTree(HuffmanNode* root, ostream &out);
    void freeTree(HuffmanNode* root);
};
