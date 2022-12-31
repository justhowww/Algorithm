// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "MPS.h"
#include <iostream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
#include <cmath>
#include <string.h>
#include <algorithm>
#include <tuple>

using namespace std;

// Constructor
MPS::MPS(int num_input, vector<int> &left, vector<int> &right, int* pair)
{
    input_left = left;
    input_right = right;
    N = num_input;
    cout << "building table" << endl;
    buildMaxTable();
    buildAnsTable();
    endOfJ = pair;
}

MPS::~MPS(){

    for (int i = 0; i < N; ++i)
    { // for each row
        delete[] ansTable[i]; 
        // cout << endl;
    }
    delete [] ansTable;
    ansTable = NULL;

}

void MPS::buildMaxTable()
{
    maxTable = new int16_t *[N];
    for (int i = 0; i < N; ++i)
        maxTable[i] = new int16_t[N];
    for (int i = 0; i < N; ++i)
    { // for each row
        for (int j = 0; j < N; ++j)
        { // for each column

            if (i == j)
            {
                maxTable[i][j] = 0;
            }
            else
            {
                maxTable[i][j] = -1;
            }
        }
    }
}
void MPS::buildAnsTable()
{
    ansTable = new int8_t *[N];
    for (int i = 0; i < N; ++i)
        ansTable[i] = new int8_t[N];
    for (int i = 0; i < N; ++i)
    { // for each row
        for (int j = 0; j < N; ++j)
        { // for each column

            ansTable[i][j] = 0;

            // cout << tempMaxTable[i][j] << " ";
        }
        // cout << endl;
    }
}

int MPS::findEndOfJ(int j)
{
    if (endOfJ[j] == -1)
    {
        vector<int>::iterator it = find(input_left.begin(), input_left.end(), j);
        if (it != input_left.end())
        {
            endOfJ[j] = input_right[distance(input_left.begin(), it)];
            return endOfJ[j];
        }
        else
        {
            vector<int>::iterator it = find(input_right.begin(), input_right.end(), j);
            if (it != input_right.end())
            {

                endOfJ[j] = input_left[distance(input_right.begin(), it)];
                return endOfJ[j];
            }
        }
    }
    return endOfJ[j];
}

void MPS::solve(int i, int j){
    solveMPS(i, j);
    answer = maxTable[0][N - 1];
    for (int i = 0; i < N; ++i)
    { // for each row

        delete[] maxTable[i]; 
        // cout << endl;
    }
    delete [] maxTable;
    maxTable = NULL;

    input_left.clear();
    input_right.clear();
}

int16_t MPS::solveMPS(int i, int j)
{
    if (j >= i)
    {
        if (maxTable[i][j] == -1)
        {
            int k = findEndOfJ(j);
            int16_t v3 = solveMPS(i, j - 1);
            if (j > k && k >= i)
            {
                int16_t v1 = solveMPS(k + 1, j - 1);
                int16_t v2 = solveMPS(i, k - 1);

                if (v3 > 1 + v1 + v2)
                {
                    maxTable[i][j] = v3;
                    ansTable[i][j] = 3;
                    return v3;
                }
                else
                {

                    if(k == i){
                        maxTable[i][j] = 1 + v1;
                        ansTable[i][j] = 1;
                        return 1+v1;
                    }
                    maxTable[i][j] = 1 + v1 + v2;
                    ansTable[i][j] = 2;
                    
                    return 1 + v1 + v2;
                }
            }
            else
            {
                maxTable[i][j] = v3;
                ansTable[i][j] = 3;
                return v3;

            }
        }
        return maxTable[i][j];
    }
   
}


void MPS::printSolution(int start, int end)
{
    if (start == end || end < 0 || end >= N || start < 0 || start >= N)
        return;
   
    if (ansTable[start][end] == 1)
    {
        ans.push_back(start);

        printSolution(start + 1, end - 1);
    }
    else if (ansTable[start][end] == 2)
    {
        const int k = findEndOfJ(end);
        ans.push_back(k);
        printSolution(start, k - 1);
        printSolution(k + 1, end - 1);
    }
    else if(ansTable[start][end] == 3)
    {
        printSolution(start, end - 1);
    }
    else{
        return;
    }
}

int16_t MPS::getAnswer()
{
    return answer;
}