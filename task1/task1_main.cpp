#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

double max(vector<double> &vec) {

    double max = vec[0];
    for (double &item : vec) {
        if (item > max) {
            max = item;
        }
    }

    return max;
}

double min(vector<double> &vec) {

    double min = vec[0];
    for (double &item : vec) {
        if (item < min) {
            min = item;
        }
    }
    return min;
}

double mean(vector<double> &vec) {

    double sum = 0;
    for (double &item : vec) {
        sum += item;
    }

    double mean = sum / vec.size();

    return mean;
}

double median(vector<double> &vec) {

    sort(vec.begin(), vec.end());
    double median;

    if (vec.size() % 2 == 1) {
        int idx = vec.size() / 2;
        median = vec[idx];
    }
    else {
        int idx = vec.size() / 2;
        median = (vec[idx - 1] + vec[idx]) / 2;
    }

    return median;
}

double percentile90(vector<double> &vec) {

    sort(vec.begin(), vec.end());

    int n = vec.size();
    double idx = n * 0.9 + 0.5;
    int k = int(idx);
    double f = idx - k;

    double percentile = (1 - f) * vec[k - 1] + f * vec[k];


    return percentile;
}


int main(int argc, char *argv[]) {


    string filename;
    if (argc > 1) { // Имя файла, из аргумента
        filename = argv[1];
    }
    else { // Имя файла, введенное пользователем
        cout << "Enter filename: ";

        cin >> filename;

    }
    ifstream file(filename);

    // Провека. Открылся ли файл?
    if (!file.is_open()) {
        cout << "Can't open file" << endl;
        system("pause");
        return 1;
    }

    // Все числа помещаем в вектор vec
    vector<double> vec;
    double temp;
    string str;int cntr = 1;
    while(getline(file, str)) {

        stringstream ss;

        ss << str;

        double temp;
        ss >> temp;

        if (!ss.eof() | ss.fail()) {
            cout << "Line " << cntr << " has been ignored: " << str << endl;
            cntr++;
            continue;
        }
        cntr++;
        vec.push_back(temp);
    }


    if(vec.size() == 0) {
        cout << "File is empty!" << endl;
        system("pause");
        return 1;
    }


    double maxEl = max(vec);
    double minEl = min(vec);
    double meanEl = mean(vec);
    double medianEl = median(vec);
    double percentile90El = percentile90(vec);


    if (argc > 1) {
        ofstream output("output.txt");
        output << percentile90El << endl
               << medianEl << endl
               << meanEl << endl
               << maxEl << endl
               << minEl << endl;
        output.close();

    }
    else {
        cout << "90 percentile " << scientific << setprecision(3) << percentile90El << endl;
        cout << "median " << scientific << setprecision(3) << medianEl << endl;
        cout << "average " << scientific << setprecision(3) << meanEl << endl;
        cout << "max " << scientific << setprecision(3) << maxEl << endl;
        cout << "min " << scientific << setprecision(3) << minEl << endl;

        system("pause");
    }

    return 0;
}