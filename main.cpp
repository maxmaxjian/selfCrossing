#include <iostream>
#include <vector>

using namespace std;

class pos {
  public:
    int x, y;

    pos(){}
    pos(int xval, int yval) : x(xval), y(yval){}

    pos moveNorth(int dist) {
        return pos(x, y+dist);
    }

    pos moveSouth(int dist) {
        return pos(x, y-dist);
    }

    pos moveEast(int dist) {
        return pos(x+dist, y);
    }

    pos moveWest(int dist) {
        return pos(x-dist, y);
    }

    pos subtract(const pos & other) const {
        return pos(x-other.x, y-other.y);
    }

    int cross(const pos & other) const {
        return x*other.y-y*other.x;
    }
};

pos operator-(const pos & p1, const pos & p2) {
    return p1.subtract(p2);
}

int cross(const pos & ln1, const pos & ln2) {
    return ln1.cross(ln2);
}

class solution {
  public:
    bool isSelfCrossing(const vector<int> & x) {
        pos p1(0,0), p2, temp, p3, p4;
        size_t i = 0;
        p2 = p1.moveNorth(x[i++]);
        temp = p2.moveWest(x[i++]);
        p3 = temp.moveSouth(x[i++]);
        p4 = p3.moveEast(x[i]);

        return isCrossing(p1, p2, p3, p4);
    }

  private:
    bool isCrossing(const pos & p1, const pos & p2, const pos & p3, const pos & p4) {
        pos p31 = p3-p1, p41 = p4-p1, p32 = p3-p2, p42 = p4-p2;
        pos p13 = p1-p3, p23 = p2-p3, p14 = p1-p4, p24 = p2-p4;
        bool p1p2_ln34 = cross(p31,p41)*cross(p32,p42)>0;
        if (p1p2_ln34)
            std::cout << "p1, p2 are on the same side of ln34\n";
        else
            std::cout << "p1, p2 are on different sides of ln34\n";
        bool p3p4_ln12 = cross(p13,p23)*cross(p14,p24)>0;
        if (p3p4_ln12)
            std::cout << "p3, p4 are on the same side of ln12\n";
        else
            std::cout << "p3, p4 are on different sides of ln12\n";
        return !p1p2_ln34 && !p3p4_ln12;
    }
};

int main() {
    // vector<int> x{2,1,1,2};
    // vector<int> x{1,2,3,4};
    vector<int> x{1,1,1,1};

    solution soln;
    std::cout << std::boolalpha << soln.isSelfCrossing(x) << std::endl;
}
