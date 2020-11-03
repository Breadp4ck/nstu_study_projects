#include <iostream>
#include <stack>

using namespace std;

int main()
{
    // Create stack
    stack<int> st;
    int input;
    
    // Fill stack
    cin >> input;
    while (input != 0)
    {
        st.push(input);
        cin >> input;
    }

    // Outpust stack
    cout << endl << "Вывод:" << endl;
    while (!st.empty())
    {
        cout << st.top() << endl;
        st.pop();
    }

    return 0;
}
