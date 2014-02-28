#ifndef COMMON_H
#define COMMON_H

#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cassert>

#include <fstream>

#define DEBUG_INFO

#define DEBUG_INFO_LOG

using namespace std;

typedef double RTdouble;

typedef pair<RTdouble, RTdouble> Point2D;

class Geometry { // abstract base class
    public:
        virtual void print(const string &) const = 0;
};

void infoPrint(const string &);
string getCurrentTime();

#endif
