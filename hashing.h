#pragma once
#include "Point.h"

class HashTable
{
private:
    int size;
    vector<vector<vector<list<Point *>>>> table;
    int count;

public:
    HashTable(int size)
    {
        this->size = size;
        table.clear();
        table.resize(size + 1);
        for (int i = 0; i < size; i++)
        {
            table[i].resize(size + 1);
            for (int j = 0; j < size; j++)
            {
                table[i][j].resize(size + 1);
                for (int k = 0; k < size; k++)
                {
                    table[i][j][k].clear();
                }
            }
        }
        count = 0;
    }
    void insert(Point point)
    {
        int x = floor((point.coord[0] / 100.0 * size));
        int y = floor((point.coord[1] / 100.0 * size));
        int z = floor((point.coord[2] / 100.0 * size));
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (z < 0)
            z = 0;
        if (x >= size)
            x = size - 1;
        if (y >= size)
            y = size - 1;
        if (z >= size)
            z = size - 1;
        Point *newPoint = new Point(point);
        table[x][y][z].insert(table[x][y][z].begin(), newPoint);
        // cout << "inserted " << newPoint->coord[0] << " " << newPoint->coord[1] << " " << newPoint->coord[2] << endl;
        // cout << "to " << x << " " << y << " " << z << endl;

        count++;
    }
    Point *nearestPoint(Point p)
    {
        // find the bucket
        int x = floor((p.coord[0] / 100.0 * size));
        int y = floor((p.coord[1] / 100.0 * size));
        int z = floor((p.coord[2] / 100.0 * size));
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (z < 0)
            z = 0;
        if (x >= size)
            x = size - 1;
        if (y >= size)
            y = size - 1;
        if (z >= size)
            z = size - 1;
        // find the nearest point
        double min_dist = 1000000;
        Point *nearest = nullptr;
        list<Point *>::iterator it;
        for (it = table[x][y][z].begin(); it != table[x][y][z].end(); it++)
        {
            double dist = (*it)->distance(p);
            if (dist < min_dist)
            {
                min_dist = dist;
                nearest = *it;
            }
        }
        int direct = 0;
        vector<int> index = {x, y, z, direct};
        queue<vector<int>> q;
        vector<bool> visited(size * size * size, false);
        visited[x * size * size + y * size + z] = true;
        for (direct = 0; direct < 3; direct++)
        {
            if (index[direct] + 1 < size)
            {
                index[direct]++;
                index[3] = direct;
                q.push(index);
                visited[index[0] * size * size + index[1] * size + index[2]] = true;
                index[direct]--;
            }
            if (index[direct] - 1 >= 0)
            {
                index[direct]--;
                index[3] = direct;
                q.push(index);
                visited[index[0] * size * size + index[1] * size + index[2]] = true;
                index[direct]++;
            }
        }
        while (!q.empty())
        {
            index = q.front();
            // cout << index[0] << " " << index[1] << " " << index[2] << endl;
            direct = index[3];
            q.pop();
            if (fabs((index[direct] * 100.0 / float(size)) - p.coord[direct]) > min_dist && fabs(((index[direct] + 1) * 100.0 / float(size)) - p.coord[direct]) > min_dist)
            {
                continue;
            }
            for (int i = 0; i < 3; i++)
            {
                if (index[i] + 1 < size)
                {
                    index[i]++;
                    index[3] = i;
                    if (!visited[index[0] * size * size + index[1] * size + index[2]])
                    {
                        q.push(index);
                        visited[index[0] * size * size + index[1] * size + index[2]] = true;
                    }
                    index[i]--;
                }
                if (index[i] - 1 >= 0)
                {
                    index[i]--;
                    index[3] = i;
                    if (!visited[index[0] * size * size + index[1] * size + index[2]])
                    {
                        q.push(index);
                        visited[index[0] * size * size + index[1] * size + index[2]] = true;
                    }
                    index[i]++;
                }
            }
            list<Point *>::iterator it;
            x = index[0];
            y = index[1];
            z = index[2];
            for (it = table[x][y][z].begin(); it != table[x][y][z].end(); it++)
            {
                double dist = (*it)->distance(p);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    nearest = *it;
                }
            }
        }

        return nearest;
    }
};

void TestingHasing(int n)
{
    clock_t start, end;
    if (fopen("./data.txt", "r"))
    {
        freopen("./data.txt", "r", stdin);
    }
    cout << "\n\nTHIS IS HASHING:";

    start = clock();

    HashTable ht(10);
    double x, y, z;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> z;
        ht.insert(Point({x, y, z}));
    }
    end = clock();
    cout << "\nBuild time: " << (double)(end - start) / CLOCKS_PER_SEC << " s" << endl;
    start = clock();
    cout << "Nearest point (0, 0, 0) is: ";
    ht.nearestPoint(Point({0, 0, 0}))->print();
    cout << endl;
    cout << "Nearest point (50, 50, 50) is: ";
    ht.nearestPoint(Point({50, 50, 50}))->print();
    cout << endl;
    cout << "Nearest point (99, 99, 99) is: ";
    ht.nearestPoint(Point({99, 99, 99}))->print();
    cout << endl;
    end = clock();
    cerr << "\nSearch time: " << ((double)(end - start)) / CLOCKS_PER_SEC << "s\n\n";
    // close file
    fclose(stdin);
}