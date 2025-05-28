#include <iostream>
#include <vector>

using namespace std;

/* Enum of SortOrder */
enum class SortOrder {
	Ascending = 1,
	Descending = 2
};

/* return sum of vector */
int GetSum(const vector<int>& vec) {
	int sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum += vec[i];
	}
	return sum;
}

/* return average of vector */
float GetAvg(const vector<int>& vec) {
	return (float)GetSum(vec) / vec.size();
}

/* Merge and Sort Left and Right vec */
void Merge(vector<int>& vec, int left, int mid, int right, bool isAscending) {
	vector<int> tmp(right - left + 1);					// need additional space : O(N)
	int i = left, j = mid + 1, k = 0;

	while (i <= mid && j <= right) {
		if (isAscending && (vec[i] <= vec[j])			// Ascending Order
			|| (!isAscending) && (vec[i] >= vec[j])) {	// OR Descending Order
			tmp[k++] = vec[i++];						// Copy Left elem to tmp[]
		}
		else {
			tmp[k++] = vec[j++];						// Copy Right elem to tmp[]
		}
	}

	while (i <= mid) {									// Copy Remain Left elem to tmp[]
		tmp[k++] = vec[i++];
	}
	while (j <= right) {								// Copy Remain Right elem to tmp[]
		tmp[k++] = vec[j++];
	}

	for (int idx = 0; idx < tmp.size(); idx++) {		// Copy tmp[] to vec[]
		vec[left + idx] = tmp[idx];
	}
}

/* Recursive call(Divide & Conquer) */
void MergeSortRecursive(vector<int>& vec, int left, int right, bool isAscending) {
	if (left >= right) {
		return;
	}

	int mid = (left + right) / 2;
	MergeSortRecursive(vec, left, mid, isAscending);
	MergeSortRecursive(vec, mid+1, right, isAscending);
	Merge(vec, left, mid, right, isAscending);
}

/* Mergesort, default sort = Ascending */
void MergeSort(vector<int>& vec, SortOrder sortOrder = SortOrder::Ascending) {
	if (sortOrder == SortOrder::Ascending) {
		MergeSortRecursive(vec, 0, vec.size() - 1, true);
	}
	else {
		MergeSortRecursive(vec, 0, vec.size() - 1, false);
	}
}

/* Print All elements */
void PrintVector(const vector<int>& vec) {
	for (int elem : vec) {
		cout << elem << " ";
	}
	cout << "\n";
}

int main() {
	vector<int> inputs(5);

	printf("Please Enter 5 numbers\n");

	// Get 5 User Input
	for (int i = 0; i < inputs.size(); i++) {
		cin >> inputs[i];
	}

	// Print Sum, Avg
	printf("Sum : %d, Avg : %.2f\n\n", GetSum(inputs), GetAvg(inputs));

	// Ascending = 1, Descending = 2
	printf("Please Set Sort Order(1: Ascending(Default), 2:Descending)\n");
	int userSortOrder;
	cin >> userSortOrder;

	// Do Merge Sort O(nlogn), O(n)
	if (userSortOrder == 2) {
		MergeSort(inputs, SortOrder::Descending);
	}
	else {
		MergeSort(inputs);
	}

	// Print Inputs
	PrintVector(inputs);
	
	return 0;
}