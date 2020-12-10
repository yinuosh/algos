#pragma once

#include "Header.h"

using namespace std;
struct BinarayTreeNode {
	int val;
	BinarayTreeNode* left;
	BinarayTreeNode* right;
	int height;

	BinarayTreeNode(int value, BinarayTreeNode* l, BinarayTreeNode* r) {
		val = value;
		left = l;
		right = r;
		height = 1;
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

	static BinarayTreeNode* lowestCommonAncestorTopDown(BinarayTreeNode* root, BinarayTreeNode* p, BinarayTreeNode* q) {
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

	int height(BinarayTreeNode* node) {
		if (NULL == node)return 0;
		return node->height;
	}

	BinarayTreeNode* Exists(BinarayTreeNode* fromNode, int val) {
		if (NULL == fromNode)return NULL;
		if (fromNode->val == val)return fromNode;
		else if (fromNode->val > val) return Exists(fromNode->left, val);
		else return Exists(fromNode->right, val);
	}
	
	BinarayTreeNode* ll_rotate(BinarayTreeNode* node) {
		/*
				A								B					
			   /                               /  \ 
			   B                 ==>          C    A
			  /
			  C
		*/
		if (NULL == node || NULL == node->left)return node;
		BinarayTreeNode* left = node->left;
		node->left = left->right;
		left->right = node;

		node->height = max(height(node->right), height(node->left)) + 1;
		left->height = max(height(left->left), height(left->right)) + 1;

		return left;
	}

	BinarayTreeNode* rr_rotate(BinarayTreeNode* node) {

		/*
				A								   B
			     \                               /   \
			      B                 ==>         A     C
			       \
			        C
		*/
		if (NULL == node || NULL == node->right)return node;
		BinarayTreeNode* right = node->right;
		node->right = right->left;
		right->left = node;

		node->height = max(height(node->left), height(node->right)) + 1;
		right->height = max(height(right->left), height(right->right)) + 1;
	}

	BinarayTreeNode* lr_rotate(BinarayTreeNode* node) {
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

	BinarayTreeNode* rl_rotate(BinarayTreeNode* node) {
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

	BinarayTreeNode* Insert(BinarayTreeNode* node, int val) {
		//if equals, drop
		if (node == NULL)node = new BinarayTreeNode(val, NULL, NULL);
		if (node->val == val)return node;;
		if (node->val > val) {
			node->left = Insert(node->left, val);
		}
		else {
			node->right = Insert(node->right, val);
		}

		node->height = max(height(node->left), height(node->right)) + 1;
		int balance = height(node->left) - height(node->right);
		if (balance > 1  && node->left->val > val) { // ll
			return ll_rotate(node);
		}
		if (balance > 1 && node->left->val < val) { // lr
			return lr_rotate(node);
		}
		if (balance < -1 && node->right->val > val) { // rl
			return rl_rotate(node);
		}
		if (balance < -1 && node->right->val < val) { // rr
			return rr_rotate(node);
		}

		return node;
	}

	BinarayTreeNode* BalanceTree(BinarayTreeNode* node) {
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
	BinarayTreeNode* Delete(BinarayTreeNode* root, int val, BinarayTreeNode* parent, bool left) {
		if (root == NULL)return NULL;
		if (root->val == val) {
			BinarayTreeNode* newRoot = NULL;
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
				BinarayTreeNode* newRootParent = root;
				newRoot = root->left;
				while (newRoot->right != NULL) {
					newRootParent = newRoot;
					newRoot = newRoot->right;
				}
				if (newRoot != root->left)newRootParent->right = NULL;
			}
			if (parent != NULL) {
				if (left)parent->left = newRoot;
				else parent->right = newRoot;
				parent->height = max(height(parent->left), height(parent->right)) + 1;
			}
			delete root;
			root = NULL;

			parent = BalanceTree(parent);

			return newRoot;
		}
		else if (root->val >= val) return Delete(root->left, val, root, true);
		else return Delete(root->right, val, root, false);
	}

public:
	BinarySearchTree() :mRoot(NULL) {};
	BinarySearchTree(BinarayTreeNode* root) :mRoot(root) {};

	bool Insert(int val) {
		if (mRoot == NULL){
			mRoot = new BinarayTreeNode(val, NULL, NULL);
			return true;
		}
		return Insert(mRoot, val);
	}

	void Delete(int val) {
		//if leaf, delete directly
		//if only left or right child, delete and move up its only child
		//else move the the max node up to the target

		BinarayTreeNode* replacement = Delete(mRoot, val, NULL, false);
		if (NULL == mRoot)mRoot = replacement;
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