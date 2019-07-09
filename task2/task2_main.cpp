#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

const bool onVertex(const vector<float> &vecx,
                    const vector<float> &vecy,
                    const float &xp,
                    const float &yp) {

    bool tf = false;
    for (int i = 0; i < vecx.size(); ++i) {
        if (xp == vecx[i] & yp == vecy[i]) {
            tf = true;
            break;
        }
    }
    return tf;
}


const bool onSpecificEdge(const float &x1, const float &x2,
                          const float &y1, const float &y2,
                          const float &x , const float &y) {
    if (x2-x1 == 0)  {
        bool tf1 = (y1 - y) * (y - y2) >= 0;
        bool tf2 = x == x1;
        return tf1 & tf2;
    }
    else {


        float k = (y2 - y1) / (x2 - x1);
        float b = y2 - k * x2;

        bool tf1 = (k * x + b) == y;
        bool tf2 = (x1 - x) * (x - x2) >= 0;
        bool tf3 = (y1 - y) * (y - y2) >= 0;
        return tf1 & tf2 & tf3;
    }
}

const bool onEdge(const vector<float> &vecx,
                  const vector<float> &vecy,
                  const float &xp,
                  const float &yp) {

    bool tf = false;
    for (int i = 0; i < vecx.size(); ++i) {
        if (i != vecx.size() - 1) {
            if (onSpecificEdge(vecx[i], vecx[i + 1],
                               vecy[i], vecy[i + 1],
                               xp, yp)) {
                tf = true;
                break;
            }
        }
        else {
            if (onSpecificEdge(vecx[i], vecx[i],
                               vecy[1], vecy[1],
                               xp, yp)) {
                tf = true;
                break;
            }
        }
    }


    return tf;
}

const bool isInside(const vector<float> &vecx,
                  const vector<float> &vecy,
                  const float &xp,
                  const float &yp) {

    // Только четырехугольник
    float bax = vecx[1] - vecx[0];
    float bay = vecy[1] - vecy[0];
    float dax = vecx[3] - vecx[0];
    float day = vecy[3] - vecy[0];

    bool tf1 = ( (xp - vecx[0])*bax + (yp - vecy[0])*bay ) < 0;
    bool tf2 = ( (xp - vecx[1])*bax + (yp - vecy[1])*bay ) > 0;
    bool tf3 = ( (xp - vecx[0])*dax + (yp - vecy[0])*day ) < 0;
    bool tf4 = ( (xp - vecx[3])*dax + (yp - vecy[3])*day ) > 0;

    return !(tf1 | tf2 | tf3 | tf4);
}



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

    // Координаты в векторы vecx и vecy
    vector<float> vecx;
    vector<float> vecy;
    string str;

    while (getline(file, str)) {
        stringstream ss;
        ss << str;

        float x;
        float y;
        ss >> x;
        ss >> y;

        vecx.push_back(x);
        vecy.push_back(y);
    }


    // Ввод координаты точки
    float xp, yp;
    cout << "Enter x: ";
    cin >> xp;
    cout << "Enter y: ";
    cin >> yp;


    // Проверка
    if ( onVertex(vecx, vecy, xp, yp) ) { // На вершине?
        cout << "The point is on the vertex" << endl;

    }
    else if ( onEdge(vecx, vecy, xp, yp) ) { // На грани?
        cout << "The point is on the edge" << endl;
    }
    else if ( isInside(vecx, vecy, xp, yp) ) { // Внутри ?
        cout << "The point is inside" << endl;
    }
    else { // Снаружи
        cout << "The point is outside" << endl;
    }

    system("pause");
    return 0;
}