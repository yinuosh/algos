#pragma once
#include "Util.h"
#include <vector>
#include <limits>
#include <queue>

using namespace std;

struct BinarayTreeNode {
	int val;
	BinarayTreeNode* left;
	BinarayTreeNode* right;

	BinarayTreeNode(int value, BinarayTreeNode* l, BinarayTreeNode* r) {
		val = value;
		left = l;
		right = r;
	}
};


typedef void (*TreeNodeHandler) (BinarayTreeNode*);

class TreeNodeMethods {
public:

	static BinarayTreeNode* FromHeapifyArray(int arr[], int len, int i) {
		// iLeftChild = 2 * i + 1,  iRightChild = 2*i + 1
		if (i >= len)return NULL;
		BinarayTreeNode* node = new BinarayTreeNode(arr[i], NULL, NULL);
		if (2 * i + 1 < len) {
			node->left = FromHeapifyArray(arr, len, 2 * i + 1);
			if (2 * 2 + 2 < len) {
				node->right = FromHeapifyArray(arr, len, 2 * i + 2);
			}
		}
		return node;
	}

	static void ToHeapifyArray(BinarayTreeNode* root, vector<int>& arr) {
		queue<BinarayTreeNode*> nodeQ;
		if (root == NULL)return;
		nodeQ.push(root);
		while (!nodeQ.empty()) {
			BinarayTreeNode* curNode = nodeQ.front();
			arr.push_back(curNode->val);
			nodeQ.pop();
			if (NULL != curNode->left)nodeQ.push(curNode->left);
			if (NULL != curNode->right)nodeQ.push(curNode->right);
		}
	}

	static void BFS(BinarayTreeNode* root, TreeNodeHandler handler) {
		queue<BinarayTreeNode*> nodeQ;
		if (root == NULL)return;
		nodeQ.push(root);
		while (!nodeQ.empty()) {
			BinarayTreeNode* curNode = nodeQ.front();
			handler(curNode);
			nodeQ.pop();
			if (NULL != curNode->left)nodeQ.push(curNode->left);
			if (NULL != curNode->right)nodeQ.push(curNode->right);
		}
	}

	static void DFS(BinarayTreeNode* root, TreeNodeHandler handler) {
		if (root == NULL)return;
		handler(root);
		DFS(root->left, handler);
		DFS(root->right, handler);
	}

	BinarayTreeNode* lowestCommonAncestorTopDown(BinarayTreeNode* root, BinarayTreeNode* p, BinarayTreeNode* q) {
		if (root == NULL)return NULL;
		if (root == p || root == q)return root;

		BinarayTreeNode* lAncestor = lowestCommonAncestorTopDown(root->left, p, q);
		BinarayTreeNode* rAncestor = lowestCommonAncestorTopDown(root->right, p, q);
		if (lAncestor && rAncestor) return root;
		else if (NULL != lAncestor) return lAncestor;
		else if (NULL != rAncestor) return rAncestor;
		else {
			return NULL;
		}
	}
};

class BinarySearchTree {
private:
	BinarayTreeNode* mRoot = NULL;
	static void printTreeNode(BinarayTreeNode* node) {
		if (node) cout << node->val << ",";
	}
	
	BinarayTreeNode* Exists(BinarayTreeNode* fromNode, int val) {
		if (NULL == fromNode)return NULL;
		if (fromNode->val == val)return fromNode;
		else if (fromNode->val > val) return Exists(fromNode->left, val);
		else return Exists(fromNode->right, val);
	}

public:
	BinarySearchTree(BinarayTreeNode* root) :mRoot(root) {};

	void Insert(BinarayTreeNode* node) {

	}

	void Delete(BinarayTreeNode* node) {

	}

	BinarayTreeNode* Exists(int val) {
		return Exists(mRoot, val);
	}

	void PrintAsHeapifyArray() {
		cout << "[";
		TreeNodeMethods::BFS(mRoot, BinarySearchTree::printTreeNode);
		cout << "]";
	}
};

class SortFactory
{
public:
	static void QuickSort(int data[], int len);
	static void MergeSort(int data[], int len);
	static void HeapSort(int data[], int len);
	static void BubbleSort(int data[], int len);
	static std::vector<int> SearchStringKMP(const char* s, int sLen, const char* p, int pLen);
	static void LeftRotateString(char* s, int n, int m);
	static void ReverseString(char* s, int from, int to);
	static void ReverseWords(char* s) {
		char* p = s;
		int from = 0, to = 0;
		while (*p != '\0') {
			if (*p == ' ') {
				if (from < to - 1) ReverseString(s, from, to - 1);
				from = to + 1;
			}
			p++;
			to++;
		}
		if (from < to - 1) ReverseString(s, from, to - 1);
		ReverseString(s, 0, to - 1);
	}

	static int StrToInt(const char* s) {
		char* p = (char*)s;
		while (*p != '\0' && *p == ' ')p++;
		int n = 0;
		int sign = 1;

		if (*p == '\0') throw - 1;

		if (*p == '-' || *p == '+')
		{
			sign = *p == '-' ? -1 : 1;
			p++;
		}

		while (isdigit(*p)) {
			int d = *p - '0';
			if (sign > 0 &&
				(n > INT_MAX / 10 ||
					(n == INT_MAX / 10 && d > INT_MAX % 10))) {
				n = INT_MAX;
				break;
			}
			else if (sign < 0 &&
				(n > (unsigned int)INT_MIN / 10 ||
					(n == (unsigned int)INT_MIN / 10 && d > (unsigned int)INT_MIN % 10))) {
				n = INT_MIN;
				break;
			}
			else {
				n = n * 10 + d;
			}
			p++;
		}

		if (n != INT_MIN && sign < 0)n = -n;
		return n;
	}

	static bool MatchRecursive(char* s, char* p) {
		//int sLen = s.size();
		//int pLen = p.size();

		char* sp = (char*)s;
		char* pp = (char*)p;

		if ('\0' == *pp)return true;
		if ('\0' == *sp) {
			return false;
		}

		if ('*' == *pp) {
			return MatchRecursive(sp, pp + 1); // ingore extra *
		}

		if (*sp == *pp || '.' == *pp) {
			if ('*' == *(pp + 1)) {
				return MatchRecursive(sp, pp + 1) || MatchRecursive(sp + 1, pp + 1);
			}
			else return MatchRecursive(sp + 1, pp + 1);
		}
		else {
			return MatchRecursive(sp + 1, pp);
		}
	}

	static bool MatchDP(char* s, int sLen, char* p, int pLen) {
		vector<vector<int>> dp(sLen + 1, vector<int>(pLen + 1, -1));
		// dp[i, j] = Match(s+i, sLen-i, p+j, pLen-j)

		// if p reach to end, match success and match length is 0
		for (int i = 0; i <= sLen; i++) {
			dp[i][pLen] = 0;
		}

		// if s reach to end,  if p left "." or ".*", it macths with length 0, otherwise not match.
		for (int j = pLen - 1; j >= 0; j--) {
			if ((p[j] == '*') || (j + 1 < pLen - 1 && p[j + 1] == '*')) {
				dp[sLen][j] = dp[sLen][j + 1];
			}
			else {
				dp[sLen][j] = -1;
			}
		}

		for (int i = sLen - 1; i >= 0; i--) {
			for (int j = pLen - 1; j >= 0; j--) {
				dp[i][j] = -1;
				if ('*' == p[j]) {
					continue;
				}

				bool nextIsStar = false;
				if (j < pLen - 1 && '*' == p[j + 1]) nextIsStar = true;
				if (s[i] == p[j] || '.' == p[j]) {
					if (nextIsStar) {
						int dpOfSkip = dp[i][j + 2]; // ignore "p[j]*"
						int dpOfNotSkip = dp[i + 1][j + 2];
						if (dpOfSkip >= 0)dp[i][j] = dpOfSkip;
						if (dpOfNotSkip >= 0 && dp[i][j] < dpOfNotSkip + 1)dp[i][j] = dpOfNotSkip + 1;
					}
					else {
						int nextDp = dp[i + 1][j + 1];
						if (nextDp >= 0) dp[i][j] = nextDp + 1;
					}
				}
			}
		}
		for (int i = 0; i < sLen; i++) {
			if (dp[i][0] >= 0)
				std::cout << "dp[" << i << "][0]: " << dp[i][0] << std::endl;
		}

		return dp[0][0] >= 0;
	}

private:
	static void QuickSort(int data[], int start, int end);
	static void QuickSort2(int data[], int start, int end);

	static void MergeSort_Rur(int data[], int low, int hi, int cache[]);

	static int iParent(int i);
	static int iLeftChild(int i);
	static int iRightChild(int i);
	static void SiftDown(int data[], int start, int end);
	static void Heapify(int data[], int len);
};
