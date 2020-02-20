#include "token.h";

#include <iostream>
#include <fstream>

string fileReader(string fileName) {
    ifstream inputFile;
    string temp;
    string text;

    inputFile.open(fileName);
    if (!inputFile.is_open()) return "";

    for (;;) {
        inputFile >> temp;
        if (inputFile.fail()) break;
        text.append(temp + " ");
    }

    inputFile.close();

    return text;
}



int main() {
    string sourceCode = fileReader("test.txt");
    tokenizer(sourceCode);
}
