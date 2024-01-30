#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <set>
#include "cipher_class/cipher.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    std::cout << "Welcome!" << '\n';

    while(true) {  
        std::cout << "Choose an operation: \n\t1- Encrypt a file \n\t2- Decrypt a file\n\t0- Exit\n";
        string op_; cin >> op_; 
        cin.ignore();

        try {
            
            int op = stoi(op_);
            if(op < 0 or op > 2) throw 505;
            
            ifstream file; string path; bool fail;
            do {
                std::cout << "File path: ";
                getline(cin, path);
                file.open(path);
                fail = file.fail();

                if(fail) std::cout << "Error: No such file or path" << '\n';

            } while(fail);
            file.close();

            switch(op) {
                // Encryption
                case 1:
                    Cipher::encrypt_file(path);
                    std::cout << "Encryption completed successfully." << '\n';
                    break;

                // Decryption
                case 2:
                    Cipher::decrypt_file(path);
                    std::cout << "Decryption completed successfully." << '\n';
                    break;
            }

            // exit
            if(op == 0) break;

            string again = "";
            set<string> awnsers = {"Y","y","n","N"};
            while(not awnsers.count(again)) {
                std::cout << '\n' << "Would you like to encrypt or decrypt another file? (Y/n) ";
                cin >> again;
            }

            // exit
            if(again == "n" or again == "N") break;
            std::cout << '\n';

        } catch(const invalid_argument& e) {
            cerr << "Error: Invalid argument." << '\n';
        } catch(int error) {
            cerr << "Error: Invalid operation." << '\n';
        }
        
    }

    std::cout << "Good bye." << '\n';

    return 0;
}