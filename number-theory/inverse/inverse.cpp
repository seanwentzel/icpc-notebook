using namespace std;
int inv(int x, int a, int y, int b)
{
	if(x==1) return a;
	if(y==0) return 0;
	return inv(y,b,x%y,a-b*(x/y));
}
