#include <iostream>
#include <string>
#include <fstream>
#include<sstream>
#include <queue>
#include<algorithm>
using namespace std;

// compare 2 string numberic
bool cpm_stringId(string a, string b){
    size_t pos_a = a.find("\t");
    size_t pos_b = b.find("\t");
    string tok_a = a.substr(0, pos_a);
    string tok_b = b.substr(0, pos_b);
    if(tok_a.length() != tok_b.length()){
        return tok_a.length() < tok_b.length();
    }else{
        int flag = true;
        for(int i=0; i<tok_a.length(); i++){
            int ac = atoi(tok_a.substr(i,1).c_str());
            int bc = atoi(tok_b.substr(i,1).c_str());
            if(ac != bc){
                return ac < bc;
            }
        }
        return true;
    }
}

class Compare
{
public:
    //Ascending order sort
    bool operator() (pair<string, int> pair1, pair<string, int> pair2)
    {
        return cpm_stringId(pair2.first, pair1.first);
    }
};

string ToString(int val) {
    stringstream stream;
    stream << val;
    return stream.str();
}

//merge all sorted files into output file
string mergeFiles(int counter) {

    std::priority_queue<pair<string, int>, std::vector<pair<string, int> >, Compare> minHeap;
    ifstream* handles = new ifstream[counter];

    // get smallest element in each file
    for (int i = 1; i <= counter; i++) {
        string sortedInputFileName = "output" + ToString(i) + ".csv";
        handles[i - 1].open(sortedInputFileName.c_str());
        string firstValue;
        getline(handles[i - 1], firstValue);
        minHeap.push(pair<string, int>(firstValue, i - 1));   //second value in pair keeps track of the file from which the number was drawn
    }

    string outputFileName = "output.csv";
    ofstream outputFile(outputFileName.c_str());

    // merge all file
    while (minHeap.size() > 0) {
        pair<string, int> minPair = minHeap.top();
        minHeap.pop();
        outputFile << minPair.first << '\n';
        string nextValue;
        flush(outputFile);
        if (getline(handles[minPair.second], nextValue)) {
            minHeap.push(pair <string, int>(nextValue, minPair.second));
        }
    }

    //clean up
    for (int i = 1; i <= counter; i++) {
        string InputFileName = "output" + ToString(i) + ".csv";
        remove(InputFileName.c_str());
        handles[i - 1].close();
    }
    outputFile.close();
    delete[] handles;//free memory

    return outputFileName;
}

// sort and write to subfile
void sortAndWrite(string *values, int size, int numberOfChunks) {
    sort(values, values + size, cpm_stringId);
    string outputFileName = "output" + ToString(numberOfChunks) + ".csv";
    ofstream outputFile(outputFileName.c_str()); //output file
    for (int i = 0; i < size; i++) {
        outputFile << values[i] << '\n';
    }
    outputFile.close();
}

int main() {
    //divide file into chunks of size that fits in your memory
    int numberOfChunks = 1;
    // Number of element in chuck
    int chunkSize = 250;
    string* inputValues = new string[chunkSize];
    string readValue;
    int currentCount = 0;
    bool unprocessedData = true;
    ifstream inputFile("./hash_catid_count.csv");

    while (getline(inputFile, readValue)) {
        unprocessedData = true;
        inputValues[currentCount++] = readValue;
        if (currentCount == chunkSize) {
//            write and sort to subfile
            sortAndWrite(inputValues, currentCount, numberOfChunks);
            numberOfChunks++;
            currentCount = 0;
            unprocessedData = false;
        }
    }
    if (unprocessedData) {
        sortAndWrite(inputValues, currentCount, numberOfChunks);
    }
    else {
        numberOfChunks--;
    }

    inputFile.close();
    delete[] inputValues; //free memory
    if (numberOfChunks != 0) {
        cout << "output is in file : " << mergeFiles(numberOfChunks);
    }

    return 0;
}