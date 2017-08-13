#include<bits/stdc++.h>
using namespace std;
const int nax = 1e6 + 11;
long long ans[nax], sieve[nax];
int check[nax];
void ini()
{
	int i, j;
	for(i=1;i<nax;++i)sieve[i]=i;
	for(i=2;i<nax;++i)
		if(sieve[i]==i)
			for(j=i;j<nax;j+=i)
			{
				sieve[j]/=i;
				sieve[j]*=(i-1);
			}
	sieve[1]=0;
	for(i=2;i<nax;++i)
		sieve[i]+=sieve[i-1];
	for(i=1;i<nax;++i)
	{
		long long prev = 0 ;
		for(j=i+i;j<nax;j+=i)
		{
			ans[j]+=i*1LL*(sieve[j/i]-prev);
			prev = sieve[j/i];
		}
	}
	for(i=1;i<nax;++i)
		ans[i]+=ans[i-1];
	
}
int main()
{	
	ini();
	int T=0,N,i;
	for(;scanf("%d",&N);)
	{
		if(!N)return 0;
		printf("%lld\n",ans[N]);
	}
	return 0;
}
