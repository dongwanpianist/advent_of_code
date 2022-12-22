#include <iostream>
#include <fstream>
#include <sstream>
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
typedef struct {
    int quantity;
    int from;
    int to;
} instruction221205A;
instruction221205A split221205A(string str, const char delim = ' ') {
    instruction221205A result;
    vector<string> splitted;
    stringstream ss(str);
    string tmp;
    while (getline(ss, tmp, delim)) splitted.push_back(tmp);
    result.quantity = stoi(splitted[1]);
    result.from = stoi(splitted[3]);
    result.to = stoi(splitted[5]);
    return result;
}
void quiz221205A() {
    ifstream openFile("221205.txt");
    vector<char> stack[10]; // 귀찮아서 그냥 줄줄 입력
    vector<instruction221205A> instruction;
    stack[1] = {'B', 'L', 'D', 'T', 'W', 'C', 'F', 'M'};
    stack[2] = {'N', 'B', 'L'};
    stack[3] = {'J', 'C', 'H', 'T', 'L', 'V'};
    stack[4] = {'S', 'P', 'J', 'W'};
    stack[5] = {'Z', 'S', 'C', 'F', 'T', 'L', 'R'};
    stack[6] = {'W', 'D', 'G', 'B', 'H', 'N', 'Z'};
    stack[7] = {'F', 'M', 'S', 'P', 'V', 'G', 'C', 'N'};
    stack[8] = {'W', 'Q', 'R', 'J', 'F', 'V', 'C', 'Z'};
    stack[9] = {'R', 'P', 'M', 'L', 'H'};
    string line;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            if (line[0] == 'm') {
                instruction.push_back(split221205A(line));
            }
        }
    }
    vector<char> tempstack;
    for (int i = 0; i < instruction.size(); i++) {
        // quiz A:
        //for (int numcrate = 0; numcrate < instruction[i].quantity; numcrate++) {
        //    stack[instruction[i].to].push_back(stack[instruction[i].from].back());
        //    stack[instruction[i].from].pop_back();
        //}
        // quiz B:
        for (int numcrate = 0; numcrate < instruction[i].quantity; numcrate++) {
            tempstack.push_back(stack[instruction[i].from].back());
            stack[instruction[i].from].pop_back();
        }
        for (int numcrate = 0; numcrate < instruction[i].quantity; numcrate++) {
            stack[instruction[i].to].push_back(tempstack.back());
            tempstack.pop_back();
        }
    }
    for (int i = 1; i <= 9; i++) {
        cout << "stack[" << i << "] = \" ";
        for (char ch : stack[i]) {
            cout << ch << ' ';
        }
        cout << "\"\n";
    }
}
void quiz221206A() {
    int answer = 0;
    ifstream openFile("221206.txt");
    string line;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            cout << line << endl;
        }
    }
    bool ismarker = true;
    for (int i = 0; i <= line.size(); i++) {
        cout << "Check between [" << i << "] and [" << i+13 << "] : \"" << line.substr(i, 14) << "\"";
        for (int strfrom = 0; strfrom < 13; strfrom++) {
            for (int strto = strfrom+1; strto < 14; strto++) {
                if (line[i+strfrom] == line[i+strto]) {
                    ismarker = false;
                }
            }
        }
        cout << " / ismarker? " << (ismarker?"true\n":"false\n");
        if (ismarker) {
            answer = i + 14;
            break;
        } else ismarker = true;
    }
    cout << answer << endl;
}
vector<string> split(string str, char delim) {
    vector<string> result;
    string parsestr;
    int prevdelim = 0;
    for (int i = 0; i < str.size(); i++) if (str[i] == delim) {
        parsestr = str.substr(prevdelim, i-prevdelim);
        if (parsestr.size() != 0) result.push_back(parsestr);
        prevdelim = i + 1;
    }
    parsestr = str.substr(prevdelim);
    if (parsestr.size() != 0) result.push_back(parsestr);
    return result;
}
vector<pair<string, int> > aocdirinfo;
bool dircompare(pair<string, int> A, pair<string, int> B) {
    return (A.second < B.second);
}
struct aocfile {
    string name;
    int size;
    aocfile() {
        name = "";
        size = 0;
    }
    aocfile(string _name, int _size) {
        name = _name;
        size = _size;
    }
};
struct aocdir {
    string name;
    int depth;
    vector<aocfile> file;
    vector<aocdir*> subdir;
    aocdir* parentdir;
    int totalsize;
    int totalsize100000;
    bool calculated;
    bool calculated100000;
    aocdir() {
        name = "";
        depth = 0;
        totalsize = 0;
        calculated = false;
    }
    aocdir(string _name, aocdir* _parentdir) {
        name = _name;
        depth = _parentdir->depth + 1;
        totalsize = 0;
        calculated = false;
        parentdir = _parentdir;
    }
    ~aocdir() {
        for (int i = 0; i < subdir.size(); i++) {
            delete subdir[i];
        }
        subdir.clear();
    }
    void addfile(string _name, int _size = 0) {
        file.push_back({_name, _size});
        calculated = false;
    }
    void adddir(string _name) {
        subdir.push_back(new aocdir(_name, this));
        calculated = false;
    }
    aocdir* finddir (string _name) {
        for (int i = 0; i < subdir.size(); i++) {
            if (subdir[i]->name == _name) return subdir[i];
        }
        return NULL;
    }
    void print() {
        int i, j;
        if (name == "/") {
            cout << " dir / (root)";
            if (calculated) cout << "  " << totalsize;
            cout << "\n";
        }
        for (i = 0; i < subdir.size(); i++) {
            for (j = 0; j < depth; j++) cout << "  │ ";
            cout << "  └─ dir " << subdir[i]->name;
            if (subdir[i]->calculated) cout << "  " << subdir[i]->totalsize;
            cout << "\n";
            subdir[i]->print();
        }
        for (i = 0; i < file.size(); i++) {
            for (j = 0; j < depth; j++) cout << "  │ ";
            cout << "  └─ file " << file[i].name << "  " << file[i].size << "\n";
        }
    }
    void calculate() {
        int i;
        int _totalsize = 0;
        for (i = 0; i < subdir.size(); i++) {
            if (!subdir[i]->calculated) subdir[i]->calculate();
            _totalsize += subdir[i]->totalsize;
        }
        for (i = 0; i < file.size(); i++) {
            _totalsize += file[i].size;
        }
        calculated = true;
        totalsize = _totalsize;
        aocdirinfo.push_back({name, totalsize});
    }
};
void quiz221207B() {
    aocdir system;
    aocdir* cursor = &system;
    cursor->name = "/";
    ifstream openFile("221207.txt");
    string lineraw;
    vector<string> line;
    bool promptmode = true;
    if (openFile.is_open()) {
        while (getline(openFile, lineraw)) {
            line = split(lineraw, ' ');
            if (!promptmode) {
                if (line[0] == "$") {
                    promptmode = true;
                } else {
                    if (line[0] == "dir") cursor->adddir(line[1]);
                    else cursor->addfile(line[1], stoi(line[0]));
                }
            }
            if (promptmode) {
                if (line[1] == "cd") {
                    if (line[2] == "/") cursor = &system;
                    else if (line[2] == "..") cursor = cursor->parentdir;
                    else cursor = cursor->finddir(line[2]);
                } else if (line[1] == "ls") {
                    promptmode = false;
                }
            }
        }
    }
    cursor = &system;
    cout << "Reading is done!\nRead info:\n";
    cursor->print();
    cout << "\n==============================================================\n";
    cout << "===================== calculating....... =====================\n";
    cout << "==============================================================\n\n";
    cursor->calculate();
    cout << "After calculation, info:\n";
    cursor->print();
    cout << "\nALl directories of <= 100000:\n";
    int total100000 = 0;
    for (int i = 0; i < aocdirinfo.size(); i++) {
        if (aocdirinfo[i].second <= 100000) {
            cout << "  " << aocdirinfo[i].first << "  " << aocdirinfo[i].second << "\n";
            total100000 += aocdirinfo[i].second;
        }
    }
    cout << "Sum of <=100000 directories: " << total100000 << endl;
    ///// 221207B /////
    // So, we need delete one directory of more than 2558312 (=30000000-(70000000-42558312)) in order to reserve 30000000.
    sort(aocdirinfo.begin(), aocdirinfo.end(), dircompare);
    cout << "After sorting:\n";
    for (int i = 0; i < aocdirinfo.size(); i++) {
        cout << "  " << aocdirinfo[i].first << "  " << aocdirinfo[i].second << "\n";
    }
}
void quiz221208A() {
    vector<vector<int>> grid;
    ifstream openFile("221208.txt");
    string line;
    int Wcount, Hcount = 0;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            grid.push_back({});
            Wcount = line.size();
            for (char i : line) {
                grid[Hcount].push_back(i-'0');
            }
            Hcount++;
        }
    }
    cout << "Received map of W " << Wcount << " x H " << Hcount << " (= W " << grid[0].size() << " x H " << grid.size() << ")" << endl;
    bool visibletop[Hcount][Wcount];
    bool visiblebottom[Hcount][Wcount];
    bool visibleleft[Hcount][Wcount];
    bool visibleright[Hcount][Wcount];
    bool visible[Hcount][Wcount]; // 최종연산: 4방향 OR연산으로 한 방향에서라도 보이면 보이는겨
    int visiblelevel;
    for (int i = 0; i < Hcount; i++) {
        // visibility from left
        visiblelevel = grid[i][0];
        visibleleft[i][0] = true;
        for (int j = 1; j < Wcount; j++) { //
            if (grid[i][j] > visiblelevel) {
                visiblelevel = grid[i][j];
                visibleleft[i][j] = true;
            } else visibleleft[i][j] = false;
        }
        // visibility from right
        visiblelevel = grid[i][Wcount-1];
        visibleright[i][Wcount-1] = true;
        for (int j = Wcount-2; j >= 0; j--) {
            if (grid[i][j] > visiblelevel) {
                visiblelevel = grid[i][j];
                visibleright[i][j] = true;
            } else visibleright[i][j] = false;
        }
    }
    for (int j = 0; j < Wcount; j++) {
        // visibility from top
        visiblelevel = grid[0][j];
        visibletop[0][j] = true;
        for (int i = 1; i < Hcount; i++) { //
            if (grid[i][j] > visiblelevel) {
                visiblelevel = grid[i][j];
                visibletop[i][j] = true;
            } else visibletop[i][j] = false;
        }
        // visibility from bottom
        visiblelevel = grid[Hcount-1][j];
        visiblebottom[Hcount-1][j] = true;
        for (int i = Hcount-2; i >= 0; i--) {
            if (grid[i][j] > visiblelevel) {
                visiblelevel = grid[i][j];
                visiblebottom[i][j] = true;
            } else visiblebottom[i][j] = false;
        }
    }
    int visiblecount = 0;
    cout << "After calculation, map of visibility:\n"; // print and calculate at once
    for (int i = 0; i < Hcount; i++) {
        for (int j = 0; j < Wcount; j++) {
            visible[i][j] = (visibletop[i][j] || visiblebottom[i][j] || visibleleft[i][j] || visibleright[i][j]);
            if (visible[i][j]) {
                ++visiblecount;
                cout << "\033[1;32m" << (int)grid[i][j] << "\033[0m";
            } else {
                cout << (int)grid[i][j];
            }
        }
        cout << "\n";
    }
    cout << "Total visible spots: " << visiblecount << endl;
}
void quiz221208B() {
    vector<vector<int>> grid;
    ifstream openFile("221208.txt");
    string line;
    int Wcount, Hcount = 0;
    if (openFile.is_open()) {
        while (getline(openFile, line)) {
            grid.push_back({});
            Wcount = line.size();
            for (char i : line) {
                grid[Hcount].push_back(i-'0');
            }
            Hcount++;
        }
    }
    cout << "\nReceived map of W " << Wcount << " x H " << Hcount << " (= W " << grid[0].size() << " x H " << grid.size() << ")" << endl;
    int viewtop[Hcount][Wcount];
    int viewbottom[Hcount][Wcount];
    int viewleft[Hcount][Wcount];
    int viewright[Hcount][Wcount];
    int view[Hcount][Wcount]; // 최종연산: 4방향을 곱하기
    int viewcount;
    int i, j, k;
    for (i = 0; i < Hcount; i++) {
        for (j = 0; j < Wcount; j++) {
            viewleft[i][j] = 0;
            viewright[i][j] = 0;
            viewtop[i][j] = 0;
            viewbottom[i][j] = 0;
            viewcount = 0;
            for (k = j-1; k >= 0; k--, viewcount++) {
                if (grid[i][k] >= grid[i][j]) {
                    viewcount++;
                    break;
                }
            }
            viewleft[i][j] = viewcount;
            viewcount = 0;
            for (k = j+1; k <= Wcount-1; k++, viewcount++) {
                if (grid[i][k] >= grid[i][j]) {
                    viewcount++;
                    break;
                }
            }
            viewright[i][j] = viewcount;
            viewcount = 0;
            for (k = i-1; k >= 0; k--, viewcount++) {
                if (grid[k][j] >= grid[i][j]) {
                    viewcount++;
                    break;
                }
            }
            viewtop[i][j] = viewcount;
            viewcount = 0;
            for (k = i+1; k <= Hcount-1; k++, viewcount++) {
                if (grid[k][j] >= grid[i][j]) {
                    viewcount++;
                    break;
                }
            }
            viewbottom[i][j] = viewcount;
        }
    }
    int maxview = 0, maxH, maxW;
    cout << "After calculation, map of scenic view:\n"; // print and calculate at once
    for (int i = 0; i < Hcount; i++) { //for (int i = 0; i < Hcount; i++) {
        for (int j = 0; j < Wcount; j++) {
            view[i][j] = viewtop[i][j] * viewbottom[i][j] * viewleft[i][j] * viewright[i][j];
            if (view[i][j] > maxview) {
                maxview = view[i][j];
                maxH = i;
                maxW = j;\
            }
            if ((i == 48) && (j == 14)) {
                cout << "\033[1;35m" << (int)grid[i][j] << "\033[0m"; // magenta
            } else if (((i == 48) && (j < 31)) || (j == 14)) {
                cout << "\033[1;32m" << (int)grid[i][j] << "\033[0m"; // green
            } else {
                cout << (int)grid[i][j];
            }
            /*
            if (view[i][j] < 100) {
                cout << (int)grid[i][j];
            } else if (view[i][j] < 500) {
                cout << "\033[1;32m" << (int)grid[i][j] << "\033[0m"; // green
            } else if (view[i][j] < 2500) {
                cout << "\033[1;34m" << (int)grid[i][j] << "\033[0m"; // blue
            } else if (view[i][j] < 12500) {
                cout << "\033[1;36m" << (int)grid[i][j] << "\033[0m"; // cyan
            } else if (view[i][j] < 100000) {
                cout << "\033[1;35m" << (int)grid[i][j] << "\033[0m"; // magenta
            } else {
                cout << "\033[1;31m" << (int)grid[i][j] << "\033[0m"; // red
            }
            */
        }
        cout << "\n";
    }
    /*
    for (int i = 0; i < Hcount; i++) {
        for (int j = 0; j < Wcount; j++) {
            view[i][j] = viewtop[i][j] * viewbottom[i][j] * viewleft[i][j] * viewright[i][j];
            if (view[i][j] > maxview) maxview = view[i][j];
            if (view[i][j] < 100) {
                cout << (int)view[i][j] << " ";
            } else if (view[i][j] < 500) {
                cout << "\033[1;32m" << (int)view[i][j] << "\033[0m "; // green
            } else if (view[i][j] < 2500) {
                cout << "\033[1;34m" << (int)view[i][j] << "\033[0m "; // blue
            } else if (view[i][j] < 12500) {
                cout << "\033[1;36m" << (int)view[i][j] << "\033[0m "; // cyan
            } else if (view[i][j] < 100000) {
                cout << "\033[1;35m" << (int)view[i][j] << "\033[0m "; // magenta
            } else {
                cout << "\033[1;31m" << (int)view[i][j] << "\033[0m "; // red
            }
            //highest view score : view[48][14]
        }
        cout << "\n";
    }
    */
    cout << "\nThe grid [" << maxH << "][" << maxW << "] has the maximum scenic score of...\nLeft:\t" << viewleft[maxH][maxW] << "\nRight:\t" << viewright[maxH][maxW] << "\nTop:\t" << viewtop[maxH][maxW] << "\nBottom:\t" << viewbottom[maxH][maxW] << "\nTotal score: " << viewleft[maxH][maxW] << " x " << viewright[maxH][maxW] << " x " << viewtop[maxH][maxW] << " x " << viewbottom[maxH][maxW] << " = " << view[maxH][maxW] << endl;
}
int main() {
    quiz221208A();
    quiz221208B();
}
