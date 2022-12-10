#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
bool comparepair(pair<vector<int>, int> A, pair<vector<int>, int> B) {
    return ((A.second) > (B.second));
}
void quiz221201() {
    ifstream openFile("221201.txt");
    string line;
    int buf;
    int deer_count = 0;
    vector<pair<vector<int>, int> > note;
    if (openFile.is_open()) {
        note.push_back({{},0});
        while (getline(openFile, line)){
            if (line != "") {
                buf = stoi(line);
                note[deer_count].first.push_back(buf);
                note[deer_count].second += buf;
            } else {
                ++deer_count;
                note.push_back({{},0});
            }
        }
        openFile.close();
    }

    int max = 0;
    for (int i = 0; i < note.size(); i++) {
        if (max < note[i].second) max = note[i].second;
    }
    cout << "Max Calories: " << max << endl;

    sort(note.begin(), note.end(), comparepair);
    cout << "Top three Calories: " << note[0].second << ", " << note[1].second << ", " << note[2].second << "\n";
    cout << "Sum of them: " << note[0].second + note[1].second + note[2].second << "\n";
}
void quiz221202() {
    ifstream openFile("221202.txt");
    string line;
    int count = 0;
    int totalscore = 0;
    if (openFile.is_open()) {
        while (getline(openFile, line)){
            uint8_t oppo = line[0]-'A'+1, strategy = line[2];
            uint8_t me;
            if (strategy == 'Y') me = oppo;
            else if (strategy == 'X') {
                me = oppo - 1;
                if (me == 0) me = 3;
            } else {
                me = oppo + 1;
                if (me == 4) me = 1;
            }
            count++;
            if (me == oppo) totalscore += me + 3;
            else if (me == 1) {
                if (oppo == 2) totalscore += me + 0;
                else totalscore += me + 6;
            } else if (me == 2) {
                if (oppo == 1) totalscore += me + 6;
                else totalscore += me + 0;
            } else {
                if (oppo == 1) totalscore += me + 0;
                else totalscore += me + 6;
            }
        }
        openFile.close();
    }
    cout << "Total " << count << " matches, total score: " << totalscore << endl;
}
int prior(char letter) {
    if (letter <= 'Z') return letter-'A'+27;
    else return letter-'a'+1;
}
void quiz221203A() {
    ifstream openFile("221203.txt");
    string line, compartmentA, compartmentB;
    int count = 0, answer = 0, i;
    size_t found;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            count++;
            compartmentA = line.substr(0, line.size()/2);
            compartmentB = line.substr(line.size()/2);
            found = compartmentA.find_first_of(compartmentB);
            answer += prior(compartmentA[found]);
        }
        openFile.close();
    }
    cout << "Total " << count << " rucksacks, total item score: " << answer << endl;
}
void quiz221203B() {
    ifstream openFile("221203.txt");
    string line, group[3];
    int count = 0, answer = 0, i;
    int groupcount = 0;
    size_t found;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            group[groupcount] = line;
            count++;
            if (++groupcount == 3) {
                groupcount = 0;
                found = group[0].find_first_of(group[1]);
                while (group[2].find_first_of(group[0][found])==string::npos) found = group[0].find_first_of(group[1], found+1);
                answer += prior(group[0][found]);
            }
        }
        openFile.close();
    }
    cout << "Total " << count << " rucksacks, total item score: " << answer << endl;
}
void quiz221204A() {
    ifstream openFile("221204.txt");
    string line;
    int count = 0, answer = 0, pos;
    int Xbegin, Xend, Ybegin, Yend;
    bool containment;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            ++count;
            containment = false;
            pos = line.find_first_of('-');
            Xbegin = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            pos = line.find_first_of(',');
            Xend = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            pos = line.find_first_of('-');
            Ybegin = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            Yend = stoi(line);
            if (Xbegin == Ybegin) containment = true;
            else if (Xend == Yend) containment = true;
            else if (Xbegin < Ybegin) { if (Xend > Yend) containment = true; }
            else if (Xbegin > Ybegin) { if (Xend < Yend) containment = true; }
            if (containment == true) { ++answer; }
        }
        openFile.close();
    }
    cout << "Total " << count << " assignments, total containment pairs: " << answer << endl;
}void quiz221204B() {
    ifstream openFile("221204.txt");
    string line;
    int count = 0, answer = 0, pos;
    int Xbegin, Xend, Ybegin, Yend;
    bool overlap;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            ++count;
            overlap = true;
            pos = line.find_first_of('-');
            Xbegin = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            pos = line.find_first_of(',');
            Xend = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            pos = line.find_first_of('-');
            Ybegin = stoi(line.substr(0,pos));
            line = line.substr(pos+1);
            Yend = stoi(line);
            if (Xbegin > Yend) overlap = false;
            else if (Ybegin > Xend) overlap = false;
            if (overlap == true) { ++answer; }
        }
        openFile.close();
    }
    cout << "Total " << count << " assignments, total containment pairs: " << answer << endl;
}
int main() {
    quiz221204B();
}
