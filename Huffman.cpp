#include "Huffman.h"

const int MAX_SIZE = 100;

void Huffman::runHuffman() {
    string mode;
    cin >> mode;

    while (mode != "exit") {
        if (mode == "-c") {
            doCompress();
        }

        if (mode == "-d") {
            doDecompress();
        }
        cin >> mode;
    }
}

void Huffman::doCompress() {
    cout << "Program works in compress mode" << endl;
    string file;
    cin >> file;

    string inFile;
    string outFile;

    if (file == "-i") {
        cin >> inFile; //.txt
    }
    cin >> file;

    if (file == "-o") {
        cin >> outFile;
    }
    
    getStringFromFile(inFile, inputString);

    countChar();

    createTree();
    runMakeAlphabet();

    string compressed;
    compressed = constructCompressed();

    writeToFile(outFile, compressed);
    levelOfCompression(compressed);
    runDebugMode(compressed);
}

void Huffman::doDecompress() {
    cout << "Program works in decompress mode" << endl;
    string file;
    cin >> file;

    string inFile;
    string outFile;

    if (file == "-i") {
        cin >> inFile; //.txt
    }
    cin >> file;

    if (file == "-o") {
        cin >> outFile;
    }

    string getCompressed;
    getStringFromFile(inFile, getCompressed);

    string decompressed;
    decompressed = decompress(getCompressed);

    writeToFile(outFile, decompressed);
}

void Huffman::createTree() { 
    while (list.size() != 1) {
        BinaryTreeNode* left = list.getSmallestFreqData()->data;
        int firstPosition = list.getPosition(left);
        list.removeElementAtPosition(firstPosition);

        BinaryTreeNode* right = list.getSmallestFreqData()->data;
        int secondPosition = list.getPosition(right);
        list.removeElementAtPosition(secondPosition);

        BinaryTreeNode* node = new BinaryTreeNode('$', left->freq + right->freq);
        if (firstPosition <= secondPosition) {
            node->left = left;
            node->right = right;
        }
        else {
            node->left = right;
            node->right = left;
        }
        
        if (firstPosition > list.size()) {
            list.addElement(node);
        }
        else {
            list.addElementAtPosition(firstPosition, node);
        }
        this->root = node;
    }
}

void Huffman::runMakeAlphabet() {
    int arr[MAX_SIZE], index = 0;
    makeAlphabet(this->root, arr, index);
}

void Huffman::makeAlphabet(BinaryTreeNode* root, int arr[], int index) {
    if (root->left) {
        arr[index] = 0;
        makeAlphabet(root->left, arr, index + 1);
    }
    
    if (root->right) {
        arr[index] = 1;
        makeAlphabet(root->right, arr, index + 1);
    }
    
    if (!root->left && !root->right) {
        //std::cout << root->symb << " ";
        string code;
        for (int i = 0; i < index; i++) {
            //std::cout << arr[i];
            code += std::to_string(arr[i]);
        }
        m.emplace(root->symb, code);
        //std::cout << std::endl;
    }
}

void Huffman::countChar() {
    map<char, int> count;
    int l = this->inputString.size();
    for (int i = 0; i < l; i++) {
        count[this->inputString[i]]++;
    }
    
    for (const auto it : count) {
        list.addElement(new BinaryTreeNode(it.first, it.second));
    }
}

string Huffman::constructCompressed() {
    string compressed;
    char symbol;
    int sz = this->inputString.size();
    for (int i = 0; i < sz; i++) {
        symbol = this->inputString[i];
        //cout << this->inputString[i] << endl;
        for (const auto it : m) {
            if (symbol == it.first) {
                compressed += it.second;
            }
        }
    }
    return compressed;
}

void Huffman::getStringFromFile(string fileName, string& input) {
    ifstream inputFile;
    inputFile.open(fileName);

    if (!inputFile.is_open()) {
        cout << "cannot open file" << endl;
        throw std::runtime_error("Can not read from file");
    }

    getline(inputFile, input);
    inputFile.close();
}

void Huffman::writeToFile(string fileName, string& output) {
    ofstream outputFile;
    outputFile.open(fileName, ios::out | ios::trunc /*ios::app*/);

    if (outputFile.fail()) {
        cout << "Error opening file" << endl;
        throw std::runtime_error("Can not write to file");
    }
    outputFile << output;
    outputFile.close();
}

void Huffman::levelOfCompression(string compressed) {
    double first = (double)this->inputString.size() * 8;
    double second = compressed.size();
    double result = 100 - ((first - second) / first * 100);

    cout << "Original size: " << first << " bits" << endl;
    cout << "Compressed size: " << second << " bits" << endl;

    cout << "About " << std::fixed << std::setprecision(0) << result << '%' << " of the original size" << endl;
}

void Huffman::runDebugMode(string compressed) {
    cout << "Debug mode: ";
    string divideCompressed;
    int sz = compressed.size();
    int j = 0;
    for (int i = 0; i < sz; i++) {
        divideCompressed += compressed[i];
        j++;

        if (j == 8) {
            cout << debugMode(divideCompressed) << " ";
            divideCompressed = "";
            j = 0;
        }
    }
    if (!divideCompressed.empty()) {
        cout << debugMode(divideCompressed) << endl;
    }
}

int Huffman::debugMode(string compressed) {
    int decimalNumber = 0, base = 1, remainder;
    int sz = compressed.size();
    for (int i = sz - 1; i >= 0; i--) {
        remainder = compressed[i] - '0';
        decimalNumber += remainder * base;
        base *= 2;
    }
    return decimalNumber;
}

string Huffman::decompress(string compressed) {
    string decompressed;
    BinaryTreeNode* curr = this->root;
    int sz = compressed.size();
    for (int i = 0; i < sz; i++) {
        if (compressed[i] == '0') {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
        
        if (!curr->left && !curr->right) {
            decompressed += curr->symb;
            curr = this->root;
        }
    }
    return decompressed;
}
