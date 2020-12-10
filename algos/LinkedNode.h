#pragma once
#include <iostream>
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
		if (val < list->val) {
			LinkedNode* newNode = new LinkedNode(val, list);
			list = newNode;
			return;
		}

		LinkedNode* cur = list;

		while (nullptr != cur->next) {
			if (val < cur->next->val) {
				LinkedNode* newNode = new LinkedNode(val, cur->next);
				cur->next = newNode;
				return;
			}
			else {
				cur = cur->next;
			}
		}

		//Reach to end
		cur->next = new LinkedNode(val, nullptr);
	}

	static void RemoveFirst(LinkedNode*& list, int val) {
		if (nullptr == list)return;
		if (list->val == val) {
			LinkedNode* toBeRemoved = list;
			list = list->next;
			delete toBeRemoved;
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

		while (nullptr != cur->next && nullptr != cur->next->next) {
			if (cur->next->val == cur->next->next->val) {
				LinkedNode* toBeDeleted = cur->next->next;
				cur->next->next = toBeDeleted->next;
				delete toBeDeleted;
				bNextDup = true;
				continue;
			}
			else {
				if (bNextDup) {
					LinkedNode* toBeDeleted = cur->next;
					cur->next = cur->next->next;
					delete toBeDeleted;
					bNextDup = false;
					continue;
				}
				cur = cur->next;
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

	static int CycleLen(LinkedNode* list) {
		if (nullptr == list || nullptr == list->next)return 0;
		LinkedNode* pSlow = list;
		LinkedNode* pFast = list->next;

		while (nullptr != pFast) {
			if (pSlow == pFast) {
				int cLen = 1;
				pSlow = pSlow->next;
				pFast = pFast->next->next;
				while (pSlow != pFast) {
					pSlow = pSlow->next;
					pFast = pFast->next->next;
					cLen++;
				}
				return cLen;
			}
			pSlow = pSlow->next;
			if (nullptr != pFast->next) {
				pFast = pFast->next->next;
			}
			else {
				break;
			}
		}
		return 0;
	}

	static LinkedNode* GetCycleEntry(LinkedNode* list) {
		if (nullptr == list || nullptr == list->next)return nullptr;
		LinkedNode* pSlow = list;
		LinkedNode* pFast = list->next;

		while (nullptr != pFast) {
			if (pSlow == pFast) {
				pSlow = pSlow->next;
				LinkedNode* pSlow1 = list;
				while (pSlow != pSlow1) {
					pSlow = pSlow->next;
					pSlow1 = pSlow1->next;
				}
				return pSlow;
			}
			pSlow = pSlow->next;
			if (nullptr != pFast->next) {
				pFast = pFast->next->next;
			}
			else {
				break;
			}
		}
		return nullptr;
	}

	static void PrintList(LinkedNode* list) {
		LinkedNode* cycleEntry = GetCycleEntry(list);
		bool entryPrinted = false;

		std::cout << "[";
		while (list != nullptr) {
			if (nullptr != cycleEntry) {
				if (entryPrinted) {
					std::cout << "...";
					break;
				}
				else {
					entryPrinted = true;
				}
			}
			std::cout << list->val;
			if (list->next != nullptr) {
				std::cout << ", ";
			}
			list = list->next;
		}
		std::cout << "]" << std::endl;
	}


	static void MakeCycle(LinkedNode* list, int entryVal) {
		if (nullptr == list)return;

		LinkedNode* entryNode = nullptr;
		while (nullptr != list->next) {
			if (list->val == entryVal) {
				entryNode = list;
			}
			list = list->next;
		}
		if (entryNode != nullptr)list->next = entryNode;
	}
};