#include "SortFactory.h"

void SortFactory::QuickSort(int data[], int len)
{
	Util::PrintIntArray(data, len, "Before sort");
	QuickSort2(data, 0, len - 1);
	Util::PrintIntArray(data, len, "After sort");
}

void SortFactory::QuickSort(int data[], int start, int end)
{
	Util::PrintIntArray(data, start, end);
	if (start < end) {
		int pivotIndex = start;
		int pivotValue = data[end];
		
		std::cout << "p:" << pivotValue << ", " << pivotIndex << "," << start << "," << end << std::endl;
		for (int i = start; i < end; i++) {
			if (data[i] < pivotValue){
				std::cout << data[i] << "<->" << data[pivotIndex] << std::endl;
				Util::Swap(data, i, pivotIndex);				
				pivotIndex++;
			}
		}
		Util::Swap(data, pivotIndex, end);
		QuickSort(data, start, pivotIndex-1);
		QuickSort(data, pivotIndex+1, end);
	}
}

void SortFactory::QuickSort2(int data[], int low, int hi)
{
	if (low < hi) {
		int pivot = data[(hi + low) / 2];
		int i = low;
		int j = hi;
		while (true) {
			while (data[i] < pivot)i++;
			while (data[j] > pivot)j--;
			if (i >= j) {
				QuickSort2(data, low, j);
				QuickSort2(data, j + 1, hi);
				break;
			};
			Util::Swap(data, i, j);
			i++;
			j--;
		}
		

	}
}

void SortFactory::MergeSort(int data[], int len) {
	Util::PrintIntArray(data, len, "Before sort");
	int cache[256];
	Util::CopyIntArr(data, cache, len);
	MergeSort_Rur(cache, 0, len, data);
	//Util::CopyIntArr(cache, data, len);
	Util::PrintIntArray(data, len, "After sort");
}

void SortFactory::HeapSort(int data[], int len)
{
	Heapify(data, len);

	int end = len - 1;
	while (end > 0) {
		Util::Swap(data, 0, end);
		end--;
		SiftDown(data, 0, end);
	}
}

void SortFactory::BubbleSort(int data[], int len)
{
	int lastBubble = len;
	while (lastBubble > 1) {
		int end = lastBubble;
		lastBubble = 0;
		for (int i = 1; i < end; i++) {
			if (data[i - 1] > data[i]) {
				Util::Swap(data, i - 1, i);
				lastBubble = i;
			}
		}
	}
}

std::vector<int> SortFactory::SearchStringKMP(const char* s, int sLen, const char* p, int pLen)
{
	std::vector<int> result;

	//Build KMP array from p
	std::vector<int> next(pLen, 0);
	for (int i = 1; i < pLen; i++) {
		int k = next[i - 1];

		while (true) {
			if (p[i] == p[k]) {
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

	int k = 0; // p index
	for (int i = 0; i < sLen; i++) {
		if (s[i] == p[k]) {
			k++;
			if (k == pLen) {
				result.push_back(i - pLen + 1);
				k = next[pLen - 1];
			}
		}
		else {		
			if (k > 0) {
				k = next[k - 1];
				i--;
			}
		}
	}
	return result;
}



void SortFactory::LeftRotateString(char* s, int n, int m)
{
	ReverseString(s, 0, m-1);
	ReverseString(s, m, n-1);
	ReverseString(s, 0, n - 1);
}

void SortFactory::ReverseString(char* s, int from, int to)
{
	while (from < to) {
		char t = s[from];
		s[from] = s[to];
		s[to] = t;
		from++;
		to--;
	}
}

void SortFactory::MergeSort_Rur(int data[], int low, int hi, int cache[]) {
	if (hi - low <= 1)return;

	int mid = low + (hi - low) / 2;

	MergeSort_Rur(cache, low, mid, data);
	MergeSort_Rur(cache, mid, hi, data);

	int i = low;
	int j = mid;
	for (int k = low; k < hi; k++) {
		if (i < mid && (j >= hi || data[i] <= data[j])) {
			cache[k] = data[i];
			i++;
		}
		else {
			cache[k] = data[j];
			j++;
		}
	}
}

int SortFactory::iParent(int i)
{
	return (i - 1) / 2;
}

int SortFactory::iLeftChild(int i)
{
	return 2 * i + 1;
}

int SortFactory::iRightChild(int i)
{
	return 2 * i + 2;
}

void SortFactory::SiftDown(int data[], int start, int end)
{
	int root = start;
	
	while (iLeftChild(root) <= end) {
		int swap = root;
		int left = iLeftChild(root);
		if (data[left] > data[swap]) swap = left;
		if (left + 1 <= end && data[left + 1] > data[swap]) swap = left + 1; // right child
		if (root == swap) return; //no swap need
		else {
			Util::Swap(data, root, swap);
			root = swap;;
		}
	}
}

void SortFactory::Heapify(int data[], int len)
{
	for (int k = iParent(len - 1); k >= 0; k--) {
		SiftDown(data, k, len - 1);
	}
}
