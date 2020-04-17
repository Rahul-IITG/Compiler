#ifndef LEXICAL_H
#define LEXICAL_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool is_preprocessor(vector <string>words);

bool is_keyword(string word);

bool is_operator(string word);

bool is_delimiter(string word);

bool is_logical(string word);

pair <string,string>preprocessor_token(vector <string>words);

void token_generator2(vector <string>words, vector <pair <string,string>>&tokens);

bool is_parts(string word, vector <pair <string,string>>&tokens);

void token_generator(vector <string>words, vector <pair <string,string>>&tokens);

template <typename t1, typename t2>
void token(string line, vector <pair <t1,t2>>&tokens);

void lexi(string file_name);


#endif // LEXICAL_H
