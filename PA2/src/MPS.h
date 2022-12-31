
#ifndef _MPS_H
#define _MPS_H

#include <vector>
 #include <stdint.h>
using namespace std;

class MPS
{
public:
    MPS(int , vector<int> &, vector<int> &, int*); // constructor
    ~MPS();
    int16_t solveMPS(int, int);
    void buildMaxTable();
    void buildAnsTable();
    void solve(int, int);
    int findEndOfJ(int);
    int16_t getAnswer();
    void printSolution(int, int);
    vector<int> ans;
    int *endOfJ;

private:
    int getIndex(int j);
    vector<int> ans_left;
    vector<int> ans_right;
    int N;
    int16_t answer;
    vector<int> input_left;
    vector<int> input_right;
    int8_t **ansTable;
    int16_t **maxTable;
    // vector<int> flow_right;
};

#endif
