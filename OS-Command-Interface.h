#pragma once
#include "pch.h"
#include <string>
#include <windows.h>
#ifdef CMD_EXPORTS
#define CMD_API _declspec(dllexport)
#else
#define CMD_API _declspec(dllimport)
#endif // !CMD_API
using namespace std;

extern string CMD_API cwd;//当前工作目录
extern void CMD_API ls(string path);
extern void CMD_API ls_l(string path);
extern void CMD_API ls_S(string path,string option);
extern void CMD_API ls_a(string path);
extern void CMD_API ls_d(string path);
extern void CMD_API ls_A(string path);
extern void CMD_API ls_R(string path);
extern void CMD_API ls_m(string path);
extern void CMD_API Mkdir(string folderpath);
extern void CMD_API Mkdir_p(string path);
extern void CMD_API Mkdir_m(string folderpath, string num);
extern void CMD_API touch(string filename);
extern void CMD_API touch_a(string folderpath);
extern void CMD_API touch_m(string folderpath);
extern void CMD_API touch_r(string sourcepath, string goalpath);
extern void CMD_API touch_d(string filepath, const char* ptime);
extern void CMD_API cp(string sourcefile, string goalfile);
extern void CMD_API cp_R(string sourcedir, string goaldir);
extern void CMD_API rm_R(string path);
extern void CMD_API rm(string path);
extern void CMD_API rm_i(string path);
extern void CMD_API rmdir(string path);
extern void CMD_API rmdir_p(string path);
extern void CMD_API cd(string path);
extern void CMD_API cat(string path, BOOL pFlag);
extern void CMD_API mv(string sourcepath, string goalpath);
extern bool CMD_API Dir_IsEmpty(string path);
extern void CMD_API recursive_find_1(string path, string parameter);
extern void CMD_API recursive_find(string path, string parameter);
extern void CMD_API complex_find(string path, string name[], string size, string iname[], string maxdepth, string mindepth, string atime, string amin, string mtime, string mmin, string newer, bool empty, int name_length, int iname_length);
extern void CMD_API complex_find_depth(string path, string name[], string size, string iname[], string maxdepth, string mindepth, string atime, string amin, string mtime, string mmin, string newer, bool empty, int name_length, int iname_length);
extern bool CMD_API complex_find_size(WIN32_FIND_DATAA FindFileData, string size);
extern bool CMD_API complex_find_empty(WIN32_FIND_DATAA FindFileData, bool empty);
extern bool CMD_API complex_find_iname(WIN32_FIND_DATAA FindFileData, string iname[], int num);
extern bool CMD_API complex_find_name(WIN32_FIND_DATAA FindFileData, string name[], int num);
extern bool CMD_API complex_find_newer(WIN32_FIND_DATAA FindFileData, string newer);
extern bool CMD_API complex_find_maxdepth(string maxdepth);
extern bool CMD_API complex_find_mindepth(string mindepth);
extern bool CMD_API complex_find_atime(WIN32_FIND_DATAA FindFileData, string atime);
extern bool CMD_API complex_find_mtime(WIN32_FIND_DATAA FindFileData, string mtime);
extern bool CMD_API complex_find_amin(WIN32_FIND_DATAA FindFileData, string amin);
extern bool CMD_API complex_find_mmin(WIN32_FIND_DATAA FindFileData, string mmin);
extern bool CMD_API find_time(WIN32_FIND_DATAA FindFileData, string time_option, string time_str);
extern bool CMD_API Error(string newer);
extern string  CMD_API Change(string str);
class CMD_API IOPUT //定义输出字符串的类
{
public:
	const IOPUT& operator << (string str);//对输出字符串的重载
	const IOPUT& operator << (char ch);//对输出字符串的重载
	const IOPUT& operator << (string str)const;//对输出字符串的重载
	const IOPUT& operator << (int Value);//对输出整数的重载
	string setw(int num);
private:
	int total=0;
};
