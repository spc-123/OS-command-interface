// Linux_Cmd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"OS-Command-Interface.h"
#pragma comment(lib,"lib/OS-Command-Interface.lib")
#include<iostream>
string folderpath[8];
void Analizepath(string* str)
{
	int ptr = 0;
	for (int i = 0; !str[i].empty(); i++)
	{
		//判断为全局路径
		if ((str[i].find(":", 0) != string::npos&&str[i][0]>=65&&str[i][0] <=122) || strcmp(str[i].c_str(), ".") == 0 || strcmp(str[i].c_str(), "..") == 0)//若为全局路径
			folderpath[ptr++] = str[i];
		else if (str[i].find("\\", 0) != string::npos || str[i].find("/", 0) != string::npos)//若为相对路径
			folderpath[ptr++] = cwd + str[i];
		else if (str[i].find(".", 0) != string::npos)//若为文件
		{
			folderpath[ptr] = cwd;
			folderpath[ptr++].append("\\").append("\\").append(str[i]);
		}
		else if (str[i] == "~")
			folderpath[ptr++] = str[i];
	}
	if (folderpath[0].empty())
		folderpath[ptr++] = cwd;
}
int main()
{
	//mkdir -m 700 F:\\test\\test.txt
	cout << "*******************************************************" << endl;
	cout << "**        操作系统课设：兼容Linux的命令接口          **" << endl;
	cout << "**ls、mkdir、cp、cd、rm、touch、rmdir、cat、mv、find **" << endl;
	cout << "**                 Author：shao  xh                  **" << endl;
	cout << "*******************************************************" << endl;

	string StrCmd;
	string str[100];
	int pos = 0;
	char CurrentWorkDirectory[128];
	GetCurrentDirectoryA(128, CurrentWorkDirectory);
	cout << "$ "<<(string)CurrentWorkDirectory << ">";
	cwd = CurrentWorkDirectory;
	while (cin.get() != '\n')
	{
		cin.unget();
		cin >> str[pos];
		pos++;
	}
	while (true)
	{
		//folderpath[0] = cwd;
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
			else if (str[1] == "-S") { Analizepath(str);	ls_S(folderpath[0],str[2]); }
			else if(str[1].find("-",0)==string::npos) { Analizepath(str);	ls(folderpath[0]); }
			else {	cout << "The input is incorrect!  ls ([选项]) [参数]" << endl;	}
		}
		else if (str[0] == "touch")
		{
			if (str[1] == "-a") {	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_a(folderpath[i]);	}
			else if (str[1] == "-m"){	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_m(folderpath[i]);	}
			//把指定目录或文件的时间设置为参考文件的时间，一个参考文件或目录，多个指定文件或目录
			else if (str[1] == "-r") { Analizepath(str); int j = 0; for (; !folderpath[j].empty(); j++); for (int i = 0; !folderpath[i + 1].empty(); i++) touch_r(folderpath[i], folderpath[j-1]); }
			else if (str[1] == "-d") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++)touch_d(folderpath[i], (str[3*(i+1)] +" "+ str[3*(i+1)+1]).c_str()); }
			else if(!str[1].empty()){	Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch(folderpath[i]);	}
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
				Analizepath(str); for (int i = 0; !folderpath[i+1].empty(); i++) { string temp = folderpath[pos - 2]; cp(folderpath[i], temp.append("\\").append(str[i + 1])); }
			}
			else if (!str[1].empty() && str[2].empty()) { Analizepath(str);
			string temp = cwd;
			cp(folderpath[0], temp.append(str[1].substr(str[1].find_last_of("\\"),str[1].length()))); }
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
			Analizepath(str);
			if (str[1].find("-") == string::npos)
				mv(folderpath[0], folderpath[1]);
			else
				cout << "ERROR!" << endl;
		}
		else if (str[0] == "find")//find   path   -option   [   -print ]   [ -exec   -ok   command ]   {} \;
		{

			string find_path;
			string name[20];
			string iname[20];
			int name_length = 0;
			int iname_length = 0;
			string size = "";
			string maxdepth = "";
			string mindepth = "";
			string atime = "";
			string mtime = "";
			string amin = "";
			string mmin = "";
			string newer = "";
			bool empty = true;


			for (int j = 0; j <= pos; j++)
			{
				if (strcmp(str[j].c_str(), "-name") == 0)
				{
					name[name_length] = str[j + 1];
					name_length++;
				}
				if (strcmp(str[j].c_str(), "-size") == 0)
					size = str[j + 1];
				if (strcmp(str[j].c_str(), "-iname") == 0)
				{
					iname[iname_length] = str[j + 1];
					iname_length++;
				}

				if (strcmp(str[j].c_str(), "-maxdepth") == 0)
					maxdepth = str[j + 1];
				if (strcmp(str[j].c_str(), "-mindepth") == 0)
					mindepth = str[j + 1];
				if (strcmp(str[j].c_str(), "-atime") == 0)
					atime = str[j + 1];
				if (strcmp(str[j].c_str(), "-amin") == 0)
					amin = str[j + 1];
				if (strcmp(str[j].c_str(), "-mtime") == 0)
					mtime = str[j + 1];
				if (strcmp(str[j].c_str(), "-mmin") == 0)
					mmin = str[j + 1];
				if (strcmp(str[j].c_str(), "-newer") == 0)
					newer = str[j + 1];
				if (strcmp(str[j].c_str(), "-empty") == 0)
					empty = false;
			}
			if (str[1].find(":", 0) != string::npos)//若为全局路径
				find_path = str[1];
			else
				find_path = cwd + str[1];



			recursive_find_1(find_path, newer);


			if (!Error(newer))
				complex_find_depth(find_path, name, size, iname, maxdepth, mindepth, atime, amin, mtime, mmin, newer, empty, name_length, iname_length);
		}

		cout << "$ " << cwd << ">";
		for (int j = 0; j < 8; j++)
		{
			str[j].erase(0, str[j].length());
			folderpath[j].erase(0, folderpath[j].length());
			pos++;
		}

		pos = 0;
		
		while (cin.get() != '\n')
		{
			cin.unget();
			cin >> str[pos];
			pos++;
		}
	}
	 return 0;
}
