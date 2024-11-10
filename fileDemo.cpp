//demo 1   文件输入：文件操作的读取
#define _CRT_SECURE_NO_WARNINGS   ///使用类scanf printf这样的函数需要在第一行包含该语句
#define BUFLEN 256
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include <iostream>
#include <set>
#include<string>
using namespace std;
int main() {
    vector<string>MYFile;
    char lineBuf[BUFLEN];
    FILE* source;
    const char* pgm = "case2.txt";     ///test.txt文件需要和该代码源文件在同一个目录，注意查看是否隐藏了文件类型，避免文件为test.txt.txt
    source = fopen(pgm, "r");    ////获得文件指针，"r"表示只读方式打开
    while (1) {
        if (fgets(lineBuf, BUFLEN - 1, source)) {  ///逐行读入文件内容，每次读入的内容都存放在lineBuf中
            string tmep;
            tmep = lineBuf;
            MYFile.insert(MYFile.end(),tmep);
        }
        else {   ////已经到了文件末尾，可以直接退出
            //end of file
            break;
        }
    }  
    fclose(source);   ///用完后要关闭文件指针
    while (!MYFile.empty())
    {
        vector<string>  myFile;
        for (int i = 0; i < 4; i++)
        {
            myFile.insert(myFile.end(), MYFile[0]);
            cout << myFile[i];
            MYFile.erase(MYFile.begin());
        }
        if(!MYFile.empty())MYFile.erase(MYFile.begin());

        //变量赋值
        vector<string> P1;
        vector<string> P2;
        set<char> Vp;
        set<char> Vn;
        char S;
        //对Vp进行处理；
        string s = myFile[0];
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ',')
                continue;
            Vp.insert(s[i]);
        }
        //对Vn进行处理
        s = myFile[1];
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ',')
                continue;
            Vn.insert(s[i]);
        }
        //对P进行处理
        s = myFile[2];
        int start = 0;
        int pos;
        bool has1;
        //cout << pos << endl;
        int index_of_arrow;
        string term;
        string Arrow = "->";
        string alpha, beta;
        string beta1;
        //对term进行分割
        while (s.length() != 0)
        {
            pos = s.find(',');
            term = s.substr(start, pos);
            if (term.find(Arrow, 0) != string::npos)
            {
                has1 = false;
                index_of_arrow = term.find(Arrow, 0);
                alpha = term.substr(0, index_of_arrow);
                beta = term.substr(index_of_arrow + 2, term.length() - index_of_arrow - 2);
                int pos1 = beta.find('|');
                while (pos1 > 0)
                {
                    has1 = true;
                    beta1 = beta.substr(0, pos1);
                    beta = beta.substr(pos1 + 1, beta.length() - pos);
                    //cout << beta1 <<endl << beta<<endl;
                    //cout <<"----------------"<<endl;
                    pos1 = beta.find('|');
                    P1.insert(P1.end(), alpha);
                    P2.insert(P2.end(), beta1);
                }
                P1.insert(P1.end(), alpha);
                P2.insert(P2.end(), beta);
            }
            if (pos < 0)
                break;
            s = s.substr(pos + 1, s.length() - pos);
            if (has1) {
                P1.insert(P1.end(), alpha);
                P2.insert(P2.end(), beta1);
                continue;
            }
        }
        //判断文法
        int one_of_type = 4;
        int type = 4;//文法类型
        for (int it = 0; it < P1.size(); it++)
        {
            if (one_of_type < type)
                type = one_of_type;
            alpha = P1[it];
            beta = P2[it];
            //判断0型文法
            bool has_Vp = false;//旗帜
            for (int i = 0; i < alpha.length(); i++) {
                if (Vp.find(alpha[i]) != Vp.end()) {
                    has_Vp = true;
                    break;
                }
            }
            one_of_type = 0;
            if (!has_Vp) {
                type = -1;
                break;
            }
            //判断1型文法
            if (alpha.length() <= beta.length() || beta.length() == 0)
                one_of_type = 1;
            else
                continue;
            //判断2型文法
            if (alpha.length() == 1 && Vp.find(alpha[0]) != Vp.end())
                one_of_type = 2;
            else
                continue;
            //判断3型文法
            if (beta.length() == 1 && Vn.find(beta[0]) != Vn.end())
                one_of_type = 3;
            else if (beta.length() == 2 && (Vn.find(beta[0]) != Vn.end() && Vp.find(beta[1]) != Vp.end()) || (Vn.find(beta[1]) != Vn.end() && Vp.find(beta[0]) != Vp.end()))
                one_of_type = 3;
            else
                continue;
        }
        if (one_of_type < type)
            type = one_of_type;
        //最后输出文法
        if (type == -1)
            cout << "该文法不是正规文法" << endl;
        else
            cout << "该文法为 " << type << " 型文法" << endl;

        cout << endl;

    }
}
