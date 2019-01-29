//============================================================================
// Name        : APlusBHard.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <string>
#include <assert.h>

//#define DEBUG

using namespace std;

const int MAX = 1000000;
int n, num_buf[MAX], num0_buf[MAX], ans[MAX + 1], numlen;
char a_[MAX], b_[MAX], equ_buf[MAX], equ0_buf[MAX];
string a, b, final, temp;
bool is_negative;

void equalize(){
	int la = a.length(), lb = b.length();
	const char* buf_ = a.c_str();
	const char* buf0_ = b.c_str();

	if(la > lb){
		int delta = la - lb;
		for (int i = 0; i < la; ++i) {
			if(i >= delta){
				num0_buf[i] = buf0_[i - delta] - '0';
			}
			else{
				num0_buf[i] = 0;
			}
			num_buf[i] = buf_[i] - '0';
		}

		numlen = la;

#ifdef DEBUG
		printf("Equalize (a>b)\n");
#endif
	}
	else if(lb > la){
		int delta = lb - la;
		for (int i = 0; i < lb; ++i) {
			if(i >= delta){
				num_buf[i] = buf_[i - delta] - '0';
			}
			else{
				num_buf[i] = 0;
			}
			num0_buf[i] = buf0_[i] - '0';
		}

		numlen = lb;

#ifdef DEBUG
		printf("Equalize (a<b)\n");
#endif
	}
	else{
		for (int i = 0; i < la; ++i) {
			num_buf[i] = buf_[i] - '0';
			num0_buf[i] = buf0_[i] - '0';
		}

		numlen = la;

#ifdef DEBUG
		printf("Equalize (a=b)\n");
#endif
	}

#ifdef DEBUG
	printf("numlen: %d\n", numlen);
	printf("num_buf: ");
	for (int i = 0; i < numlen; ++i) {
		printf("%d, ", num_buf[i]);
	}
	printf("\n");

	printf("num0_buf: ");
	for (int i = 0; i < numlen; ++i) {
		printf("%d, ", num0_buf[i]);
	}
	printf("\n");
#endif
}

//no sign;
void add(){
	ans[0] = 0;
	for (int i = 0; i < numlen; ++i) {
		ans[i + 1] = num_buf[i] + num0_buf[i];
	}

	for(int i = numlen; i > 0; i--){
		if(ans[i] >= 10){
			ans[i] -= 10;
			ans[i - 1]++;
		}
	}

#ifdef DEBUG
	printf("ans: ");
	for (int i = 0; i < numlen + 1; ++i) {
		printf("%d, ", ans[i]);
	}
	printf("\n");
#endif

	bool begin = false;
	for (int i = 0; i <= numlen; ++i) {
		if(!begin){
			begin = ans[i] != 0;
		}

		if(begin){
			final += to_string(ans[i]);
		}
	}
}

void subtract(){
#ifdef DEBUG
	printf("subtract\n");
#endif
	ans[0] = 0;
	for (int i = 0; i < numlen; ++i) {
		ans[i + 1] = num_buf[i] - num0_buf[i];
	}

	int begin = -1;
	for (int i = 0; i <= numlen; ++i) {
		if(ans[i] != 0){
			begin = i;
			break;
		}
	}

	is_negative = ans[begin] >= 0;
	if(!is_negative){
		//Number is negative
		for (int i = numlen; i >= 0; --i) {
			ans[i] = -ans[i];
		}
	}
	for(int i = numlen; i > 0; i--){
		if(ans[i] < 0){
			ans[i] += 10;
			ans[i - 1]--;
		}
	}

#ifdef DEBUG
	printf("ans: ");
	for (int i = 0; i < numlen + 1; ++i) {
		printf("%d, ", ans[i]);
	}
	printf("\n");
	printf("is_negative: %d\n", is_negative);
#endif

	bool beginn = false;
	for (int i = 0; i <= numlen; ++i) {
		if(!beginn){
			beginn = ans[i] != 0;
		}
		if(beginn){
			final += to_string(ans[i]);
		}
	}
}

string s_sign(string a){
	return a.substr(1, a.length() - 1);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s %s", a_, b_);
		a = string(a_);
		b = string(b_);

		bool sign_a = a[0] == '-', sign_b = b[0] == '-';

		if(sign_a){
			if(sign_b){
				a = s_sign(a);
				b = s_sign(b);

				equalize();
				add();

				printf("-%s\n", final.c_str());
			}
			else{
				a = s_sign(a);

				temp = a;
				a = b;
				b = temp;

				equalize();
				subtract();

				printf("%s%s\n", is_negative ? "" : "-", final.c_str());
			}
		}
		else{
			if(sign_b){
				b = s_sign(b);
				equalize();
				subtract();

				printf("%s%s\n", is_negative ? "" : "-", final.c_str());
			}
			else{
				equalize();
				add();

				printf("%s\n", final.c_str());
			}
		}

		if(final == ""){
			//Answer is 0
			printf("0\n");
		}

		final = "";
	}
	return 0;
}
