#pragma once
#include <iostream>
#include <vector>

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

	static LinkedNode* FindToLast(LinkedNode* head, int k) {
		LinkedNode* p1 = head;
		int cur = 0;
		while (p1 != nullptr && cur < k) {
			cur++;
			p1 = p1->next;
		}

		//total nodes less than k, return null pointer.
		if (cur != k) {
			return nullptr;
		}

		LinkedNode* p2 = head;
		while (p1 != nullptr) {
			p1 = p1->next;
			p2 = p2->next;
		}

		return p2;
	}

	static LinkedNode* FindMidNode(LinkedNode* head) {
		if (head == nullptr)return nullptr;
		
		LinkedNode* fast = head->next;
		LinkedNode* slow = head;

		while (true) {
			if (fast->next == nullptr) {				
				break;
			}
			else if (fast->next->next == nullptr) {
				slow = slow->next;
				break;
			}

			fast = fast->next->next;
			slow = slow->next;
		}

		return slow;
	}

	static LinkedNode* Merge(LinkedNode* list1, LinkedNode* list2) {
		if (list1 == nullptr)return list2;
		if (list2 == nullptr)return list1;

		LinkedNode* head = new LinkedNode(-1, nullptr);
		LinkedNode* cur = head;

		while (true) {
			if (list1 == nullptr && list2 == nullptr) {
				break;
			}
			else if (list1 == nullptr) {
				cur->next = list2;
				break;
			}
			else if (list2 == nullptr) {
				cur->next = list1;
			}
			else {
				if (list1->val <= list2->val) {
					cur->next = list1;
					list1 = list1->next;
				}
				else {
					cur->next = list2;
					list2 = list2->next;
				}
				cur = cur->next;
				cur->next = nullptr;
			}
		}

		return head->next;
	}

	static LinkedNode* CreateListFromValues(std::vector<int> vals) {
		if (vals.empty())return nullptr;
		LinkedNode* head = new LinkedNode(vals[0], nullptr);
		for (int i = 1; i < vals.size(); i++) {
			Insert(head, vals[i]);
		}
		return head;
	}

	static LinkedNode* Reverse(LinkedNode* list) {
		if (list == nullptr)return nullptr;

		LinkedNode* newHead = new LinkedNode(-1, nullptr);

		while (list != nullptr) {			
			LinkedNode* node = list;
			list = list->next;

			node->next = newHead->next;
			newHead->next = node;
		}

		return newHead->next;
	}

	static LinkedNode* ReverseKGroup(LinkedNode* list, int k) {
		LinkedNode* head = new LinkedNode(-1, nullptr);
		LinkedNode* groupHead = list;
		LinkedNode* groupEnd = nullptr;		

		while (groupHead != nullptr){
			LinkedNode* groupCur = groupHead;
			int count = 0;
			while (groupCur != nullptr) {
				count++;
				if (count == k || groupCur->next == nullptr) {
					break;
				}
				groupCur = groupCur->next;
			}
			groupEnd = groupCur;

			LinkedNode* nextGroupHead = groupEnd->next;

			groupEnd->next = head->next;
			head->next = groupHead;

			groupHead = nextGroupHead;
			groupEnd = nullptr;
		}

		//debug
		PrintList(head);

		return Reverse(head->next);
	}
};