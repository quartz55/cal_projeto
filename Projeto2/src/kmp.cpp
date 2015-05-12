/*
 * kmp.c
 *
 *  Created on: 12/05/2015
 *      Author: Nuno
 */

#include "kmp.h"

vector<int> computePrefixFunction(string word){
	int m = word.size();
	vector<int> cpf={};
	cpf.resize(m);
	if(word.size() > 0)
	{
		cpf[0] = 0;
		int k { 0 };
		for(int q = 1 ; q < m ; q++)
		{
			while(k > 0 && word[k] != word[q])
				k = cpf[k];
			if(word[k] == word[q])
				k++;
			cpf[q] = k;
		}
	}
	return cpf;
}

int kmp(string text, string wordToSearch){
	int counter {0};
	bool b = false; //
	int n = text.size();
	int m = wordToSearch.size();
	vector<int> pi = computePrefixFunction(wordToSearch);
	int q {0};
	for(int i = 0 ; i < n ; i++)
	{
		while(q > 0 && wordToSearch[q+1] != text[i])
		{
			q = pi[q];
		}
		if(wordToSearch[q+1] == text[i])
		{
			q++;
		}
		if(q == m-1)
		{
			//cout << "Pattern occurs with shift " << i-m << endl;
			counter++;
			b = true;
			q = pi[q];
		}
	}
	return b;
	//return counter;
}
