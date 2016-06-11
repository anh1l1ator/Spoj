#include<bits/stdc++.h>
using namespace std;
typedef pair < int , int > Point;

bool comp(Point a,Point  b)
{

    Point center = {0,0};
    #define x first
    #define y second
    if (a.x - center.x >= 0 && b.x - center.x < 0)
        return true;
    if (a.x - center.x < 0 && b.x - center.x >= 0)
        return false;
    if (a.x - center.x == 0 && b.x - center.x == 0) {
        if (a.y - center.y >= 0 || b.y - center.y >= 0)
            return a.y > b.y;
        return b.y > a.y;
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
    if (det < 0)
        return true;
    if (det > 0)
        return false;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
    int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
    return d1 > d2;
    #undef x
    #undef y
}



int dp[101][101];
const int INF = (int)1e9;
Point create(Point B , Point A){return {A.first-B.first,A.second-B.second};}
int cross(Point A,Point B){return A.first * B.second - B.first * A.second;}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string S;
    while(cin>>S)
    {
        int N , i , j ;
        cin>>N;
        vector < Point > A(N+1);
        for(i=1;i<=N;++i)
            cin>>A[i].first>>A[i].second;
        sort(A.begin()+1,A.end(),comp);
        A[0] = {0,0};
        int ans = 3;
        for(i=1;i<=N;++i)
        {
            dp[i][0] = 2;
            for(j=1;j<=i-1;++j)
            {
                dp[i][j] = -INF;
                for(int k=0;k<=j-1;++k)
                    if(cross(create(A[k],A[j]),create(A[j],A[i]))<0)
                        dp[i][j] = max(dp[i][j] , dp[j][k]+1);
                if(cross( create(A[j],A[i]),create(A[i],A[0])  )<0)
                    ans = max(ans , dp[i][j]);
            }
        }
        cout<<"POLYGON.OUT\n\n";
        cout<<ans<<"\n\n";
    }
    return 0;
}
