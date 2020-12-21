#pragma once

#include "Header.h"

using namespace std;
struct BinaryTreeNode {
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int height;

	BinaryTreeNode(int value, BinaryTreeNode* l, BinaryTreeNode* r) {
		val = value;
		left = l;
		right = r;
		height = 1;
	}
};


typedef void (*TreeNodeHandler) (BinaryTreeNode*);

class TreeNodeMethods {
public:

	static BinaryTreeNode* FromHeapifyArray(int arr[], int len, int i) {
		// iLeftChild = 2 * i + 1,  iRightChild = 2*i + 1
		if (i >= len)return NULL;
		BinaryTreeNode* node = new BinaryTreeNode(arr[i], NULL, NULL);
		if (2 * i + 1 < len) {
			node->left = FromHeapifyArray(arr, len, 2 * i + 1);
			if (2 * 2 + 2 < len) {
				node->right = FromHeapifyArray(arr, len, 2 * i + 2);
			}
		}
		return node;
	}

	static void ToHeapifyArray(BinaryTreeNode* root, vector<int>& arr) {
		queue<BinaryTreeNode*> nodeQ;
		if (root == NULL)return;
		nodeQ.push(root);
		while (!nodeQ.empty()) {
			BinaryTreeNode* curNode = nodeQ.front();
			arr.push_back(curNode->val);
			nodeQ.pop();
			if (NULL != curNode->left)nodeQ.push(curNode->left);
			if (NULL != curNode->right)nodeQ.push(curNode->right);
		}
	}

	static void BFS(BinaryTreeNode* root, TreeNodeHandler handler) {
		queue<BinaryTreeNode*> nodeQ;
		if (root == NULL)return;
		nodeQ.push(root);
		while (!nodeQ.empty()) {
			BinaryTreeNode* curNode = nodeQ.front();
			handler(curNode);
			nodeQ.pop();
			if (NULL != curNode->left)nodeQ.push(curNode->left);
			if (NULL != curNode->right)nodeQ.push(curNode->right);
		}
	}

	static void DFS_stack(BinaryTreeNode* root, TreeNodeHandler handler) {
		if (root == nullptr)return;
		stack<BinaryTreeNode*> s;
		s.push(root);
		s.push(root->right);
		s.push(root->left);

		while (!s.empty()) {
			BinaryTreeNode* node = s.top(); s.pop();
			if (node->right != nullptr) {
				s.push(node->right);
			}
			else if (node->left != nullptr) {
				s.push(node->left);
			}
			handler(node);
		}
	}

	static void DFS(BinaryTreeNode* root, TreeNodeHandler handler) {
		if (root == NULL)return;
		handler(root);
		DFS(root->left, handler);
		DFS(root->right, handler);
	}

	static BinaryTreeNode* lowestCommonAncestorTopDown(BinaryTreeNode* root, BinaryTreeNode* p, BinaryTreeNode* q) {
		if (root == NULL)return NULL;
		if (root == p || root == q)return root;

		BinaryTreeNode* lAncestor = lowestCommonAncestorTopDown(root->left, p, q);
		BinaryTreeNode* rAncestor = lowestCommonAncestorTopDown(root->right, p, q);
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
	BinaryTreeNode* mRoot = NULL;
	static void printTreeNode(BinaryTreeNode* node) {
		if (node) cout << node->val << ",";
	}

	int height(BinaryTreeNode* node) {
		if (NULL == node)return 0;
		return node->height;
	}

	BinaryTreeNode* Exists(BinaryTreeNode* fromNode, int val) {
		if (NULL == fromNode)return NULL;
		if (fromNode->val == val)return fromNode;
		else if (fromNode->val > val) return Exists(fromNode->left, val);
		else return Exists(fromNode->right, val);
	}
	
	BinaryTreeNode* ll_rotate(BinaryTreeNode* node) {
		/*
				A								B					
			   /                               /  \ 
			   B                 ==>          C    A
			  /
			  C
		*/
		if (NULL == node || NULL == node->left)return node;
		BinaryTreeNode* left = node->left;
		node->left = left->right;
		left->right = node;

		node->height = max(height(node->right), height(node->left)) + 1;
		left->height = max(height(left->left), height(left->right)) + 1;

		return left;
	}

	BinaryTreeNode* rr_rotate(BinaryTreeNode* node) {

		/*
				A								   B
			     \                               /   \
			      B                 ==>         A     C
			       \
			        C
		*/
		if (NULL == node || NULL == node->right)return node;
		BinaryTreeNode* right = node->right;
		node->right = right->left;
		right->left = node;

		node->height = max(height(node->left), height(node->right)) + 1;
		right->height = max(height(right->left), height(right->right)) + 1;

		return right;
	}

	BinaryTreeNode* lr_rotate(BinaryTreeNode* node) {
		/*
				A								C
			   /                               /  \
			   B                 ==>          B    A
			    \
			     C
		*/
		if (node == NULL)return NULL;
		node->left = rr_rotate(node->left);
		return ll_rotate(node);
	}

	BinaryTreeNode* rl_rotate(BinaryTreeNode* node) {
		/*
				A								C
			      \                               /  \
				   B                 ==>          B    A
				  /
			     C
		*/
		if (node == NULL)return NULL;
		node->right = ll_rotate(node->right);
		return rr_rotate(node);
	}

	void Insert(BinaryTreeNode* &node, int val) {
		//if equals, drop
		if (node == NULL) {
			node = new BinaryTreeNode(val, NULL, NULL);
			return;
		}
		if (node->val == val)return;

		if (node->val > val) {
			Insert(node->left, val);
		}
		else {
			Insert(node->right, val);
		}

		node->height = max(height(node->left), height(node->right)) + 1;
		int balance = height(node->left) - height(node->right);
		if (balance > 1  && node->left->val > val) { // ll
			node = ll_rotate(node);
		}
		if (balance > 1 && node->left->val < val) { // lr
			node = lr_rotate(node);
		}
		if (balance < -1 && node->right->val > val) { // rl
			node = rl_rotate(node);
		}
		if (balance < -1 && node->right->val < val) { // rr
			node = rr_rotate(node);
		}
	}

	BinaryTreeNode* BalanceTree(BinaryTreeNode* node) {
		int balance = height(node->left) - height(node->right);
		if (balance > 1) {
			if (height(node->left->left) > height(node->left->right))return ll_rotate(node);
			else return lr_rotate(node);
		}
		if (balance < -1) {
			if (height(node->right->right) > height(node->right->left))return rr_rotate(node);
			else return rl_rotate(node);
		}
		return node;
	}

	//return newRoot
	void Delete(BinaryTreeNode* &root, int val, BinaryTreeNode* parent) {
		if (root == NULL)return;
		if (root->val == val) {
			BinaryTreeNode* newRoot = NULL;
			if (NULL == root->left && NULL == root->right) {
				newRoot = NULL;
			}
			else if (NULL == root->left) {
				newRoot = root->right;
			}
			else if (NULL == root->right) {
				newRoot = root->left;
			}
			else {
				BinaryTreeNode* newRootParent = root;
				newRoot = root->left;
				while (newRoot->right != NULL) {
					newRootParent = newRoot;
					newRoot = newRoot->right;
				}

				if(newRoot != root->left)newRoot->left = root->left;
				newRoot->right = root->right;
				newRootParent->right = NULL;
			}
			/*if (parent != NULL) {
				parent->height = max(height(parent->left), height(parent->right)) + 1;
			}*/

			delete root;
			root = newRoot;

			//parent = BalanceTree(parent);
		}
		else if (root->val >= val) {
			Delete(root->left, val, root);
		}
		else {
			Delete(root->right, val, root);
		}
	}

public:
	BinarySearchTree() :mRoot(NULL) {};
	BinarySearchTree(BinaryTreeNode* root) :mRoot(root) {};

	void Insert(int val) {
		return Insert(mRoot, val);
	}

	void Delete(int val) {
		//if leaf, delete directly
		//if only left or right child, delete and move up its only child
		//else move the the max node up to the target

		Delete(mRoot, val, NULL);
	}

	BinaryTreeNode* Exists(int val) {
		return Exists(mRoot, val);
	}

	void PrintAsHeapifyArray() {
		cout << "[";
		TreeNodeMethods::BFS(mRoot, BinarySearchTree::printTreeNode);
		cout << "]";
	}

	void To2DLinkedNode(BinaryTreeNode*& left, BinaryTreeNode*& right) {
		ConvertTo2DLinkedNode(mRoot, left, right);
	}

	static void ConvertTo2DLinkedNode(BinaryTreeNode* root, BinaryTreeNode*& left, BinaryTreeNode*& right) {
		if (root == nullptr) {
			left = nullptr;
			right = nullptr;
			return;
		}

		BinaryTreeNode* l_left = nullptr, * l_right = nullptr;
		ConvertTo2DLinkedNode(root->left, l_left, l_right);

		BinaryTreeNode* r_left = nullptr, * r_right = nullptr;
		ConvertTo2DLinkedNode(root->right, r_left, r_right);

		if (l_left == nullptr) left = root;
		else left = l_left;

		if (r_left == nullptr) right = root;
		else right = r_right;

		if (left != root) { l_right->right = root; root->left = l_right; }
		if (right != root) { root->right = r_left; r_left->left = root; }
	}

	static void PrintAs2DLinkedNode(BinaryTreeNode* root) {
		BinaryTreeNode* cur = root;
		cout << "[";
		while (cur != nullptr) {
			cout << cur->val;
			if (cur->right != nullptr) {
				cout << ",";
				cur = cur->right;
			}
			else break;
		}
		cout << "]" << endl;
	}
};