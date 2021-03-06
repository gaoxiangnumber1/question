#include "../common_system_header.h"
// Assume all inputs are valid. Assume n is the number of elements to be sorted.
// TC: Best = O(n^2), Average = O(n^2), Worst = O(n^2)
// SC: O(1)
void SelectionSort(int *data, int first, int last)
{
	// [first, first_unsorted) is sorted, [first_unsorted, last) is unsorted.
	for(int first_unsorted = first; first_unsorted < last - 1; ++first_unsorted)
	{
		int min_index = first_unsorted;
		for(int compare_index = first_unsorted + 1; compare_index < last;
			++compare_index)
		{
			if(data[min_index] > data[compare_index])
			{
				min_index = compare_index;
			}
		}
		if(min_index != first_unsorted)
		{
			swap(data[min_index], data[first_unsorted]);
		}
		// One more element is sorted:
		// [first, first_unsorted + 1) is sorted, [first_unsorted + 1, last) is unsorted.
	}
}
/////////////////////////////////////////////
// TC: Best = O(n), Average = O(n^2), Worst = O(n^2)
// SC: O(1)
void BubbleSort(int *data, int first, int last) // [first, last)
{
	// [first, first_sorted) is unsorted, [first_sorted, last) is sorted.
	for(int first_sorted = last; first_sorted != first;)
	{
		int last_swap_latter_index = first;
		// Traverse [first, first_sorted)
		for(int latter_index = first + 1; latter_index < first_sorted;
			++latter_index)
		{
			if(data[latter_index - 1] > data[latter_index])
			{
				swap(data[latter_index - 1], data[latter_index]);
				last_swap_latter_index = latter_index;
			}
		}
		// [first, last_swap_latter_index) is unsorted, [last_swap_latter_index, last) is sorted.
		first_sorted = last_swap_latter_index;
	}
}
/////////////////////////////////////////////
// TC: Best = O(n), Average = O(n^2), Worst = O(n^2)
// SC: O(1)
void InsertionSort(int *data, int first, int last)
{
	// [first, first_unsorted) is sorted, [first_unsorted, last) is unsorted.
	for(int first_unsorted = first + 1; first_unsorted < last; ++first_unsorted)
	{
		for(int compare_index = first_unsorted;
			compare_index - 1 >= first
				&& data[compare_index - 1] > data[compare_index]; --compare_index)
		{
			swap(data[compare_index - 1], data[compare_index]);
		}
		// One more element is sorted.
		// [first, first_unsorted + 1) is sorted; [first_unsorted + 1, last) is unsorted.
	}
}
void ShellSort(int *data, int first, int last)
{
	for(int gap = (last - first) / 2; gap > 0; gap /= 2)
	{
		for(int first_sorted = first; first_sorted < first + gap; ++first_sorted)
		{
			for(int first_unsorted = first_sorted + gap; first_unsorted < last;
				first_unsorted += gap)
			{
				for(int compare_index = first_unsorted;
					compare_index - gap >= first
						&& data[compare_index - gap] > data[compare_index];
					compare_index -= gap)
				{
					swap(data[compare_index - gap], data[compare_index]);
				}
			}
		}
	}
}
/////////////////////////////////////////////
int Partition2(int *data, int first, int last) // O(n)
{
	int pivot = data[first];
	int divide = last - 1;
	for(int index = last - 1; index > first; --index)
	{
		if(data[index] > pivot)
		{
			data[index] != data[divide] ? swap(data[index], data[divide]) : void(0);
			--divide;
		}
	}
	data[divide] != data[first] ? swap(data[divide], data[first]) : void(0);
	return divide;
}
int Partition(int *data, int first, int last) // O(n)
{
	int pivot = data[first], divide = first + 1;
	for(int index = first + 1; index < last; ++index)
	{
		if(data[index] <= pivot)
		{
			data[index] != data[divide] ? swap(data[index], data[divide]) : void();
			++divide;
		}
	}
	data[--divide] != data[first] ? swap(data[divide], data[first]) : void();
	return divide;
}
// TC: Best = O(nlogn), Average = O(nlogn), Worst = O(n^2)
// SC: Best = O(logn), Worst = O(n)
void QuickSort(int *data, int first, int last) // [first, last)
{
	if(last - first <= 1) // Only one element is auto sorted.
	{
		return;
	}
	// Divide: [first, divide) <= [divide, divide + 1) < [divide + 1, last)
	int divide = Partition(data, first, last);
	// Conquer: sort [first, divide) and [divide + 1, last) by recursive calls.
	QuickSort(data, first, divide);
	QuickSort(data, divide + 1, last);
	// Combine: sub arrays are sorted, no work is needed to combine them.
}
void QuickSortLinkedList()
{
	// ../ds/linked_list.cc
}
/////////////////////////////////////////////
void Merge(int *data, int first, int middle, int last, int *helper) // O(n)
{
	int left = first; // index in left-subrange [first, middle).
	int right = middle; // index in right-subrange [middle, last).
	int helper_index = first; // index in helper.
	while(left < middle || right < last)  // Either subrange is not empty
	{
		// Copy left element into helper when:
		// 1.	Left subrange is not empty and right subrange is empty:
		//		`left < middle && right >= last`
		// 2.	Both are not empty and left element is lesser than or equal to right element:
		//		`left < middle && right < last && data[left] <= data[right]`
		// NOTE:
		// 1. `||` is short-circuit.
		// 2. `<=` keep the relative order of equal elements, thus guarantee sorting stability.
		if(right >= last || (left < middle && data[left] <= data[right]))
		{
			helper[helper_index++] = data[left++];
		}
		else
		{
			helper[helper_index++] = data[right++];
		}
	}
	// Copy sorted elements into data.
	for(int index = first; index < last; ++index)
	{
		data[index] = helper[index];
	}
}
void MergeSortMain(int *data, int first, int last, int *helper)
{
	if(last - first <= 1) // Only 1 element is auto sorted.
	{
		return;
	}
	// Divide: divide n-element array into two n/2-element subarrays.
	int middle = first + (last - first) / 2;
	// Conquer: sort two subarrays [first, middle) and [middle, last) recursively.
	MergeSortMain(data, first, middle, helper);
	MergeSortMain(data, middle, last, helper);
	// Combine: merge two sorted subarrays.
	Merge(data, first, middle, last, helper);
}
// TC: Best = O(nlogn), Average = O(nlogn), Worst = O(nlogn)
// SC: O(n)
void MergeSort(int *data, int first, int last) // [first, last)
{
	int helper[last]; // helper temporary stores the sorted subarrays in Merge.
	MergeSortMain(data, first, last, helper);
}
void MergeSortLinkedList()
{
	// ../ds/linked_list.cc
}
/////////////////////////////////////////////
void FixDown(int *data, int parent_index, int length)
{
	int max_child_index = parent_index * 2 + 1;
	while(max_child_index < length)
	{
		if(max_child_index + 1 < length
			&& data[max_child_index] < data[max_child_index + 1])
		{
			++max_child_index;
		}
		if(data[parent_index] >= data[max_child_index]) // `=` guarantee stable.
		{
			return;
		}
		swap(data[parent_index], data[max_child_index]);
		parent_index = max_child_index;
		max_child_index = parent_index * 2 + 1;
	}
}
// TC: Best = O(nlogn), Average = O(nlogn), Worst = O(nlogn)
// SC: O(1)
void HeapSort(int *data, int first, int last)
{
	// 1. Convert to max heap. O(nlogn). (Tight is O(n), see ITA $6.3).
	int length = last - first;
	data += first; // [first, last) -> [0, length)
	for(int parent_index = length / 2 - 1; parent_index >= 0; --parent_index)
	{
		FixDown(data, parent_index, length);
	}
	// 2. Extract maximum. O(nlogn)
	for(int now_length = length - 1; now_length > 0; --now_length)
	{
		if(data[0] != data[now_length])
		{
			swap(data[0], data[now_length]);
			FixDown(data, 0, now_length);
		}
	}
}
/////////////////////////////////////////////
// Assume all numbers are in [0, max]
// n is the number of inputs, m is the max value.
// TC: Best = Average = Worst = O(n + m)
// SC: O(n + m)
void CountingSort(int *data, int first, int last) // [first, last)
{
	int length = last - first;
	data += first;
	// Get the maximum value.
	int max = 0;
	for(int index = 0; index < length; ++index)
	{
		max < data[index] ? max = data[index] : max;
	}
	vector<int> count(max + 1, 0); // count[value] is the count of elements that are <= value.
	// Count the frequency of every value in data.
	for(int index = 0; index < length; ++index)
	{
		++count[data[index]]; // WRONG: count[data[index]] = 1
	}
	// Compute how many elements are <= value.
	for(int value = 1; value <= max; ++value)
	{
		count[value] += count[value - 1];
	}
	// 1. x elements <= value: place value in [x - 1].
	// 2. Place from back to front: keep stability.
	int temp[length]; // Temporary store the sorted elements.
	for(int index = length - 1; index >= 0; --index)
	{
		temp[--count[data[index]]] = data[index];
	}
	// Copy the sorted elements into data.
	for(int index = 0; index < length; ++index)
	{
		data[index] = temp[index];
	}
}
/////////////////////////////////////////////
// n is the number of inputs, d is the number of digits, m is the max value in each digit.
// TC: Best = Average = Worst = O(d(n + m))
// SC: O(n + m)
void RadixSort(int *data, int first, int last)
{
	const int kMaxDigitValue = 9;
	const int kDigitValueNumber = kMaxDigitValue + 1;
	const int kMaxDigitNumber = 10; // 10^10 < 2^31 < 10^11, thus has at most 10 digits.
	data += first;
	int length = last - first;
	int divisor = 1;
	for(int digit = 1; digit <= kMaxDigitNumber; ++digit)
	{
		int digit_number[length];
		vector<int> count(kDigitValueNumber, 0);
		// Get each digit number from least to most significant digit.
		for(int index = 0; index < length; ++index)
		{
			digit_number[index] = (data[index] / divisor) % kDigitValueNumber;
			++count[digit_number[index]];
		}
		for(int value = 1; value <= kMaxDigitValue; ++value)
		{
			count[value] += count[value - 1];
		}
		int temp[length];
		for(int index = length - 1; index >= 0; --index)
		{
			// Sort according to digit_number, but store data.
			temp[--count[digit_number[index]]] = data[index];
		}
		for(int index = 0; index < length; ++index)
		{
			data[index] = temp[index];
		}
		// Update divisor to get the next digit_number.
		divisor *= kDigitValueNumber;
	}
}
/////////////////////////////////////////////
void PrintData(int *data, int first, int last)
{
	printf("%d", data[first]);
	for(int index = first + 1; index < last; ++index)
	{
		printf(" %d", data[index]);
	}
	printf("\n");
}
using SortFunction = void(*)(int*, int, int);
void TestSortAlgorithm(const char *name, SortFunction Sort)
{
	printf("-----Test%s-----\n", name);
	int number_count = 10;
	for(int first = 0; first <= number_count; ++first)
	{
		vector<vector<int>> test1 = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 9, 8, 7, 6,
			5, 4, 3, 2, 1, 0 }, { 0, 2, 4, 6, 8, 9, 7, 5, 3, 1 } };
		vector<vector<int>> test2 = test1;
		for(int index = 0; index < static_cast<int>(test1.size()); ++index)
		{
			Sort(test1[index].data(), first, number_count);
			sort(test2[index].data() + first, test2[index].data() + number_count);
			for(int i = 0; i < number_count; ++i)
			{
				assert(test1[index][i] == test2[index][i]);
			}
		}
	}
	printf("All case pass.\n");
}
/////////////////////////////////////////////
string SortArrayToMinNumber(const vector<int> &arr)
{
	return "";
}
void TestSortArrayToMinNumber()
{
	printf("-----TestSortArrayToMinNumber-----\n");
	vector<vector<int>> arr { {},/*Negative test*/{ 123 }, { 1, 1, 10 },/*Edge test*/
	{ 4, 5, 6, 40, 56, 666, 410, 59, 600, 44, 516, 671, 45, 508, 6 } };
	vector<string> answer { "", "123", "1011", "40410444455085165565960066666671" };
	for(int index = 0; index < static_cast<int>(arr.size()); ++index)
	{
		assert(SortArrayToMinNumber(arr[index]) == answer[index]);
	}
	printf("All case pass.\n");
}
//////////////////////////////////////////////////////////////////////
int main()
{
	TestSortAlgorithm("SelectionSort", SelectionSort);
	TestSortAlgorithm("BubbleSort", BubbleSort);
	TestSortAlgorithm("InsertionSort", InsertionSort);
	TestSortAlgorithm("ShellSort", ShellSort);
	TestSortAlgorithm("QuickSort", QuickSort);
	TestSortAlgorithm("MergeSort", MergeSort);
	TestSortAlgorithm("HeapSort", HeapSort);
	TestSortAlgorithm("CountingSort", CountingSort);
	TestSortAlgorithm("RadixSort", RadixSort);
	TestSortArrayToMinNumber();
}
