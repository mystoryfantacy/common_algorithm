//KMP 算法
#include<stdio.h>
#include<string.h>

//build next;
void makeNext(const char* pattern, int* next) {
	int len = strlen(pattern);
	int i=1,j=0;
	next[0] = 0;

	for(; i < len; i++) {
		while(j>0 && pattern[j] != pattern[i])
			j = next[j-1];
		if (pattern[j] == pattern[i])
			j = j+1;
		next[i] = j; 
	} 
}

//search
int kmp(const char* s, const char* pattern, int* matches) {
	int len = strlen(s);
	int pattern_len = strlen(pattern);
	int* next = new int[pattern_len];
	makeNext(pattern, next);
	int n = 0;
	for (int i = 0, j = 0; i < len; i++) {
		while(j>0 && s[i] != pattern[j])
			j = next[j-1];
		if (s[i] == pattern[j])
			j++;
		if (j == pattern_len) {
            matches[n++] = i - pattern_len + 1;
            j = next[j-1];
		}

	}
	return n;
}

int kmp(const char* s, const char* pattern, int* matches) {
	int len = strlen(s);
	int pattern_len = strlen(pattern);
	int* next = new int[pattern_len];
	makeNext(pattern, next);
	int n = 0, i = 0, j = 0;
	while(pattern_len - j < len - i) {
		while (j>0 && s[i] != pattern[j])
			j = next[j-1];
		if (s[i] == pattern[j])
			j++;
		if (j == pattern_len) {
			matches[n++] = i - pattern_len + 1;
			j = next[j-1];
		}
		i++;
	}
	return n;
}