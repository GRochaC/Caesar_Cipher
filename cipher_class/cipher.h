#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Cipher {
    private:
        static pair<vector<string>, string> cryptography(string& path);
    public:
        static void encrypt_file(string& path);
        static void decrypt_file(string& path);
};