// Linux_Cmd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"Command.h"

string folderpath[8];
void Analizepath(string* str)
{
	int ptr = 0;
	for (int i = 0; !str[i].empty(); i++)
	{
		if (str[i].find(":", 0) != string::npos|| strcmp(str[i].c_str(), ".") == 0 || strcmp(str[i].c_str(), "..")==0)//若为全局路径
			folderpath[ptr++] = str[i];
		else if (str[i].find("\\", 0) != string::npos||str[i].find("/", 0) != string::npos)//若为相对路径
			folderpath[ptr++] = cwd + str[i];
		else if (str[i].find(".", 0) != string::npos)//若为文件
		{
			folderpath[ptr] = cwd;
			folderpath[ptr++].append("\\").append("\\").append(str[i]);
		}
	}
	if (ptr == 0 && str[1].empty())
		folderpath[ptr++] = cwd;
}
int main()
{
	//mkdir -m 700 F:\\test\\test.txt
	cout << "*********************************************" << endl;
	cout << "**  操作系统课设：兼容Linux的命令接口      **" << endl;
	cout << "**ls、mkdir、cp、cd、rm、touch、rmdir、cat **" << endl;
	cout << "**           Author：shao  xh              **" << endl;
	cout << "*********************************************" << endl;
	string StrCmd;
	string str[8];
	int npos = 0;
	char CurrentWorkDirectory[128];
	GetCurrentDirectoryA(128, CurrentWorkDirectory);
	cout << "$ "<<(string)CurrentWorkDirectory << ">";
	cwd = CurrentWorkDirectory;
	while (cin.get() != '\n')
	{
		cin.unget();
		cin >> str[npos];
		npos++;
	}
	while (true)
	{
		folderpath[0] = cwd;
		if (str[0] == "mkdir")
		{
			if (str[1] == "-p") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) Mkdir_p(folderpath[i]); }
			else if (str[1] == "-m") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++)Mkdir_m(folderpath[i], str[2]); }
			else if(str[1].find("-p", 0) == string::npos&&str[1].find("-m", 0) == string::npos){ Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++)Mkdir(folderpath[i]); }
			else { cout << "The input is incorrect!  mkdir ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "cd")
		{
			if (!str[1].empty()){	Analizepath(str);cd(folderpath[0]);}
			else{ cout << "The input is incorrect!  cd ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "ls")
		{
			if (str[1] == "-l") { Analizepath(str);			ls_l(folderpath[0]); }
			else if (str[1] == "-a") { Analizepath(str);	ls_a(folderpath[0]); }
			else if (str[1] == "-d") { Analizepath(str);	ls_d(folderpath[0]); }
			else if (str[1] == "-A") { Analizepath(str);	ls_A(folderpath[0]); }
			else if (str[1] == "-R") { Analizepath(str);	ls_R(folderpath[0]); }
			else if (str[1] == "-m") { Analizepath(str);	ls_m(folderpath[0]); }
			else if(str[1].find("-",0)==string::npos) { Analizepath(str);	ls(folderpath[0]); }
			else {	cout << "The input is incorrect!  ls ([选项]) [参数]" << endl;	}
		}
		else if (str[0] == "touch")
		{
			if (str[1] == "-a") {	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_a(folderpath[i]);	}
			else if (str[1] == "-m"){	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_m(folderpath[i]);	}
			else if (str[1] == "-r") { Analizepath(str); int j = 0; for (; !folderpath[j].empty(); j++); for (int i = 0; !folderpath[i + 1].empty(); i++) touch_r(folderpath[i], folderpath[j-1]); }
			else if (str[1] == "-d") { Analizepath(str); int j = 0; for (; !folderpath[j].empty(); j++); for (int i = 0; i<j-2; i++) touch_d(folderpath[i], (str[j-1] + str[j-2]).c_str()); }
			else if(!str[1].empty()){	Analizepath(str);touch(folderpath[0]);	}
			else { cout << "The input is incorrect!  touch ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "rm")
		{
			if (str[1] == "-R"){	Analizepath(str);rm_R(folderpath[0]);	}
			else if (str[1] == "-i") { Analizepath(str); rm_i(folderpath[0]); }
			else if(!str[1].empty()){	Analizepath(str);rm(folderpath[0]);	}
			else { cout << "The input is incorrect!  rm ([选项]) [参数]" << endl; }
		}

		else if (str[0] == "rmdir")
		{
			if (str[1] == "-p"){	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) rmdir_p(folderpath[i]);}
			else if(!str[1].empty()){ Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) rmdir(folderpath[i]); }
			else { cout << "The input is incorrect!  rmdir ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "cp")
		{
			if (str[1] == "-R") {
				Analizepath(str);
				cp_R(folderpath[0], folderpath[1]);
			}
			else if (str[1].find(".",0)!=string::npos && !str[2].empty()) {
				Analizepath(str); for (int i = 0; !folderpath[i+1].empty(); i++) { string temp = folderpath[npos - 2]; cp(folderpath[i], temp.append("\\").append(str[i + 1])); }
			}
			else if (!str[1].empty() && str[2].empty()) { Analizepath(str); cp(folderpath[0], cwd); }
			else { cout << "The input is incorrect!  cp ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "cat")
		{
			if (str[1].find("-",0)==string::npos)
			{	Analizepath(str); cat(folderpath[0], FALSE);	}
			else if(str[1] == "-n")
			{	Analizepath(str); cat(folderpath[0], TRUE);	}
			else {	cout << "The input is incorrect!  cp ([选项]) [参数]" << endl;	}
		}
		else if (str[0] == "mv")
		{
			Analizepath(str); mv(folderpath[0], folderpath[1]);
		}
		else {
			cout << "This instruct is not currently supported!" << endl;
		}

		cout << "$ " << cwd << ">";
		for (int j = 0; j < 8; j++)
		{
			str[j].clear();
			folderpath[j].clear();
		}

		npos = 0;
		
		while (cin.get() != '\n')
		{
			cin.unget();
			cin >> str[npos];
			npos++;
		}
	}
	 return 0;
}
