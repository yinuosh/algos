#pragma once
#include <vector>

using namespace std;
class Algos
{
public:
	static int MaxSumOfSubArr(vector<int> arr) {
		int ans = INT_MIN;
		int curSum = 0;
		for (int i = 0; i < arr.size(); i++) {
			if (curSum + arr[i] < 0) {
				curSum = 0;
				if (ans < 0) ans = max(ans, arr[i]);
			}
			else {
				curSum += arr[i];
				ans = max(ans, curSum);
			}
		}
		return ans;
	}

	static int SumOfMul(vector<int> &a, vector<int> &b, int size) {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += (a[i]*b[i]);
		}
		return sum;
	}

	static bool Allocate_Increment(vector<int>& a, vector<int>& b, int bi, int bv) {
		b[bi] += bv;
		if (SumOfMul(a, b, a.size()) > a.size()) {
			b[bi] -= bv;
			return false;
		}
		else {
			return Allocate_Increment(a, b, b[bi], 1);
		}
	}

	/*
	* 举一个例子，

		数值: 0,1,2,3,4,5,6,7,8,9

		分配: 6,2,1,0,0,0,1,0,0,0

		0在下排出现了6次，1在下排出现了2次，

		2在下排出现了1次，3在下排出现了0次....
	*/
	static vector<int> Allocate(vector<int> a) {
		vector<int> b(a.size(), 0);
		for (int i = a.size(); i >= 0; i--) {
			int maxVal = a.size() / i;
			for (int v = maxVal; v >= 0; v--) {
				if (Allocate_Increment(a, b, i, v)) {
					if (SumOfMul(a, b, a.size()) == a.size())return b;
				}
			}
		}

	}

};

