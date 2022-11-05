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
    maxTable = buildMaxTable();
    ansTable = buildAnsTable();
    endOfJ = pair;
}

int **MPS::buildMaxTable()
{
    int **tempMaxTable = new int *[N];
    for (int i = 0; i < N; ++i)
        tempMaxTable[i] = new int[N];
    for (int i = 0; i < N; ++i)
    { // for each row
        for (int j = 0; j < N; ++j)
        { // for each column

            if (i == j)
            {
                tempMaxTable[i][j] = 0;
            }
            else
            {
                tempMaxTable[i][j] = -1;
            }
            // cout << tempMaxTable[i][j] << " ";
        }
        // cout << endl;
    }
    return tempMaxTable;
}
int **MPS::buildAnsTable()
{
    int **tempMaxTable = new int *[N];
    for (int i = 0; i < N; ++i)
        tempMaxTable[i] = new int[N];
    for (int i = 0; i < N; ++i)
    { // for each row
        for (int j = 0; j < N; ++j)
        { // for each column

            tempMaxTable[i][j] = -1;

            // cout << tempMaxTable[i][j] << " ";
        }
        // cout << endl;
    }
    return tempMaxTable;
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

int MPS::solveMPS(int i, int j)
{
    if (j >= i)
    {
        if (maxTable[i][j] == -1)
        {
            int k = findEndOfJ(j);
            int v3 = solveMPS(i, j - 1);
            if (j > k && k >= i)
            {
                int v1 = solveMPS(k + 1, j - 1);
                int v2 = solveMPS(i, k - 1);

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

// int MPS::solveMPS(int i, int j)
// {
//     if (j >= i)
//     {
//         if (maxTable[i][j] == -1)
//         {
//             int k = findEndOfJ(j);
//             int v1 = solveMPS(k + 1, j - 1);
//             if (k == i)
//             {
//                 ansTable[i][j] = 1;
//                 maxTable[i][j] = 1 + v1;
//                 return 1 + v1;
//             }
//             else
//             {

//                 int v3 = solveMPS(i, j - 1);
//                 if (j > k && k > i)
//                 {
//                     int v2 = solveMPS(i, k - 1);

//                     if (v3 < 1 + v1 + v2)
//                     {
//                         maxTable[i][j] = 1 + v1 + v2;
//                         ansTable[i][j] = 2;
//                         return 1 + v1 + v2;
//                     }
//                 }
//                 else
//                 {
//                     maxTable[i][j] = v3;
//                     ansTable[i][j] = 3;
//                     return v3;
//                 }
//             }
//         }
//         return maxTable[i][j];
//     }
//     return 0;
// }

void MPS::printSolution(int start, int end)
{
    if (start == end)
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
    else
    {
        printSolution(start, end - 1);
    }
}

int MPS::getAnswer()
{

    return maxTable[0][N - 1];
}