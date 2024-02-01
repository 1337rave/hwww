#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string cleanWord(const string& word) {
    string cleanedWord;
    for (char c : word) {
        if (isalpha(c))
            cleanedWord += tolower(c);
    }
    return cleanedWord;
}

int main() {
    ifstream inputFile;
    ofstream outputFile;
    string inputFileName, outputFileName;

    map<string, int> wordFrequency;

    int choice;
    do {
        cout << "Menu:\n"
            << "1. Read input text from file\n"
            << "2. Display information about all words\n"
            << "3. Display information about the most common word\n"
            << "4. Write results to a file\n"
            << "5. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the input file name: ";
            cin >> inputFileName;
            inputFile.open(inputFileName);
            if (!inputFile.is_open()) {
                cerr << "Unable to open input file!" << endl;
                return 1;
            }
            string word;
            while (inputFile >> word) {
                string cleanedWord = cleanWord(word);
                if (!cleanedWord.empty())
                    wordFrequency[cleanedWord]++;
            }
            cout << "Text read successfully." << endl;
            inputFile.close();
        }
        else if (choice == 2) {
            for (const auto& pair : wordFrequency) {
                cout << pair.first << ": " << pair.second << endl;
            }
        }
        else if (choice == 3) {
            auto mostCommonWord = max_element(wordFrequency.begin(), wordFrequency.end(),
                [](const pair<string, int>& a, const pair<string, int>& b) {
                    return a.second < b.second;
                });
            cout << "Most common word: " << mostCommonWord->first << " (" << mostCommonWord->second << " times)" << endl;
        }
        else if (choice == 4) {
            cout << "Enter the output file name: ";
            cin >> outputFileName;
            outputFile.open(outputFileName);
            if (!outputFile.is_open()) {
                cerr << "Unable to open output file!" << endl;
                return 1;
            }
            for (const auto& pair : wordFrequency) {
                outputFile << pair.first << ": " << pair.second << endl;
            }
            cout << "Results written to file." << endl;
            outputFile.close();
        }
        else if (choice == 5) {
            cout << "Exiting program." << endl;
        }
        else {
            cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    } while (choice != 5);

    return 0;
}
