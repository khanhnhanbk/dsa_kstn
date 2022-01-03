#pragma once
#include "Point.h"

class Node
{
public:
    Point point;
    Node *left;
    Node *right;
    int axis;
    Node(Point point) : point(point), left(NULL), right(NULL), axis(0){};
    ~Node()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
    }
};
class KDtree
{
    Node *root;

public:
    KDtree()
    {
        root = NULL;
    }
    ~KDtree()
    {
        delete root;
    }
    void insert(Point point)
    {
        if (root == NULL)
        {
            root = new Node(point);
            root->axis = 0;
            return;
        }
        Node *cur = root;
        while (cur)
        {
            if (point.coord[cur->axis] < cur->point.coord[cur->axis])
            {
                if (cur->left == NULL)
                {
                    cur->left = new Node(point);
                    cur->left->axis = (cur->axis + 1) % 3;
                    return;
                }
                cur = cur->left;
            }
            else
            {
                if (cur->right == NULL)
                {
                    cur->right = new Node(point);
                    cur->right->axis = (cur->axis + 1) % 3;
                    return;
                }
                cur = cur->right;
            }
        }
    }

    Node *search(Point point)
    {
        if (root == NULL)
            return NULL;
        Node *cur = root;
        while (cur)
        {
            if (cur->point == point)
                return cur;
            if (point.coord[cur->axis] < cur->point.coord[cur->axis])
                cur = cur->left;
            else
                cur = cur->right;
        }
        return NULL;
    }
    // find the nearest point to the given point
    Node *nearest(Point point)
    {
        if (root == NULL)
        {
            cout << "Error: Tree is empty" << endl;
            exit(1);
        }
        double min_dist = root->point.distance(point);
        Node *result = root;
        // find the nearest point
        Node *cur = root;
        while (cur)
        {
            double dist = cur->point.distance(point);
            if (dist < min_dist)
            {
                min_dist = dist;
                result = cur;
            }
            if (point.coord[cur->axis] < cur->point.coord[cur->axis])
                cur = cur->left;
            else
                cur = cur->right;
        }
        nearest(point, root, min_dist, result);
        return result;
    }
    void nearest(Point point, Node *cur, double &min_dist, Node *&result)
    {
        if (cur == NULL)
            return;
        double dist = cur->point.distance(point);
        if (dist < min_dist)
        {
            min_dist = dist;
            result = cur;
        }
        if (point.coord[cur->axis] - cur->point.coord[cur->axis] < min_dist)
            nearest(point, cur->left, min_dist, result);
        if (cur->point.coord[cur->axis] - point.coord[cur->axis] < min_dist)
            nearest(point, cur->right, min_dist, result);
    }
};

int testingKDTree(int n)
{
    if (fopen("./data.txt", "r"))
    {
        freopen("./data.txt", "r", stdin);
    }
    cout << "\n\nTHIS IS KD-TREE:";
    clock_t start, end;
    start = clock();
    KDtree kd;
    double x, y, z;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> z;
        kd.insert(Point({x, y, z}));
    }
    end = clock();
    cerr << "\nBuild time: " << ((double)(end - start)) / CLOCKS_PER_SEC << "s\n\n";

    start = clock();
    cout << "Nearest point (0, 0, 0) is: ";
    kd.nearest(Point({0, 0, 0}))->point.print();
    cout << endl;
    cout << "Nearest point (50, 50, 50) is: ";
    kd.nearest(Point({50, 50, 50}))->point.print();
    cout << endl;
    cout << "Nearest point (99, 99, 99) is: ";
    kd.nearest(Point({99, 99, 99}))->point.print();
    cout << endl;
    end = clock();

    cerr << "\nExecution time: " << ((double)(end - start)) / CLOCKS_PER_SEC << "s\n\n";
    fclose(stdin);
    return 0;
}