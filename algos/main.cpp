﻿#include <iostream>
#include "SortFactory.h"
#include <stack>
#include <map>
#include <ctime>
#include <vector>
#include "BinaryTreeNode.h"
#include "LinkedNode.h"
#include "Algos.h"

using namespace std;

bool IsValidString(const char* str, int len);


std::stack<int> A, B, C;
std::map<char, int> hanoiMap;
void printTreeNode(BinaryTreeNode* node);

int main(int argc, char* argv[])
{
	std::cout << "Hello world!" << std::endl;
	std::string s = "AABAACAADAABAABA";
	std::string p = "AABA";
	auto result = SortFactory::SearchStringKMP(s.c_str(), s.size(), p.c_str(), p.size());
	for (auto i : result) {
		std::cout << i << std::endl;
	}

	string input = "Hi, this is Sky!";
	char chars[] = "AABAACAADAABAABA";
	SortFactory::LeftRotateString(chars, s.size(), 4);
	std::cout << chars << std::endl;

	char chars2[] = "Hi, this is Sky!";
	SortFactory::ReverseWords(chars2);
	std::cout << chars2 << std::endl;

	char dStr[] = " d214748364999";
	int d = SortFactory::StrToInt(dStr);
	cout << d << std::endl;

	cout << "===========TreeNode=======================" << endl;

	int btArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	BinaryTreeNode* root = TreeNodeMethods::FromHeapifyArray(btArr, 9, 0);
	TreeNodeMethods::BFS(root, printTreeNode);
	cout << endl;
	TreeNodeMethods::DFS(root, printTreeNode);
	cout << endl;
	vector<int> heapifyVec;
	TreeNodeMethods::ToHeapifyArray(root, heapifyVec);
	Util::PrintVector(heapifyVec, "heapifyVec");



	cout << "===========TreeNode=======================" << endl;

	BinarySearchTree tree = BinarySearchTree();
	tree.PrintAsHeapifyArray();
	for (int i = 0; i < 10; i++)
	{
		tree.Insert(i);
		tree.PrintAsHeapifyArray();
	}

	tree.Delete(2);
	tree.PrintAsHeapifyArray();
	tree.Delete(7);
	tree.PrintAsHeapifyArray();

	BinaryTreeNode* left, * right;
	tree.To2DLinkedNode(left, right);
	BinarySearchTree::PrintAs2DLinkedNode(left);

	cout << "===========LinkedNode=======================" << endl;

	LinkedNode* head = nullptr;
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 1);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 2);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 3);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 2);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 3);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 4); LinkedNodeUtil::Insert(head, 5); LinkedNodeUtil::Insert(head, 6); LinkedNodeUtil::Insert(head, 7); LinkedNodeUtil::Insert(head, 7);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::RemoveDuplication(head);
	LinkedNodeUtil::PrintList(head);

	LinkedNodeUtil::Insert(head, 7);
	LinkedNodeUtil::Insert(head, 2);
	LinkedNodeUtil::Insert(head, 3);
	LinkedNodeUtil::PrintList(head);

	cout << "4 to last: " << LinkedNodeUtil::FindToLast(head, 4)->val << endl;

	cout << "Mid: " << LinkedNodeUtil::FindMidNode(head)->val << endl;

	LinkedNodeUtil::Insert(head, 8);
	LinkedNodeUtil::PrintList(head);
	cout << "Mid: " << LinkedNodeUtil::FindMidNode(head)->val << endl;




	cout << "Is Cycle: " << LinkedNodeUtil::CycleExists(head);

	LinkedNodeUtil::MakeCycle(head, 5);
	LinkedNodeUtil::PrintList(head);

	cout << "Is Cycle: " << LinkedNodeUtil::CycleExists(head) << endl;
	cout << "Cycle Len: " << LinkedNodeUtil::CycleLen(head) << endl;
	cout << "Cycle Entry Val: " << LinkedNodeUtil::GetCycleEntry(head)->val << endl;

	LinkedNode* list1 = LinkedNodeUtil::CreateListFromValues(vector<int>{1,2, 3, 4, 6, 9, 10});
	LinkedNodeUtil::PrintList(list1);

	LinkedNode* list2 = LinkedNodeUtil::CreateListFromValues(vector<int>{2, 5, 6 , 7, 8, 14});
	LinkedNodeUtil::PrintList(list2);

	LinkedNode* mergedList = LinkedNodeUtil::Merge(list1, list2);
	LinkedNodeUtil::PrintList(mergedList);

	LinkedNode* reversedList = LinkedNodeUtil::Reverse(mergedList);
	LinkedNodeUtil::PrintList(reversedList);

	LinkedNode* kReversedList = LinkedNodeUtil::ReverseKGroup(reversedList, 3);
	LinkedNodeUtil::PrintList(kReversedList);

	cout << "===========MaxSumOfSubArr=======================" << endl;
	vector<int> arr{ 1, -2, 3, 10, -4, 7, 2, -5 };
	int MaxSumOfSubArr_Ans = Algos::MaxSumOfSubArr(arr);
	cout << "MaxSumOfSubArr_Ans: " << MaxSumOfSubArr_Ans << endl;
}

void Hanoi(char& a, char& b, char& c, int moveNum, std::map<char, int>& count) {

	if (moveNum == 1) {
		/*c.push(a.top());
		a.pop();*/
		//std::cout << a << " -> " << "c" << std::endl;
		//count[a]--;
		//count[c]++;
	}
	else {
		Hanoi(a, c, b, moveNum - 1, count);
		/*c.push(a.top());
		a.pop();*/
		//std::cout << a << " -> " << "c" << std::endl;
		//count[a]--;
		//count[c]++;
		Hanoi(b, a, c, moveNum - 1, count);
	}
	//std::cout << "moveNum:" << moveNum  << ", A:" << count['A'] << ", B:" << count['B'] << ", C:" << count['C'] << std::endl;
	//PrintHanoi();
}



void printTreeNode(BinaryTreeNode* node) {
	if (node) cout << node->val << ",";
}

bool IsValidString(const char* str, int len) {
	std::stack<char> s;
	char leftChars[] = {'(', '{', '['};
	char rightChars[] = {')', '}', ']'};
	int i = 0;
	while (i < len) {
		switch(str[i]){
		case ')':
			if (s.empty() || s.top() != '(') {
				return false;
			}
			s.pop();
			break;
		case '}':
			if (s.empty() || s.top() != '{') {
				return false;
			}
			s.pop();
			break;
		case ']':
			if (s.empty() || s.top() != '[') {
				return false;
			}
			s.pop();
			break;
		default:
			s.push(str[i]);
		}
		i++;
	}
	return s.empty();
}

// next is filled with 0
void preKMP(const char* pattern, int len, std::vector<int>& next) {
	next[0] = 0;
	for (int i = 1; i < len; i++) {
		int k = next[i - 1];
		while (k >= 0)
		{
			if (pattern[i] == pattern[k])
			{
				next[i] = k + 1;
				break;
			}


			if (k > 0) {
				k = next[k - 1];
			}
			else {
				next[i] = 0;
				break;
			}
		}
	}
}

void KMP(const char* s, int sLen, const char* p, int pLen) {
	std::vector<int> next(pLen, 0);
	preKMP(p, pLen, next);
	std::cout << "[";
	for (int k : next)
	{
		std::cout << k << ",";
	}
	std::cout << "]" << std::endl;

	int j = 0;
	for (int i = 0; i < sLen; i++) {
		if (s[i] == p[j]) {
			j++;
			if (j == pLen) {
				std::cout << i - pLen + 1 << std::endl;
				j = next[pLen - 1];
			}
		}
		else {
			i--;
			if (j > 0) j = next[j - 1];
		}

	}
}

void PrintStack(std::stack<int>& a) {
	std::stack<int> copy(a);
	while (!copy.empty())
	{
		std::cout << copy.top() << ",";
		copy.pop();
	}
	std::cout << std::endl;
}

void PrintHanoi() {
	std::cout << "A:"; PrintStack(A);
	std::cout << "B:"; PrintStack(B);
	std::cout << "C:"; PrintStack(C);
	std::cout << "=====================" << std::endl;
}