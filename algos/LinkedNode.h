#pragma once
struct LinkedNode
{
	int val;
	LinkedNode* next;

	LinkedNode(int v, LinkedNode* n) :val(v), next(n) {

	}
};

class LinkedNodeUtil {
public:
	static void Insert(LinkedNode*& list, int val) {
		if (nullptr == list) {
			list = new LinkedNode(val, nullptr);
			return;
		}
		if (val <= list->val) {
			LinkedNode* newNode = new LinkedNode(val, list);
			list = newNode;
			return;
		}

		LinkedNode* cur = list;

		while (nullptr != cur->next) {
			if (val <= cur->next->val) {
				LinkedNode* newNode = new LinkedNode(val, cur->next);
				cur->next = newNode;
				return;
			}
			else {
				cur->next;
			}
		}

		//Reach to end
		cur->next = new LinkedNode(val, nullptr);
	}

	static void Remove(LinkedNode*& list, int val) {
		if (nullptr == list)return;
		if (list->val == val) {
			LinkedNode* removingNode = list;
			list = list->next;
			delete removingNode;
			return;
		}

		LinkedNode* cur = list;

		while (nullptr != cur->next) {
			if (cur->next->val == val) {
				LinkedNode* toBeRemove = cur->next;
				cur->next = cur->next->next;
				delete toBeRemove;
				return;
			}
			else if (cur->next->val > val)break;
		}
	}

	static void RemoveDuplication(LinkedNode*& list) {
		bool bNextDup = false;
		LinkedNode* head = new LinkedNode(0, list);
		LinkedNode* cur = head;

		while (nullptr != cur->next) {
			if (nullptr != cur->next->next) {
				if (cur->next->val == cur->next->next->val) {
					LinkedNode* toBeDeleted = cur->next->next;
					cur->next->next = toBeDeleted->next;
					delete toBeDeleted;
					bNextDup = true;
				}
				else {
					if (bNextDup) {
						LinkedNode* toBeDeleted = cur->next;
						cur->next = cur->next->next;
						delete toBeDeleted;
					}
					else {
						cur->next = cur->next->next;
					}
					bNextDup = false;
				}
			}
		}

		if (bNextDup) {
			LinkedNode* toBeDeleted = cur->next;
			cur->next = nullptr;
			delete toBeDeleted;
		}

		list = head->next;
	}

	static bool CycleExists(LinkedNode* list) {
		if (nullptr == list || nullptr == list->next)return false;
		LinkedNode* pSlow = list;
		LinkedNode* pFast = list->next;

		while (nullptr != pFast) {
			if (pSlow == pFast) {
				return true;
			}
			pSlow = pSlow->next;
			if (nullptr != pFast->next) {
				pFast = pFast->next->next;
			}
			else {
				break;
			}
		}
		return false;
	}

};