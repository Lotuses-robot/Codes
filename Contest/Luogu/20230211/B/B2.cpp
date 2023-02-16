#include <iostream>
#include <vector>

using namespace std;

int findMedian(vector<int>& nums) {
    int n = nums.size();
    int left = 0, right = n - 1;
    int k = (n + 1) / 2;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] <= nums[mid]) {
                count++;
            }
        }
        if (count <= k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return nums[left];
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << findMedian(nums) << endl;
    return 0;
}
