#include<bits/stdc++.h>

#define EPS 1e-9

using namespace std;

bool eq(complex<double> a, complex<double> b)
{
	return abs(a-b)<EPS;
}

//O(n log n), dir is +1 for a forward transform and -1 for the inverse
vector< complex<double> > dft(vector< complex<double> > inp, int dir)
{
	int n=inp.size();
	if(n==0 || n==1) return inp;
	vector< complex<double> > par[2];
	for(int i=0;i<n;++i)
	{
		par[i&1].push_back(inp[i]);
	}
	vector< complex<double> > evens=dft(par[0],dir);
	vector< complex<double> > odds=dft(par[1],dir);
	vector< complex<double> > ans;
	int nt=n/2;
	for(int i=0;i<nt;++i)
	{
		ans.push_back(evens[i]+polar(1.0,-dir*2*M_PI*i/n)*odds[i]);
	}
	for(int i=0;i<nt;++i)
	{
		ans.push_back(evens[i]-polar(1.0,-dir*2*M_PI*i/n)*odds[i]);
	}
	return ans;
}


int main()
{
	int n;
	cin>>n;
	vector< complex<double> > inp;
	for(int i=0;i<n;++i)
	{
		double x,y;
		cin>>x>>y;
		inp.push_back(complex<double>(x,y));
	}
	vector< complex<double> > ans=dft(inp,1);
	vector< complex<double> > inv=dft(ans,-1);
	for(int i=0;i<n;++i)
	{
		assert(eq(inv[i]/double(n),inp[i]));
		cout<<ans[i]<<' '<<'\n';
	}
	return 0;
}
