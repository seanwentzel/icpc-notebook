#include<bits/stdc++.h>

using namespace std;

vector<int> jump_table(vector<int> needle)
{
	vector<int> ans(needle.size(), 0);
	ans[0] = -1;
	int at = 1;
	int match_len= 0;
	while(at < needle.size())
	{
		if(needle[at] == needle[match_len])
		{
			++at;
			++match_len;
			ans[at]=match_len;
		}
		else if(match_len > 0)
		{
			match_len=ans[match_len];
		}
		else
		{
			match_len=0;
			at++;
		}
	}
	return ans;
}

//finds all matches of needle in haystack in O(n+m)
vector<int> kmp(vector<int> needle, vector<int> haystack)
{
	vector<int> jump = jump_table(needle);
	vector<int> ans;
	int pos = 0;
	int match_len = 0;
	while(true)
	{
		if(match_len == needle.size())
		{
			ans.push_back(pos - needle.size());
			match_len = 0;
			//return here to get only first match
		}
		if(pos == haystack.size())
		{
			return ans;
		}
		if(haystack[pos] == needle[match_len])
		{
			++pos;
			++match_len;
		}
		else if(jump[match_len] >= 0)
		{
			match_len = jump[match_len];
		}
		else
		{
			match_len = 0;
			++pos;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	vector<int> needle, haystack;
	for(int i=0;i<n;++i)
	{
		int tmp;
		cin>>tmp;
		needle.push_back(tmp);
	}
	for(int i=0;i<m;++i)
	{
		int tmp;
		cin>>tmp;
		haystack.push_back(tmp);
	}
	vector<int> ans=kmp(needle,haystack);
	for(int i=0;i<ans.size();++i)
	{
		cout<<ans[i]<<'\n';
	}
	return 0;
}
