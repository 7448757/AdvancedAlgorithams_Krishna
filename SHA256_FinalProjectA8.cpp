#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include<cstdint>
#include <bitset>
#include <cstring>
#include <fstream>

using namespace std;

string sha256(const string& input) {
    // Constants for SHA-256
    //Initialising an array for first 32bits of fractional parts of the cube roots of first 64 prime numbers
    const uint32_t k[] = {                             //uint32_t is 32 bit unsigned intiger
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    // Initial hash values
    //first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    // Pre-processing
    //Here we are converting each character to binary which is 8 bits
    string binaryInput = "";
    for (char c : input) {
        bitset<8> binaryChar(c);
        binaryInput += binaryChar.to_string();
    }

    // Append the bit '1' to the message.Here we are appending 1 to the message
    binaryInput += "1";

    // Append 0s to the end of the message until the length is 448 mod 512.padding step ensures that the final block.
    //which will have a length that is a multiple of 512 bits
    while (binaryInput.length() % 512 != 448) {
        binaryInput += "0";
    }

    // Append original length in bits modulo 2^64 to the end of the message
    uint64_t originalLength = input.length() * 8;
    bitset<64> lengthBits(originalLength);
    binaryInput += lengthBits.to_string();

    // Process the message in 512-bit chunks
    for (size_t chunkStart = 0; chunkStart < binaryInput.length(); chunkStart += 512) {
        bitset<512> chunk(binaryInput.substr(chunkStart, 512));

        // Break the chunk into sixteen 32-bit words
        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = bitset<32>(chunk.to_string().substr(i * 32, 32)).to_ulong();
        }

        // Extend the sixteen 32-bit words into sixty-four 32-bit words
        for (int i = 16; i < 64; ++i) {
            uint32_t s0 = (w[i - 15] >> 7 | (w[i - 15] << 25)) ^ (w[i - 15] >> 18 | (w[i - 15] << 14)) ^ (w[i - 15] >> 3);
            uint32_t s1 = (w[i - 2] >> 17 | (w[i - 2] << 15)) ^ (w[i - 2] >> 19 | (w[i - 2] << 13)) ^ (w[i - 2] >> 10);

            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        // Initialize working variables to current hash value
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        // Compression function main loop
        for (int i = 0; i < 64; ++i) {  
            uint32_t s1 = (e >> 6 | (e << 26)) ^ (e >> 11 | (e << 21)) ^ (e >> 25 | (e << 7));
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + s1 + ch + k[i] + w[i];
            uint32_t s0 = (a >> 2 | (a << 30)) ^ (a >> 13 | (a << 19)) ^ (a >> 22 | (a << 10));
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = s0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Add the compressed chunk to the current hash value
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    // Final hash value
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << h0
       << hex << setw(8) << setfill('0') << h1
       << hex << setw(8) << setfill('0') << h2
       << hex << setw(8) << setfill('0') << h3
       << hex << setw(8) << setfill('0') << h4
       << hex << setw(8) << setfill('0') << h5
       << hex << setw(8) << setfill('0') << h6
       << hex << setw(8) << setfill('0') << h7;

    return ss.str();
}
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    // Specify the file path
    string filename = "mark.txt";

    // Read content from the file
    string input = readFile(filename);
    if (input.empty()) {
        cout<<"empty file";
        return 1; // Exit with an error code
    }

    // Calculate SHA-256 hash
    string hash = sha256(input);

    cout << "Input from file '" << filename << "':\n" << input << endl;
    cout << "SHA-256 Hash: " << hash << endl;

    return 0;
}