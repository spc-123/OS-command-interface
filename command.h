#pragma once
#include "pch.h"
#include<iostream>
#include <string>
#include<iomanip>
#include "windows.h"

using namespace std;

extern string cwd;//当前工作目录
extern void ls(string path);
extern void ls_l(string path);
extern void ls_a(string path);
extern void ls_d(string path);
extern void ls_A(string path);
extern void ls_R(string path);
extern void ls_m(string path);
extern void Mkdir(string folderpath);
extern void Mkdir_p(string path);
extern void Mkdir_m(string folderpath, string num);
extern void touch(string filename);
extern void touch_a(string folderpath);
extern void touch_m(string folderpath);
extern void touch_r(string sourcepath, string goalpath);
extern void touch_d(string filepath, const char* ptime);
extern void cp(string sourcefile, string goalfile);
extern void cp_R(string sourcedir, string goaldir);
extern void rm_R(string path);
extern void rm(string path);
extern void rm_i(string path);
extern void rmdir(string path);
extern void rmdir_p(string path);
extern void cd(string path);
extern void cat(string path,BOOL pFlag);
extern void mv(string sourcepath, string goalpath);
