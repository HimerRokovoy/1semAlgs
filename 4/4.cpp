#include<iostream>
#include<vector>

using namespace std;
int is_sorted(vector<int> v)
{
    for(int i = 1; i < v.size(); i++)
    {
        if(v[i] < v[i-1])
        return -1;
        
    }
    return v[v.size()-1] - v[0];
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < v.size(); i++)
    {
        cin >> v[i];
    }
    cout << is_sorted(v);

 
}