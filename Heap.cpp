#include <bits/stdc++.h>

using namespace std;

int leastAfter(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int x : nums) q.push(x);
    while (k--){
        int top = q.top();
        q.pop();
        q.push(top * 2);
    }
    return q.top();
}

int main(){
    vector<int> nums {2, 3, 5, 7};
    int k = 3;
    cout << leastAfter(nums, k);
}