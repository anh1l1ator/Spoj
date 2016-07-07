#define Max 2001

vector < vector < vector < vector < int > > > > dp(15 ,
vector < vector < vector < int > > >(15,
vector < vector < int > >(Max,
vector < int >(Max))));

struct WTF
{
    int LG[Max+1];

    void ini(int N)
    {
        
        LG[1]=0;
        LG[0]=-1e9;
        int i , j , k , l ;
        for(i=2;i<=Max;++i)LG[i]=LG[i/2]+1;
        for(j=1;(1<<j)<=N;++j)
            for(k=1;k<=N;++k)
                for(l=1;l+(1<<j)-1<=N;++l)
                        dp[0][j][k][l] = max(dp[0][j-1][k][l],dp[0][j-1][k][l+(1<<j-1)]);
        for(i=1;(1<<i)<=N;++i)
            for(k=1;k+(1<<i)-1<=N;++k)
                for(l=1;l<=N;++l)
                        dp[i][0][k][l] = max(dp[i-1][0][k][l],dp[i-1][0][k+(1<<i-1)][l]);

        for(i=1;(1<<i)<=N;++i)
            for(j=1;(1<<j)<=N;++j)
                    for(k=1;k+(1<<i)-1<=N;++k)
                        for(l=1;l+(1<<j)-1<=N;++l)
                            dp[i][j][k][l] = max({
                                                dp[i-1][j-1][k][l] ,
                                                dp[i-1][j-1][k+(1<<i-1)][l],
                                                dp[i-1][j-1][k][l+(1<<j-1)],
                                                dp[i-1][j-1][k+(1<<i-1)][l+(1<<j-1)]}
                            );
    }
    int query(int x1 , int y1 , int x2 , int y2)
    {
        int dif_x = x2 - x1 + 1;
        int dif_y = y2 - y1 + 1;
        return max({dp[LG[dif_x]][LG[dif_y]][x1][y1],
                    dp[LG[dif_x]][LG[dif_y]][x2-(1<<LG[dif_x])+1][y1],
                    dp[LG[dif_x]][LG[dif_y]][x1][y2-(1<<LG[dif_y])+1],
                    dp[LG[dif_x]][LG[dif_y]][x2-(1<<LG[dif_x])+1][y2-(1<<LG[dif_y])+1]
                    });
    }
};
int main()
{
  for(i=1;i<=N;++i)
    for(j=1;j<=N;++j)
            dp[0][0][i][j]=mat[i][j];
    ZZ.ini(N);
    LL ans = 0;
    for(i=1;i+K-1<=N;++i)
        for(j=1;j+K-1<=N;++j)
            ans+=ZZ.query(i,j,i+K-1,j+K-1);

