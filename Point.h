#pragma once
#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
    vector<double> coord;
    Point(vector<double> coord)
    {
        if (coord.size() != 3)
        {
            cout << "Error: Point must have 3 coordinates" << endl;
            exit(1);
        }
        this->coord = coord;
    }
    bool operator==(const Point &p) const
    {
        return this->coord == p.coord;
    }
    double distance(Point p)
    {
        double sum = 0;
        for (int i = 0; i < coord.size(); i++)
        {
            sum += pow(coord[i] - p.coord[i], 2);
        }
        return sqrt(sum);
    }
    void print()
    {
        cout << "(";
        for (int i = 0; i < coord.size(); i++)
        {
            cout << coord[i] << " ";
        }
        cout << ")";
    }
};