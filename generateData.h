#pragma once
#include <bits/stdc++.h>

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
void generateData(int n)
{
    ofstream fout("data.txt");
    for (int i = 0; i < n; i++)
    {
        fout << fixed << setprecision(3) << fRand(0, 100) << " " << fRand(0, 100) << " " << fRand(0, 100) << endl;
    }
    fout.close();
}