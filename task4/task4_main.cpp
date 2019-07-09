#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

class time {
public:
    time(int h, int m) {
        h_ = h;
        m_ = m;
    }

    const string show() {
        return to_string(h_) +':' + to_string(m_);
    }

public:
    int h_;
    int m_;
};

bool operator<(time lhs, time rhs) {
    if (lhs.h_ < rhs.h_) {
        return true;
    }
    else if (lhs.h_ > rhs.h_) {
        return false;
    }
    else {
        if (lhs.m_ < rhs.m_) {
            return true;
        }
        else if (lhs.m_ > rhs.m_) {
            return false;
        }
        else {
            return false;
        }
    }

}


class person {
public:
    person(time t1, time t2) : t1_(t1), t2_(t2){

    }

    bool isInside(time t1, time t2) {
        return (t1_ < t1 | !(t1 < t1_)) & (t1 < t2_| !(t2_ < t1)) &
               (t1_ < t2 | !(t2 < t1_)) & (t2 < t2_| !(t2_ < t2));
    }
private:
    time t1_;
    time t2_;
};

int main() {
    string filename;
    cout << "Enter filename: ";

    cin >> filename;


    ifstream file(filename);

    // Провека. Открылся ли файл?
    if (!file.is_open()) {
        cout << "Can't open file" << endl;
        system("pause");
        return 1;
    }

    string str;
    vector<person> persons;
    set<time> times;
    while(getline(file, str)) {
        int h;
        int m;
        stringstream ss;
        ss << str;

        // Время входа
        ss >> h;
        ss.ignore();
        ss >> m;
        time t1(h,m);

        // Время выхода
        ss >> h;
        ss.ignore();
        ss >> m;
        time t2(h,m);

        times.insert(t1);
        times.insert(t2);

        person p1(t1, t2);
        persons.push_back(p1);


    }

    vector<time> times2;
    for (auto time : times) {
        times2.push_back(time);
    }

    int maxCntr = 0;
    vector<int> maxCntrIdx;

    for (int i = 0; i < times2.size() - 1; ++i) {
        int cntr = 0;
        for (auto person : persons) {
            if (person.isInside(times2[i], times2[i+1])) {
                cntr++;
            }
        }

        if (cntr > maxCntr) {
            maxCntr = cntr;
            maxCntrIdx.clear();
            maxCntrIdx.push_back(i);
        }
        else if (cntr == maxCntr) {
            maxCntrIdx.push_back(i);
        }
    }


    for (auto item : maxCntrIdx) {
        cout <<times2[item].show() << " - " <<times2[item+1].show() << endl;
    }
system("pause");
    return 0;
}