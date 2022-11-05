// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "MPS.h"

using namespace std;

void help_message()
{
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        help_message();
        return 0;
    }

    //////////// read the input file /////////////

    int N = 0;
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    fin >> N;
    int l, r;
    vector<int> left, right;
    int *pair = new int[N];

    cout << "input\n";
    while (fin >> l >> r)
    {
        if (r)
        {
            pair[l] = r;
            pair[r] = l;
            left.push_back(l);
            right.push_back(r);
        }
    }

    //////////// MPS ////////////////

    MPS mps(N, left, right, pair);
    cout << "start solving\n";
    mps.solveMPS(0, N - 1);
    // cout << mps.getAnswer() << endl;

    cout << "reversing solution" << endl;
    mps.printSolution(0, N - 1);
    sort(mps.ans.begin(), mps.ans.end());
    cout << "ans num: " << mps.ans.size() << endl;
    for (int i = 0; i < mps.ans.size(); i++)
    {
        cout << mps.ans[i] << endl;
    }
    //////////// write the output file ///////////
    fout << mps.getAnswer() << endl;
    for (int i = 0; i < mps.ans.size(); i++)
        fout << mps.ans[i] << " " << mps.endOfJ[mps.ans[i]] << endl;
    fin.close();
    fout.close();
    return 0;
}

// int main()
// {
//     int N = 12;
//     vector<int> l = {0, 1, 2, 3, 5, 8};
//     vector<int> r = {4, 9, 6, 10, 7, 11};
//     MPS mps(N, l, r);
//     mps.solveMPS();
//     cout << mps.maxTable[0][11] << endl;
//     mps.printSolution(0, 11);
// }
