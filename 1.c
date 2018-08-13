#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define input 2
#define hidden 2
#define alpha 10
#define SEED 65535

#define bignum 100
#define limit 0.0001

double s(double u);
void initHW(double hw[hidden][input + 1]);
void initOW(double ow[hidden + 1]);
void learnO(double ow[hidden + 1], double hi[], double e[input + 1], double o);
void learnH(double hw[hidden][input + 1], double ow[hidden + 1], double hi[], double e[input + 1], double o);
double drnd(void);
void print(double hw[hidden][input + 1], double ow[hidden + 1]);
double forward(double hw[hidden][input + 1], double ow[hidden + 1], double hi[], double e[input + 1]);


int main() {
	double hw[hidden][input + 1];
	double ow[hidden];
	double e[4][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 1.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 } };
	double hi[hidden];
	double o;
	double error = bignum;
	int i, j;
	int n_e;
	int count = 0;

	srand(SEED);


	initHW(hw);
	initOW(ow);
	print(hw, ow);

	n_e = 4;


	printf("학습 데이터 개수 : %d\n", n_e);


	while (error > limit) {  
		error = 0.0;
		for (i = 0; i < n_e; ++i) {
			o = forward(hw, ow, hi, e[i]);
			learnO(ow, hi, e[i], o);
			learnH(hw, ow, hi, e[i], o);
			error += (o - e[i][input])*(o - e[i][input]);
		}
		++count;
		printf("%d\t%lf\n", count, error);
	}

	print(hw, ow);
	

	for (i = 0; i < n_e; ++i) {
		printf("%d ", i);
		for (j = 0; j < input+1; ++j) {
			printf("%lf ", e[i][j]);
		}
		o = forward(hw, ow, hi, e[i]);
		printf("%lf ", o);
		if (o > 0.5 ){
			printf("결과 : %lf\n", 1.0);
		}
		else {
			printf("결과 : %lf\n", 0.0);
		}

	}

	double test[1][2];
	scanf("%lf %lf\n", &test[0][0], &test[0][1]);
	o = forward(hw, ow, hi, test[0]);
	printf("%lf ", o);
	if (o > 0.5) {
		printf("결과 : %lf\n", 1.0);
	}
	else {
		printf("결과 : %lf\n", 0.0);
	}

	system("pause");
	return 0;
}



double s(double u)
{
	return 1.0 / (1.0 + exp(-u));
}
void initHW(double hw[hidden][input + 1])
{
	int i, j;
	for (i = 0; i < hidden; ++i) {
		for (j = 0; j < input + 1; ++j) {
			hw[i][j] = drnd();

		}
	}
}



void initOW(double ow[hidden + 1])
{
	for (int i = 0; i < hidden + 1; ++i)
	{
		ow[i] = drnd();
	}
}




void learnO(double ow[hidden + 1], double hi[], double e[input + 1], double o)
{
	int i;
	double d;
	d = (e[input] - o)*o*(1 - o);
	for (i = 0; i < hidden; ++i)
	{
		ow[i] += alpha * hi[i] * d;
	} 
	ow[i] += alpha * (-1.0)*d;

}




void learnH(double hw[hidden][input + 1], double ow[hidden + 1], double hi[], double e[input + 1], double o)
{
	int i, j;
	double dj;

	for (j = 0; j < hidden; ++j)
	{
		dj = hi[j] * (1 - hi[j]) * ow[j] * (e[input] - o)*o*(1 - o);
		for (i = 0; i < input; ++i)
		{
			hw[j][i] += alpha * e[i] * dj;
		}
		hw[j][i] += alpha * (-1.0)*dj;
	}
}



double drnd(void)
{
	double rndno;

	while ((rndno = (double)rand() / RAND_MAX) == 1.0);
	rndno = rndno * 2 - 1;

	return rndno;

}




void print(double hw[hidden][input + 1], double ow[hidden + 1])
{
	int i, j;
	for (i = 0; i < hidden; ++i) {
		for (j = 0; j < input ; j++) {
			printf("%lf ", hw[i][j]);
		}
	}
	printf("\n");
	for (i = 0; i < hidden ; ++i) {
		printf("%lf ", ow[i]);
	}
	printf("\n");

}




double forward(double hw[hidden][input + 1], double ow[hidden + 1], double hi[], double e[input + 1])
{
	int i, j;
	double u;
	double o;

	for (i = 0; i < hidden; ++i) {
		u = 0;
		for (j = 0; j < input; ++j)
		{
			u += e[j] * hw[i][j];
		}
		u -= hw[i][j];
		hi[i] = s(u);

	}
	o = 0;
	for (i = 0; i < hidden; ++i) {
		o += hi[i] * ow[i];
	}
	o -= ow[i];

	
	return s(o);

}
