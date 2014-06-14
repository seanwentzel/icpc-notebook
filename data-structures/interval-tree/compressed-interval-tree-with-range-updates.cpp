#include<bits/stdc++.h>

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define f(i,a,b) for(int (i)=(a);(i)<(b);++(i))

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > event;

/*Given an integer-indexed set of values, this structures supports two logarithmic
 * operations: increment all the values in a range by a constant, and return the 
 * maximum value over all the indices. Can leak memory.
 */
class maxtree
{
	int modifier,lo,hi,split;
	maxtree* lh;
	maxtree* rh;
	public:
	int mval;
	maxtree(int l,int h)
	{
		lo=l;
		hi=h;
		split=(l+h)/2;
		modifier=0;
		mval=0;
		lh=NULL;
		rh=NULL;
	}

	void modify(int change,int l,int h)
	{
		if(l<lo) l=lo;
		if(h>hi) h=hi;
		if(l==h) return;
		if(lo==l && hi==h)
		{
			modifier += change;
		}
		else if (l < split && h > split)
		{
			modifier += change;
			modify(-change, lo, l);
			modify(-change, h, hi);
		} 
		else if (h <= split)
		{
			if (lh == NULL) lh = new maxtree(lo, split);
			lh->modify(change, l, h);
		}
		else
		{
			if (rh == NULL) rh = new maxtree(split, hi);
			rh->modify(change, l, h);
		}
		if(lh==NULL && rh==NULL) mval=modifier;
		else if(lh==NULL) mval=modifier+max(0,rh->mval);
		else if(rh==NULL) mval=modifier+max(0,lh->mval);
		else mval=modifier+max(lh->mval,rh->mval);
	}
};

int n,k;
int gi[100005];
int xi[100005];
int yi[100005];
set<event> evs;
int main()
{
	ios_base::sync_with_stdio(false);
	ifstream fin("lazy.in");
	ofstream fout("lazy.out");
	fin>>n>>k;
	f(i,0,n)
	{
		fin>>gi[i]>>xi[i]>>yi[i];
		int tmp=xi[i];
		xi[i]=yi[i]-xi[i];
		yi[i]=yi[i]+tmp;
		evs.insert(mp(xi[i]-k,mp(1,i)));
		evs.insert(mp(xi[i]+k+1,mp(-1,i)));
	}
	int best=0;
	maxtree world(-2500005,2500005);
	event now;
	int circle;
	for(set<event>::iterator it=evs.begin();it!=evs.end();++it)
	{
		now=(*it);
		circle=now.y.y;
		world.modify(now.y.x*gi[circle],yi[circle]-k,yi[circle]+k+1);
		best=max(best,world.mval);
	}
	fout<<best<<endl;
	fin.close();
	fout.close();
	return 0;
}
