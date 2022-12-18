#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

const vector<char> MODS = {'+', '-', '*'};
const char SEPARATOR = ',';
const char DICE_SEPARATOR = 'd';

bool isModifier(char c, vector<char> mods = MODS) {
    bool isMod = false;
    for (int i = 0; i < mods.size(); i++) {
        if (mods[i] == c) {
            isMod = true;
        }
    }

    return isMod;
}

int useOperator(int firstElem, string s, vector<char> mods = MODS) {
    int res, secondElem;
    string newLine;

    for (int i = 1; i < s.size(); ++i) {
        newLine += s[i];
    }

    secondElem = stoi(newLine);

    switch (s[0])
    {
        case '+':
            res = firstElem + secondElem;
            break;
        case '-':
            res = firstElem - secondElem;
            break;
        case '*':
            res = firstElem * secondElem;
            break;
    }

    return res;
}

vector<string> split(string s, char separator = SEPARATOR) {
    vector<string> splitDices;
    string tempDice = "";

    for(int i = 0; i < s.size(); i++) {
        if (isModifier(s[i])){
            if (tempDice != "") {
                splitDices.push_back(tempDice);
                tempDice = "";
            }
        }
        if (s[i] != separator && s[i] != ' ') {
            tempDice += s[i];
        }
        if (i == (s.size() - 1) || s[i] == separator) {
            splitDices.push_back(tempDice);
            tempDice = "";
        }
    }

    return splitDices;
}

int randGen(int from = 1, int to = 100)  {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dis(from, to);

    return dis(gen);
}

int dice(string input, char separator_ = SEPARATOR) {
    vector<string> outputDices;
    int result = 0;

    outputDices = split(input, separator_);

    for (int i = 0; i < outputDices.size(); i++) {
        if (!isModifier(outputDices[i][0])) {
            auto playDice = split(outputDices[i], DICE_SEPARATOR);
            int dicesCount = stoi(playDice[0]);
            int diceWeight = stoi(playDice[1]);

            for (int j = 0; j < dicesCount; ++j) {
                int ran = randGen(1, diceWeight);
                //cout << ran << endl;
                result += ran;
            }

        }
    }

    for (int i = 0; i < outputDices.size(); i++) {
        if (isModifier(outputDices[i][0])) {
            result = useOperator(result, outputDices[i]);
        }
    }

    return result;
}


int main() {
//    cout << dice("2d6+2,3d10") << endl;

    string diceProb = "3d10";
    int dicesCount = 10000;
    int variantCount = 30;
    vector<int> throwsCount(variantCount);
    ofstream f("probability.txt");

    for (int i = 0; i < throwsCount.size(); ++i) {
        throwsCount[i] = 0;
    }

    for (int i = 0; i < dicesCount; ++i) {
        int throw_ = dice(diceProb);
        throwsCount[throw_ - 1]++;
    }

    for (int i = 0; i < throwsCount.size(); ++i) {
//        f << i + 1 << " ; " << throwsCount[i] << endl;
        f << throwsCount[i] << endl;
    }

    return 0;
}
