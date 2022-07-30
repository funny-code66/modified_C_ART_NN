#include <bits\stdc++.h>

#define complex complex<float>
#define FOR(i, n0, n) for(int i=n0; i<n; i++)
#define NORM(x, n, res) *res=0;FOR(i,0,n)*res+=abs(x[i]);
#define EXIST_TEST(flag) *flag=0;FOR(i,0,n)*flag+=state[i];

using namespace std;

complex w[100][100], x[100][100];
float alpha = 0.05, beta = 0.01; rho = 0.1;
int N, dataLen, categoryNum = 1, c = 0, state[100], output[100];

void init() {
  float temp1, temp2;
  scanf("%d%d", &N, &dataLen);
  FOR(i, 0, dataLen) FOR(j, 0, N) {
    scanf("%f%f", &temp1, &temp2);
    x[i][j] = complex(temp1, temp2);
  }
  memset(state, 0, sizeof(state));
  FOR(i, 0, N) w[0][i] = x[0][i];
  state[0] = 1;
}

bool vigilanceTest(int m) {
  complex tmp[100];
  float normW_X = 0;
  FOR(i, 0, N) tmp[i] = X[m][i] - W[c][i];
  NORM(tmp, N, &normW_X);
  return (normW_X / N < rho) ? 1 : 0;
}

float choiceFunc(int m, complex x[100]) {
  complex tmp[100];
  float normW_X, normW;
  FOR(i, 0, N) tmp[i] = X[i] - W[m][i];
  NORM(tmp, N, &normW_X);
  NORM(w[m], N, &normW);

  return normW_X / (alpha+normW);
}

void C_ART() {
  int flag;
  FOR(i, 1, dataLen) {
    L:
    float min = 1e10, tmp;
    c = 0;
    FOR(j, 0, categoryNum) {
      if (!state[j]) continue;
      tmp = choiceFunc(j, X[i]);
      if (min > tmp) min = tmp, c = j;
    }
    if (!vigilanceTest(i)) {
      state[c] = 0;
      EXIST_TEST(&flag);
      if (!flag) {
        output[i] = categoryNum;
        FOR(j, 0, 2*N) W[categoryNum][j] = X[i][j];
        categoryNum++;
        FOR(j, 0, categoryNum) state[j] = 1;
      }
      goto L;
    }
    FOR(j, 0, 2*N) 
      W[i][j] = beta*(W[i][j] - X[i][j]) + (1 - beta) * W[i][j];
    output[j] = c;
    FOR(j, 0, categoryNum) state[j] = 1;
  }
}

