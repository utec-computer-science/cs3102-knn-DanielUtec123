#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int N = 1000;

template <typename T>
class CartesianCoord{
public:
    typedef T value_t;
    value_t x;
    value_t y;
public:
    CartesianCoord(value_t _x = 0, value_t _y = 0)
            :x(_x),y(_y){
    }
    ~CartesianCoord(void){
    }
    template<typename _T>
    friend ostream& operator<<(ostream &out, const CartesianCoord<_T> c){
        out << "(" << c.x << "," << c.y << ")";
        return out;
    }
};
typedef CartesianCoord<int> coord_t;

struct PointWithDistance{
    coord_t point;
    double distance;
};

double Distance(coord_t a, coord_t b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y,2));
}

bool ComparePointWithDistance(PointWithDistance p1, PointWithDistance p2){
    return p1.distance < p2.distance;
}


vector<coord_t> knn ( int k, vector<coord_t> &points, const coord_t &q){
    // KNNS

    vector<PointWithDistance > point_distances;

    for (auto point:points){
        PointWithDistance a;
        a.point = point;
        a.distance = Distance(q,point);
        point_distances.push_back(a);
    }

    sort(point_distances.begin(),point_distances.end(),ComparePointWithDistance);



    cout << "K nierest"<< endl;

    for (auto it = point_distances.begin(); it != point_distances.begin()+k; it++){
        cout << it->point << " " << it->distance << endl;

    }

    return vector<coord_t>();
}


int main() {
    srand (time(NULL));

    vector<coord_t> points;
    for(int i=0; i< N; i++)
        points.push_back(coord_t(rand()%1000,rand()%1000));

 /*   vector<coord_t>::iterator it = points.begin();
    for (; it != points.end(); it++){
        fflush(stdout);
        cout << "\r" << *it;
        usleep(2000);
    }
*/
    vector<coord_t> knns;
    auto start = chrono::high_resolution_clock::now();
    knns = knn(3, points, coord_t(100,200));
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time: " << endl;
    cout << duration.count() << endl;
    cout << "knns" << endl;
    vector<coord_t>::iterator kit = knns.begin();
    for (; kit != knns.end(); kit++)
        cout << *kit << endl;
}

