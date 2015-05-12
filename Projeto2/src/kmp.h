/*
 * kmp.h
 *
 *  Created on: 12/05/2015
 *      Author: Nuno
 */

#ifndef KMP_H_
#define KMP_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

int kmp(string text, string wordToSearch);
vector<int> computePrefixFunction(string word);

#endif /* KMP_H_ */
