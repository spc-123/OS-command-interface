#include "pch.h"
#include"Command.h"

string cwd = "0";
int spacenum = -1;//ls_R函数中用来输出空格个数以便输出对齐

void ls(string path) {

	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //文件信息读取结构
	string p;
	int i = 0;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			//如果文件是目录且文件不是隐藏文件
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) { 
				//不是.或者..
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					cout <<left<<setw(32)<< FindFileData.cFileName ;
					i++;
					if (i % 4==0)
						cout << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				cout << left << setw(32) << FindFileData.cFileName;
				i++;
				if (i % 4 == 0)
					cout << endl;
			}

		} while (FindNextFileA(hFile, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFile);
	}
	cout << endl;
}

string filetype(WIN32_FIND_DATAA FindFileData)
{
	string temp; 
	temp.append(FindFileData.cFileName);
	if (temp.find(".txt")!=string::npos)
		return "txt文档";
	else if (temp.find(".doc") != string::npos)
		return "doc文档";
	else if (temp.find(".rar") != string::npos)
		return "压缩文件";
	else if (temp.find(".avi") != string::npos)
		return "avi文件";
	else if (temp.find(".cpp") != string::npos)
		return "c++源文件";
	else if (temp.find(".h") != string::npos)
		return "c++头文件";
	else if (temp.find(".pdf") != string::npos)
		return "pdf文件";
	else if (temp.find("mp3") != string::npos|| temp.find("Mp3") != string::npos)
		return "音乐文件";
	else if (temp.find("mp4") != string::npos || temp.find("Mp4") != string::npos)
		return "视频文件";
	else if (temp.find(".exe") != string::npos)
		return "可执行文件";
	else
		return "其他文件";
}

float Ceil(float num)
{
	float Num = 0;
	while (Num <= num)
	{
		Num++;
	}
	return Num;
}

void ls_l(string path)
{
	static int flag = 0;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };
	string p;
	string str_show;
	string filepath;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					//if (flag == 0)
					//{
						cout << left << setw(48) << FindFileData.cFileName;
					//}
					//flag++;

					//ls_l(p.assign(path).append("\\").append("\\").append(FindFileData.cFileName));

					//flag--;
					//if (flag == 0) {
						//cout << left << setw(16) << length/1024+1<<"KB";
						cout << left << setw(16) << FindFileData.nFileSizeLow;
						cout << left << setw(8) << FindFileData.dwFileAttributes;
						FILETIME  ftAccess = FindFileData.ftLastAccessTime;
						SYSTEMTIME stUTC, stLocal;
						FileTimeToSystemTime(&ftAccess, &stUTC);
						SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
						str_show.append(to_string(stLocal.wYear)).append("/").append(to_string(stLocal.wMonth)).append("/").append(to_string(stLocal.wDay)).append(" ")
							.append(to_string(stLocal.wHour)).append(":").append(to_string(stLocal.wMinute)).append(":").append(to_string(stLocal.wSecond));
						cout << left << setw(32) << str_show;
						str_show.clear();
						cout << "文件夹" << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
					//}
				}
			}

			//else if (flag == 0) {
			else{
				cout << left << setw(48) << FindFileData.cFileName;
				string temp;
				
				cout << left << setw(16) << temp.append(to_string((int)Ceil(FindFileData.nFileSizeLow /1024))).append("KB");
				cout << left << setw(8) << FindFileData.dwFileAttributes;

				FILETIME  ftAccess = FindFileData.ftLastAccessTime;
				SYSTEMTIME stUTC, stLocal;
				FileTimeToSystemTime(&ftAccess, &stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
				str_show.append(to_string(stLocal.wYear)).append("/").append(to_string(stLocal.wMonth)).append("/").append(to_string(stLocal.wDay)).append(" ")
					.append(to_string(stLocal.wHour)).append(":").append(to_string(stLocal.wMinute)).append(":").append(to_string(stLocal.wSecond));
				cout << left << setw(32) << str_show;
				str_show.clear();
				cout << filetype(FindFileData) << endl;
			}
			//else {
			//	length = length + FindFileData.nFileSizeLow;
			//}
		} while (FindNextFileA(hFile, &FindFileData) != 0);
		FindClose(hFile);
	}
}

void ls_a(string path) {

	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //很少用的文件信息读取结构
	string p;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {  //比较文件类型是否是文件夹
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
				cout << FindFileData.cFileName << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
			}
			else {
				cout << FindFileData.cFileName << endl;
			}
		} while (FindNextFileA(hFile, &FindFileData) != 0);
		FindClose(hFile);
	}
}

void ls_d(string path) {
	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //很少用的文件信息读取结构
	string p;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					cout << FindFileData.cFileName << endl;
				}
			}
		} while (FindNextFileA(hFile, &FindFileData) != 0);  //寻找下一个，成功返回1，否则0
		FindClose(hFile);
	}
}
void ls_A(string path) {

	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //很少用的文件信息读取结构
	string p;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					cout << FindFileData.cFileName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
				}
			}
			else {
				cout << FindFileData.cFileName << endl;
			}
		} while (FindNextFileA(hFile, &FindFileData) != 0);  //寻找下一个，成功返回1，否则0
		FindClose(hFile);
	}
}

void ls_R(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFile = INVALID_HANDLE_VALUE; //很少用的文件信息读取结构
	string p;
	if ((hFile = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		spacenum++;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (spacenum > 0)
						cout <<right<< setw(spacenum * 2) << "|";
					cout << FindFileData.cFileName << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					ls_R(p.assign(path).append("\\").append("\\").append(FindFileData.cFileName));
					spacenum--;
				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				if (spacenum > 0)
					cout << right << setw(spacenum * 2) << "|";
				cout << FindFileData.cFileName << endl;
			}

		} while (FindNextFileA(hFile, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFile);
	}
}

void ls_m(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;  //很少用的文件信息读取结构
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					cout << path << left << setw(4) << "," << FindFileData.cFileName << endl;
					ls_m(p.assign(path).append("\\").append(FindFileData.cFileName));
				}
			}
			else if (!(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {
				cout << path << left << setw(4) << "," << FindFileData.cFileName << endl;
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}
}

void Mkdir(string folderpath)
{
		if (!CreateDirectoryA(folderpath.c_str(), NULL))
			cout << "Fail to create directory!" << endl;
}

void Mkdir_p(string path)
{
	int lp = 0, rp = 0;
	string folderpath;
	rp = path.find("\\", 4);
	do
	{
		folderpath = folderpath + path.substr(lp, rp - lp);
		if (!CreateDirectoryA(folderpath.c_str(), NULL))
			cout << "Fail to create file!" << endl;
		lp = rp;
		if (rp < path.length())
		{
			rp = path.find('\\', rp + 2);
			if (rp == string::npos)
				rp = path.length();
		}
	} while (lp != rp);
}

//建立目录的同时设置目录的权限；
void Mkdir_m(string folderpath, string num)
{
	char *end;
	BOOL BFlag = CreateDirectoryA(folderpath.c_str(), NULL);
	if (BFlag == ERROR_ALREADY_EXISTS)
		cout << "The goal file has existed!" << endl;
	else if (BFlag == ERROR_PATH_NOT_FOUND)
		cout << "One or more intermediate directories do not exist" << endl;
	//1只读，2隐藏，3系统文件.4普通文件
	switch (strtol(num.c_str(), &end, 10))
	{
	case 1:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_READONLY);
		break;
	case 2:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_HIDDEN);
		break;
	case 3:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_SYSTEM);
		break;
	case 4:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_NORMAL);
		break;
	default:
		break;
	}
}

void touch(string filename)
{
	string folderpath = filename;
	HANDLE hFile = CreateFileA(folderpath.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		cout << "Fail to create the file!" << endl;
	CloseHandle(hFile);
}

void touch_a(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFile = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFile,
		(LPFILETIME)NULL,
		&ft,
		(LPFILETIME)NULL);
	CloseHandle(hFile);
}

void touch_m(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFile = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFile,
		(LPFILETIME)NULL,
		(LPFILETIME)NULL,
		&ft);
	CloseHandle(hFile);
}

void touch_r(string sourcepath, string goalpath)
{
	HANDLE hsourFile = CreateFileA(
		sourcepath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hgoalFile = CreateFileA(
		goalpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	FILETIME lpCreationTime = { 0 };
	FILETIME lpLastAccessTime = { 0 };
	FILETIME lpLastWriteTime = { 0 };

	GetFileTime(
		hsourFile,
		&lpCreationTime,
		&lpLastAccessTime,
		&lpLastWriteTime
	);

	SetFileTime(hgoalFile,
		&lpCreationTime,
		&lpLastAccessTime,
		&lpLastWriteTime);
	CloseHandle(hsourFile);
	CloseHandle(hgoalFile);
}

void TimetToFileTime(time_t t, FILETIME &pft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	pft.dwLowDateTime = (DWORD)ll;
	pft.dwHighDateTime = ll >> 32;
}

time_t DateToTimet(const char* ptime)
{
	struct tm stm;
	int iY, iM, iD, iH, iMin, iS;

	memset(&stm, 0, sizeof(stm));
	iY = atoi(ptime);
	iM = atoi(ptime + 5);
	iD = atoi(ptime + 8);
	iH = atoi(ptime + 10);
	iMin = atoi(ptime + 13);
	iS = atoi(ptime + 16);

	stm.tm_year = iY - 1900;
	stm.tm_mon = iM - 1;
	stm.tm_mday = iD;
	stm.tm_hour = iH;
	stm.tm_min = iMin;
	stm.tm_sec = iS;

	return mktime(&stm);
}

void touch_d(string filepath, const char* ptime)
{
	//const char *str_time = "2011-12-31 11:43:07";
	time_t t = DateToTimet(ptime);
	FILETIME pft = { 0 };
	TimetToFileTime(t, pft);
	HANDLE hFile = CreateFileA(
		filepath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL);
	SetFileTime(hFile,		        // Sets last-write time of the file 
		NULL,           // to the converted current system time 
		NULL,
		&pft);
	CloseHandle(hFile);
}
BOOL DisplayError(BOOL ReadFlag, BOOL WriteFlag, DWORD Readlength, DWORD Writtenlength)
{
	BOOL Flag = TRUE;
	if (FALSE == WriteFlag)
	{
		cout << "Terminal failure: Unable to write to  goal file.\n";
		Flag = FALSE;
	}
	else if (FALSE == ReadFlag)
	{
		Flag = FALSE;
		cout << "Terminal failure: Unable to read source file.\n";
	}
	else
	{
		if (Readlength != Writtenlength)
		{


			{
				Flag = FALSE;
				cout << "Error: dwBytesWritten != dwBytesToWrite\n";
			}
		}
	}
	return Flag;
}
void cp(string sourcefile, string goalfile)
{
	HANDLE m_hFile = (HANDLE)CreateFileA(sourcefile.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		m_hFile = NULL;
		cout << "Fail to open the source file!"<<endl;
	}
	HANDLE hFile = (HANDLE)CreateFileA(goalfile.c_str(),                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	DWORD dw = GetLastError();
	if (dw == 183)
		cout << "The file has already  existed!" << endl;

	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = NULL;
		cout << "Fail to create the goal file!" << endl;
	}

	DWORD filesize = GetFileSize(m_hFile, NULL);//源文件的长度
	DWORD dwFileSize = 1024;//每次读取的文件长度
	char *pBuffer = new char[dwFileSize];//接收读取的字节
	DWORD dwReadSize;//实际读取或写入字节数的指针，
	//指向一个DWORD类型变量的指针，用来接收读取的字节数。如果下一个参数为NULL，那么一定要传入这个参数
	DWORD dwBytesWritten=0;
	BOOL bWriteErrorFlag, bReadErrorFlag;

	while ((bReadErrorFlag = ReadFile(m_hFile,
		pBuffer,
		dwFileSize,
		&dwReadSize,
		NULL)) && dwReadSize > 0)
	{

		bWriteErrorFlag = WriteFile(
			hFile,           // open file handle
			pBuffer,      // start of data to write
			dwReadSize,  // number of bytes to write
			&dwBytesWritten, // number of bytes that were written
			NULL);            // no overlapped structure
		DisplayError(bReadErrorFlag,
			bWriteErrorFlag,
			dwReadSize,
			dwBytesWritten);
	}
	delete[]pBuffer;//释放资源
	CloseHandle(m_hFile);
	CloseHandle(hFile);
}

void cp_R(string sourcedir, string goaldir)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string sfile, gfile;
	int pos = sourcedir.rfind("\\", sourcedir.length());
	if(pos!=string::npos)
	goaldir.append("\\").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	else
		goaldir.append("/").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	HANDLE m_hFile = (HANDLE)CreateDirectoryA(goaldir.c_str(), NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error" << endl;
		return;
	}
	if ((hFind = FindFirstFileA(p.assign(sourcedir).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					cp_R(p.assign(sourcedir).append("\\").append(FindFileData.cFileName), goaldir);
				}
			}
			else
			{
				sfile = sourcedir;
				gfile = goaldir;
				sfile.append("/").append(FindFileData.cFileName);
				gfile.append("/").append(FindFileData.cFileName);
				cp(sfile, gfile);
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

void rm_R(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string dir, file;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		dir = path;
		do
		{
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				file = path;
				if (DeleteFileA(file.append("\\").append(FindFileData.cFileName).c_str()) == ERROR_ACCESS_DENIED)
					cout << "File don't exist:" << FindFileData.cFileName << endl;
			}
			else
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					rm_R(p.assign(path).append("\\").append(FindFileData.cFileName));
				}
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		RemoveDirectoryA(dir.c_str());
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

void rm(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	if ((hFind = FindFirstFileA(path.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			cout << "This is not a file,but a directory!Please use \"rmdir\"or \"rm -i(-R)\"" << endl;
		else
			DeleteFileA(path.c_str());
	}
}

void rm_i(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	string YN;
	if ((hFind = FindFirstFileA(path.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			cout << "Remove " << FindFileData.cFileName << "?";
			cin >> YN;
			if (YN == "Y" || YN == "y")
			{
				RemoveDirectoryA(path.c_str());
				DWORD dw = GetLastError();
				if (dw == 145)
					cout << "The directory isn't empty!" << endl;
			}
			getchar();
		}
		else {
			cout << "Remove " << FindFileData.cFileName << "? Y or N";
			cin >> YN;
			if (YN == "Y" || YN == "y")

				DeleteFileA(path.c_str());
			getchar();//取出cin流末尾的换行符
		}
	}
}

void rmdir(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string  file;
	static string dir = path;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
					rmdir(p.assign(path).append("\\").append(FindFileData.cFileName));
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		if (dir != path)
		{
			RemoveDirectoryA(path.c_str());
			DWORD dw = GetLastError();
			if (dw == 145)
				cout << "The directory isn't empty!" << endl;
		}
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

void rmdir_p(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
					rm_R(p.assign(path).append("\\").append(FindFileData.cFileName));
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
			RemoveDirectoryA(path.c_str());
			DWORD dw = GetLastError();
			if (dw == 145)
				cout << "The directory isn't empty!" << endl;
			else
				cout << "The directory has deleted:" << path << endl;

		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

/*string getDriveStrings()
{
	char szBuf[100];
	memset(szBuf, 0, 100);
	DWORD len = GetLogicalDriveStringsA(sizeof(szBuf) / sizeof(TCHAR), szBuf);
	string s = (string)szBuf;
	return s;
}*/

void cd(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	if (path == "..")
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
	else if (path == "..\..")
	{
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
	}
	else if (path == "~")
		cwd = cwd.substr(0, 2);
	else
	{
		if (FindFirstFileA(path.c_str(), &FindFileData) != INVALID_HANDLE_VALUE
			&& (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (path.size() <= 4 && path.size() > 2)
				cwd = path.substr(0, 2);
			else
				cwd = path;
		}
		else if (GetDriveTypeA(path.c_str()) != DRIVE_NO_ROOT_DIR)
		{
			if (path.size() <= 4 && path.size() > 2)
				cwd = path.substr(0, 2);
			else
				cwd = path;
		}
		else
			cout << "The path isn't a right directory,please check again!" << endl;
	}
}
void cat(string path,BOOL pFlag)
{
	HANDLE hFile = (HANDLE)CreateFileA(path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	DWORD filesize = GetFileSize(hFile, NULL);//源文件的长度
	DWORD dwFileSize = 1024;//每次读取的文件长度
	char *pBuffer = new char[dwFileSize];//接收读取的字节
	DWORD dwReadSize;//实际读取或写入字节数的指针，
	BOOL Flag = FALSE;
	static COORD curser_position;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	HANDLE hOut;
	int line = 1;
	do {
		if (Flag)
		{
			SetConsoleCursorPosition(hOut, curser_position);
		}
		ReadFile(hFile,
			pBuffer,
			dwFileSize,
			&dwReadSize,
			NULL);
		if (!pFlag)
		{
			if (dwReadSize != dwFileSize)
			{
				for (int i = 0; i < dwReadSize; i++)
					cout << pBuffer[i];
				break;
			}
			else
				cout << pBuffer;
		}
		else
		{
			for (int i = 0; i < dwReadSize; i++)
			{
				cout << pBuffer[i];
				if (pBuffer[i] == '\n')
				{
					cout << line;
					line++;
				}
			}
			if (dwReadSize != dwFileSize)
				break;
		}
		Flag = TRUE;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hOut, &bInfo);
		curser_position.X = bInfo.dwCursorPosition.X-2;
		curser_position.Y = bInfo.dwCursorPosition.Y;

		cout << "More--";
	} while (cin.get() == '\n');
	cout << endl;
	delete[]pBuffer;
	CloseHandle(hFile);
}

void mv(string sourcepath,string goalpath)
{
	MoveFileExA(sourcepath.c_str(), goalpath.c_str(), MOVEFILE_COPY_ALLOWED);
	cout << GetLastError() << endl;
}
