#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // Create vector
    vector<int> vec;
    int input;
    
    // Fill vector
    cin >> input;
    while (input != 0)
    {
        vec.push_back(input);
        cin >> input;
    }

    // Sort, then remove duplicates
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    // Output vector
    cout << endl << "Вывод:" << endl;
    for (int i : vec) cout << i << endl;

    return 0;
}

