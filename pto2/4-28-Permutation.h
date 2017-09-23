eclipse ../alg/backtrack.cc
vector<string> StringPermutation(string str)
vector<string> StringSubset(const string &str)

class Solution
{
public:
	void StringPermutationMain(string &str, int first, int last, vector<string> &result) // [)
	{
		if(first == last) // End recursive
		{
			result.push_back(str);
			return;
		}
		for(int index = first; index < last; ++index)
		{
			if(index != first && str[first] == str[index]) // Not swap repeated data.
			{
				continue;
			}
			swap(str[first], str[index]);
			StringPermutationMain(str, first + 1, last, result);
			swap(str[first], str[index]); // Pass by reference! Need recover.
		}
	}
	vector<string> Permutation(string str)
	{
		if(str.size() <= 0) // Negative test.
		{
			return vector<string>();
		}
		vector<string> result;
		StringPermutationMain(str, 0, static_cast<int>(str.size()), result);
		return result;
	}
};