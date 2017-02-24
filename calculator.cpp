// -------------------------------------------------
// Copyright 2016 Authors. All rights reserved.
// Create Date: 2016-11-18
// Author: Yiji Liao
// -------------------------------------------------
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;

const int maxn = 10010;

int len;                  //ԭʼ���ʽ���� 
int n;                    //�ʷ���Ԫ���г��� 
int numStack[maxn];       //�洢��������ջ
string opStack[maxn];     //�洢��������ջ
string str;               //ԭʼ���ʽ 
string expr[maxn];        //��׺���ʽ�ʷ���Ԫ����
string postExpr[maxn];    //��׺���ʽ�ʷ���Ԫ����
bool valid;               //�ж��Ƿ�Ϸ��ı�־ 

//�������ȼ� 
int priority(string ch) {
	if (ch == "+" || ch == "-") return 1; else
	if (ch == "*" || ch == "/") return 2;
}

//�ж��Ƿ�Ϊ���� 
bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

//�ж��Ƿ�Ϊ����� 
bool isOp(string ch) {
	return ch == "+" || ch == "-" || ch == "*" || ch == "/";
}

//�ж��Ƿ�Ϊ������ 
bool isNum(string now) {
	return isDigit(now[0]);
}

//�ַ���ת��Ϊ��ֵ 
int val(string num) {
	int n = num.size(), now = 0;
	for (int i = 0; i < n; i++) {
		now = now*10+num[i]-'0';
	}
	return now;
}

//������ʽ 
void inputExpr() {
	char ch;
	len = 0;
	while (ch = getchar(), ch != '\n' && ch != EOF){
		if (ch == ' ') continue;
		if ((ch == '+' || ch == '-') && (len == 0 || str[len-1] == '(')) str[len++] = '0';
		str[len++] = ch;
	}
}

//��ȡ�ʷ���Ԫ 
void getTokens(string tokens[]) {
	n = 0;
	string now;
	for (int i = 0; i < len; i++) {
		if (isDigit(str[i])) {
			now = "";
			while (i < len && isDigit(str[i])) now += str[i++];
			i--;
		} else now = str[i];
		tokens[++n] = now;
	}
}

//��׺���ʽת��׺���ʽ 
void trans(string tokens[], string result[]) {
	int m, top;
	m = 0;
	top = 0;
	for (int i = 1; i <= n; i++) {
		if (isNum(tokens[i])) result[++m] = tokens[i];
		else if (tokens[i] == "(") opStack[++top] = "(";
		else if (tokens[i] == ")") {
			while (top != 0 && opStack[top] != "(")
				result[++m] = opStack[top--];
			if (top == 0) {
				printf("Redundant brackets!\n");
				valid = false;
				return;
			}
			top--;
		}
		else {
			while (top != 0 && opStack[top] != "(" && priority(opStack[top]) >= priority(tokens[i]))
				result[++m] = opStack[top--];
			opStack[++top] = tokens[i];
		}
	}
	while (top != 0) {
		if (opStack[top] == "(") {
			printf("Redundant brackets!\n");
			valid = false;
			return;
		}
		result[++m] = opStack[top--];
	}
	n = m;
}

//�����׺���ʽ��ֵ 
void calc(string tokens[]) {
	int top = 0, lhs, rhs;
	for (int i = 1; i <= n; i++) {
		if (isOp(tokens[i])) {
			if (top == 0){
				printf("Invalid expression!\n");
				valid = false;
				return;
			} else rhs = numStack[top--];
			if (top == 0){
				printf("Invalid expression!\n");
				valid = false;
				return;
			} else lhs = numStack[top--];
			if (tokens[i] == "+") numStack[++top] = lhs+rhs; else
			if (tokens[i] == "-") numStack[++top] = lhs-rhs; else
			if (tokens[i] == "*") numStack[++top] = lhs*rhs; else
			if (tokens[i] == "/") {
				if (rhs == 0) {
					printf("Divided by zero!\n");
					valid = false;
					return;
				} else numStack[++top] = lhs/rhs;
			}
		} else {
			numStack[++top] = val(tokens[i]);
		}
	}
	if (top != 1) {
		printf("Invalid expression!\n");
		valid = false;
	}
}

int main() {
	inputExpr();
	getTokens(expr);
	valid = true;
	trans(expr, postExpr);
	if (!valid) return 0;
	calc(postExpr);
	if (!valid) return 0;
	printf("Answer: %d\n", numStack[1]);
	return 0;
}

