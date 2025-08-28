#include <iostream>
#include <string>
#include <limits>

#include "compressor.h"
#include "decompressor.h"

using namespace std;

#include <fstream>

static bool fileExists(const std::string &path) {
    ifstream f(path);
    return f.is_open();
}

static string promptPathLine(const string &prompt) {
    cout << prompt;
    string line;
    // read a whole line (supports spaces in filenames)
    getline(cin, line);
    return line;
}

int main(int argc, char** argv){
    Compressor compressor;
    Decompressor decompressor;

    while (true) {
        cout<<endl<<"Huffman Coding (simple)"<<endl<<"1. Compress a file"<<endl<<"2. Decompress a file"<<endl<<"3. Exit"<<endl<<"Choose: ";
        int choice;
        if (!(cin >> choice)) break;
        
        if (choice == 1) {
            string inF = promptPathLine("Input file: ");
            if (!fileExists(inF)) {
                cout << "Input file does not exist: " << inF << "\n";
                continue;
            }

            string outF = promptPathLine("Output file: ");

            if (fileExists(outF)) {
                cout << "Output file already exists. Overwrite? (y/n): ";
                char resp;
                cin>>resp;
                if (resp != 'y' && resp != 'Y') {
                    cout << "Aborted by user."<<endl;
                    continue;
                }
                else if(resp!='n' && resp!='N'){
                    cout<<"Invalid Choice. Exiting"<<endl;
                    continue;
                }
            }
            
            bool ok = compressor.compressFile(inF, outF);
            cout << (ok ? "Compressed -> " + outF + "\n" : "Compression failed.\n");
        } 
        
        else if (choice == 2) {
            string inF = promptPathLine("Compressed file: ");
            if (!fileExists(inF)) {
                cout << "Compressed file does not exist: " << inF << "\n";
                continue;
            }
            string outF = promptPathLine("Output file: ");

            if (fileExists(outF)) {
                cout << "Output file already exists. Overwrite? (y/n): ";
                char resp;
                cin>>resp;
                if (resp != 'y' && resp != 'Y') {
                    cout << "Aborted by user."<<endl;
                    continue;
                }
                else if(resp!='n' && resp!='N'){
                    cout<<"Invalid Choice. Exiting"<<endl;
                    continue;
                }
            }

            bool ok = decompressor.decompressFile(inF, outF);
            cout << (ok ? "Decompressed -> " + outF + "\n" : "Decompression failed.\n");
        } 
        
        else if (choice == 3) {
            break;
        } 
        
        else {
            cout << "Invalid choice."<<endl;
        }
    }
    
    return 0;
}