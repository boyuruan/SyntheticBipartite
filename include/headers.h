#ifndef HEADERS_INCLUDED
#define HEADERS_INCLUDED

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

enum Strategy { fix, step };

struct Para {
    int upperLevel;
    int lowerLevel;
    int bloomSize;
    int overLap;
    double prob;
    char file[255];
    enum Strategy strategy;
};

struct Para parse_args(int argc, char **argv);

#endif