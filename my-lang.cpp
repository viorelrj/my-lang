#include "core.h"
#include "token.h";

#include <iostream>
#include <fstream>

string fileReader(string fileName) {
    ifstream inputFile;
    string temp;
    string text;

    inputFile.open(fileName);
    if (!inputFile.is_open()) return "";

    while (!inputFile.eof()) {
        inputFile >> temp;
        text.append(temp + " ");
    } 

    inputFile.close();

    return text;
}



int main() {
    string text = fileReader("test.txt");
    wordSpitter(text);
}
