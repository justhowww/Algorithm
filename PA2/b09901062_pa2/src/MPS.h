
#ifndef _MPS_H
#define _MPS_H

#include <vector>
using namespace std;

class MPS
{
public:
    MPS(int, vector<int> &, vector<int> &, int*); // constructor
    int solveMPS(int, int);
    int **buildMaxTable();
    int **buildAnsTable();
    int findEndOfJ(int);
    int getAnswer();
    void printSolution(int, int);
    vector<int> ans;
    int *endOfJ;

private:
    int getIndex(int j);
    vector<int> ans_left;
    vector<int> ans_right;
    int N;
    vector<int> input_left;
    vector<int> input_right;
    int **ansTable;
    int **maxTable;
    // vector<int> flow_right;
};

#endif
