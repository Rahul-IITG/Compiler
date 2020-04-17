#include "lexical.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool is_preprocessor(vector <string>words)
{
    if (words[0]=="#include")
    {
        return true;
    }

    return false;
}

bool is_keyword(string word)
{
    vector <string>keywords={"int","string","long","double","float","vector","return","bool","if","else","for",
                             "using","namespace","std","cout","cin","endl","void","bool","noskipws","getline","ifstream","while",
                             "continue","break"};

    int s;
    s=keywords.size();

    for (int i=0;i<s;i++)
    {
        if (word==keywords[i])
        {
            return true;
        }
    }

    return false;
}

bool is_operator(string word)
{
    vector <string>operators={"+","-","*","/","%","=",">","<","<=","=<",">=","=>"};

    int s;
    s=operators.size();

    for (int i=0;i<s;i++)
    {
        if (word==operators[i])
        {
            return true;
        }
    }

    return false;
}

bool is_delimiter(string word)
{
    vector <string>delimiters={"(",")","{","}",",",";","[","]","\"","<<",">>"};

    int s;
    s=delimiters.size();

    for (int i=0;i<s;i++)
    {
        if (word==delimiters[i])
        {
            return true;
        }
    }

    return false;
}

bool is_logical(string word)
{
    vector <string>log_operators={"&&","||","&","|","!"};

    int s;
    s=log_operators.size();

    for (int i=0;i<s;i++)
    {
        if (word==log_operators[i])
        {
            return true;
        }
    }

    return false;
}


pair <string,string>preprocessor_token(vector <string>words)
{
    string lib;
    lib=words[1].substr(1,words[1].size()-2);

    return make_pair(lib,"library");
}

void token_generator2(vector <string>words, vector <pair <string,string>>&tokens)
{
    int s;
    s=words.size();

    for (int i=0;i<s;i++)
    {
        if (is_keyword(words[i]))
        {
            tokens.push_back(make_pair(words[i],"keyword"));
            continue;
        }
        if (is_operator(words[i]))
        {
            tokens.push_back(make_pair(words[i],"operator"));
            continue;
        }
        if (is_delimiter(words[i]))
        {
            tokens.push_back(make_pair(words[i],"delimiter"));
            continue;
        }
        if (is_logical(words[i]))
        {
            tokens.push_back(make_pair(words[i],"logical"));
            continue;
        }

        tokens.push_back(make_pair(words[i],"identifier"));
    }

    return;
}

bool is_parts(string word, vector <pair <string,string>>&tokens)
{
    string part;
    int s;
    s=word.size();

    vector <string>words;
    int flag;
    flag=0;

    for (int i=0;i<s;i++)
    {
        string str_n(1,word[i]);

        if (is_operator(str_n))
        {
            flag=1;
            if (part.size()!=0)
            {
                if (part=="="||part=="<"||part==">"||part=="+"||part=="-")
                {
                    part.push_back(word[i]);
                    words.push_back(part);
                    part.clear();
                    continue;
                }
                words.push_back(part);
                part.clear();
            }


        }

        part.push_back(word[i]);

        if (i==s-1)
        {
            words.push_back(part);
        }
    }

    if (flag==1)
    {
        token_generator2(words,tokens);
        return true;
    }

    return false;
}

void token_generator(vector <string>words, vector <pair <string,string>>&tokens)
{
    if (is_preprocessor(words))
    {
        tokens.push_back(preprocessor_token(words));
        return;
    }

    int s;
    s=words.size();

    for (int i=0;i<s;i++)
    {
        if (is_keyword(words[i]))
        {
            tokens.push_back(make_pair(words[i],"keyword"));
            continue;
        }
        if (is_operator(words[i]))
        {
            tokens.push_back(make_pair(words[i],"operator"));
            continue;
        }
        if (is_delimiter(words[i]))
        {
            tokens.push_back(make_pair(words[i],"delimiter"));
            continue;
        }
        if (is_logical(words[i]))
        {
            tokens.push_back(make_pair(words[i],"logical"));
            continue;
        }
        if (is_parts(words[i],tokens))
        {
            continue;
        }

        tokens.push_back(make_pair(words[i],"identifier"));
    }

    return;
}

template <typename t1, typename t2>

void token(string line, vector <pair <t1,t2>>&tokens)
{
    vector <string>words;
    string str;
    int s;
    s=line.size();

    string str_n;

    for (int i=0;i<s;i++)
    {
        if (line[i]==' '||line[i]==';'||line[i]==','||line[i]=='('||line[i]==')'||line[i]=='{'||line[i]=='}'||line[i]=='"')
        {
            if (str.size()!=0)
            {
                words.push_back(str);
                str.clear();
            }
            if (line[i]!=' ')
            {
                str_n.push_back(line[i]);
                words.push_back(str_n);
                str_n.clear();
            }

            continue;
        }

        str.push_back(line[i]);

        if (i==s-1)
        {
            if (str.size()!=0)
            {
                words.push_back(str);
            }
            continue;
        }
    }

    if (words.size()==0)
    {
        return;
    }

    token_generator(words,tokens);

    for (int i=0;i<tokens.size();i++)
    {
        cout<<"<"<<tokens[i].first<<", "<<tokens[i].second<<">"<<endl;
    }

}

void lexi(string file_name)
{
    fstream file;
    file.open(file_name);

    if (!file.is_open())
    {
        cout<<"cannot open code"<<endl;
        return;
    }

    string line;

    vector <pair <string,string>>tokens;

    while (getline(file,line))
    {
        token(line,tokens);
        tokens.clear();
    }

}
