#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "cipher.h"

using namespace std;

pair<vector<string>, string> Cipher::cryptography(string& path) {
    string line;

    int key;
    do {
        cout << "Please provide the encryption key [-26, 26] (key < 0 for left shift and key > 0 for right shift): "; 
        cin >> key;
    } while (key < -26 or key > 26);

    ifstream file(path);
    vector<string> lines;

    // Lambda function responsible for character shifting
    auto shifting = [key](string& line) {
        for(char& c : line) {
            // upper case
            if((int) c >= 65 and (int) c <= 90) {
                int pos = c - 65;
                // deals with modulus of negative numbers
                c = ((((pos + key) % 26) + 26) % 26) + 65;
            }

            // lower case
            else if((int) c >= 97 and (int) c <= 122) {
                int pos = c - 97;
                // deals with modulus of negative numbers
                c = ((((pos + key) % 26) + 26) % 26) + 97;
            }
        }

        // returns the coded/decoded line
        return line;
    };

    while(getline(file, line)) {
        lines.push_back(shifting(line) + "\n");
    }

    string original_file_name = "", file_name = "";
    for(int i = path.size()-1; path[i] != '\\' and i >= 0; i--) original_file_name += path[i];
    reverse(original_file_name.begin(), original_file_name.end());
    for(int i = 0; original_file_name[i] != '.'; i++) file_name += original_file_name[i];
    file_name = shifting(file_name) + ".txt";

    // returns the tuple: {encoded/decoded lines, encoded/decoded file name}
    return {lines, file_name};
}

void Cipher::encrypt_file(string& path) {
    auto [lines, file_name] = Cipher::cryptography(path);

    ofstream encrypted_file("encrypted_files\\" + file_name);
    for(string line : lines) {
        encrypted_file << line;
    }

    encrypted_file.close();
}

void Cipher::decrypt_file(string& path) {
    auto [lines, file_name] = Cipher::cryptography(path);

    ofstream decrypted_file("decrypted_files\\" + file_name);
    for(string line : lines) {
        decrypted_file << line;
    }

    decrypted_file.close();
}