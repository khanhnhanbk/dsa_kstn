#include "hashing.h"
#include "KDtree.h"
#include "generateData.h"
int main()
{
    cout << "Enter the number of points: ";
    int n;
    cin >> n;
    generateData(n);
    testingKDTree(n);
    TestingHasing(n);
    return 0;
}