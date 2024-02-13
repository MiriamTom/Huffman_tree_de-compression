Huffman Compression and Decompression

This repository contains C++ code for Huffman compression and decompression algorithms. Huffman coding is a widely used algorithm for lossless data compression. It assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters.

Features:
Compression: Convert a file into a compressed binary format using Huffman coding.
Decompression: Decompress a Huffman-encoded file back into its original format.
Tree Visualization: Print the Huffman tree structure to visualize how characters are encoded.
Error Handling: Detect and handle errors such as file input/output failures.
File Structure:
Huffman.h and Huffman.cpp: Implementations of the Huffman encoding algorithm, including Huffman tree construction and encoding/decoding methods.
Decompression.h and Decompression.cpp: Decompression class for restoring the original file from a Huffman-encoded binary file.
Compression.h and Compression.cpp: Compression class for encoding a file using Huffman coding.
main.cpp: Main program to demonstrate compression and decompression functionalities.
example.txt: Example input file used for testing compression and decompression.
compressed.bin: Binary file generated after compression.
decompressed.txt: Text file generated after decompression.
Usage:
Compile the program using a C++ compiler (e.g., g++).
Run the compiled executable with appropriate command-line arguments to compress or decompress files.
Follow the prompts to provide input/output file names and select compression or decompression mode.
How to Run:
Compression:
bash
Copy code
./huffman -c input.txt compressed.bin
Decompression:
bash
Copy code
./huffman -d compressed.bin decompressed.txt
Contributors:
Miriam Tomášová
