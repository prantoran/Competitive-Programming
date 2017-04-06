#include <bits/stdc++.h>
using namespace std;
const int inf = 1e30;
#define Size 1005

int N,M;
int A[Size];
int mid[Size][Size];
int DP[Size][Size];
/// DP[i][k] = Minimum total cost to divide first i positions into k partitions.
/// Where the k'th partition ends at position i.
int cost[Size][Size];
int csum[Size];

/// Knuth's Conditions:
/// mid[i,j-1] <= mid[i,j] <= mid[i+1,j]
/// Here, mid[i][j] = k represents the index which gives the optimal answer if we make the j'th partition at k.
/// cost[i][j] represents the cost for the interval i to j.
/// For any a,b,c,d where a <= b <= c <= d :
/// cost[a][c] + cost[b][d] <= cost[a][d] + cost[b][c] (quadrangle inequality).
/// cost[b][c] <= cost[a][d] (monotonicity).

void costFunction(){
    for(int i = 1;i<=N;i++){
        csum[i] = A[i];
        cost[i][i] = 0;
        for(int j = i+1;j<=N;j++){
            csum[j] = csum[j-1] + A[j];
            cost[i][j] = cost[i][j-1] + csum[j-1]*A[j];
        }
    }
}

/// Check if the cost function satisfy knuth conditions:

bool knuthValidation(int N){
    int a,b,c,d;
    int A[4];
    /// a <= b <= c <= d
    for(int i = 0;i<1000;i++){
        for(int p = 0;p<4;p++){
            A[p] = rand()%N;
            if(A[p] == 0) A[p] = 1;
        }
        sort(A,A+4);
        a = A[0], b = A[1], c = A[2], d = A[3];
        int ac_bd = cost[a][c] + cost[b][d];
        int ad_bc = cost[a][d] + cost[b][c];
        int bc = cost[b][c];
        int ad = cost[a][d];
        if(ac_bd > ad_bc || bc > ad){
            printf("Knuth Condition Mismatch for (a, b, c, d) = (%d, %d, %d, %d)\n",a,b,c,d);
            return false;
        }
    }
    return true;
}

int knuthOptimization(){
    for(int k = 1;k<=M;k++){
        mid[N+1][k] = N;
    }

    for(int i = 1;i<=N;i++){
        DP[i][1] = cost[1][i];
        mid[i][1] = 0;
    }

    for (int k = 2; k <= M; k++){
        for (int i = N; i >= 1; i--) {
            int L1 = mid[i][k-1];
            int L2 = mid[i+1][k];
            DP[i][k] = inf;
            if(L1>L2){
                /// Knuth condition mismatch.
            }
            /// The optimal answer lie for an index between (L1 - L2).
            /// So we don't need to check for all (1 - i) to make a partition.
            for(int m = L1;m<=L2 && m<i;m++){
                int rs = DP[m][k-1] + cost[m+1][i];
                if(rs < DP[i][k]){
                    DP[i][k] = rs;
                    mid[i][k] = m;
                }
            }
        }
    }
    return DP[N][M];
}

int solve(){
    costFunction();
    if(knuthValidation(N) == false) return -1;
    return knuthOptimization();
}

int main () {
    scanf("%d %d",&N,&M);
    M++;
    for(int i = 1;i<=N;i++){
        scanf("%d",&(A[i]));
    }
    int res = solve();
    printf("%d\n",res);
    return 0;
}
