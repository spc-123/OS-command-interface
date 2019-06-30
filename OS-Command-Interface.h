
#include "pch.h"
#include"OS-Command-Interface.h"
string cwd = "0";
int spacenum = -1;//ls_R函数中用来输出空格个数以便输出对齐同时是遍历的深度

const IOPUT& IOPUT::operator<<(string str)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//重载对字符的输出
	DWORD dwBytesWritten = 0;
	int length = total - str.length();
	for (int i = 0; i < length; i++)
		str += " ";
	WriteFile(
		hOut,
		str.c_str(),
		str.length (),
		&dwBytesWritten,
		NULL);
	total = 0;
	return *this;
}
const IOPUT& IOPUT::operator << (char ch)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//重载对字符的输出
	DWORD dwBytesWritten = 0;
	char pBuff[1];
	pBuff[0]= ch;
	WriteFile(
		hOut,
		pBuff,
		1,
		&dwBytesWritten,
		NULL);
	total = 0;
	return *this;
}

const IOPUT& IOPUT::operator << (string str)const
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//重载对字符的输出
	DWORD dwBytesWritten = 0;
	int length = total - str.length();
	for (int i = 0; i < length; i++)
		str += " ";
	WriteFile(
		hOut,
		str.c_str(),
		str.length(),
		&dwBytesWritten,
		NULL);
	return *this;
}

const IOPUT& IOPUT::operator << (int Value)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//重载对字符的输出
	DWORD dwBytesWritten = 0;
	string str = {};
	str.append(to_string(Value));
	int length = total - str.length();
	for (int i = 0; i < length; i++)
		str += " ";
	WriteFile(
		hOut,
		str.c_str(),
		str.length(),
		&dwBytesWritten,
		NULL);
	total = 0;
	return *this;
}

string IOPUT::setw(int num)
{
	total = num;
	return "";
}

IOPUT put;//创建一个输出字符的对象

void ls(string path) {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //文件信息读取结构
	string p;
	int i = 0;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			//如果文件是目录且文件不是隐藏文件
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {
				//不是.或者..
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					//put << left << setw(32) << FindFileData.cFileName;
					put <<FindFileData.cFileName<< put.setw(32);
					i++;
					if (i % 4 == 0)
						put << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				//put << left << setw(32) << FindFileData.cFileName;
				put << FindFileData.cFileName << put.setw(32);
				i++;
				if (i % 4 == 0)
					put << "\n" ;
			}

		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}
	put << "\n" ;
}

string filetype(WIN32_FIND_DATAA FindFileData)
{
	string temp;
	temp.append(FindFileData.cFileName);
	if (temp.find(".txt") != string::npos)
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
	else if (temp.find("mp3") != string::npos || temp.find("Mp3") != string::npos)
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

struct info {
	string name;
	string size;
	string attribute;
	string date;
	string time;
	string type;
};

long StoI(string str)
{
	int i = 0;
	int sum = 0, pow = 10;
	while (i < str.length())
	{
		if(str[i] != ':'&&str[i] != '/')
			sum = sum * pow + (str[i] - '0');
		i++;
	}
	return sum;
}

int Find(string path,info fileinfo[])
{
	static int flag = 0;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };
	string p;
	int pos = 0;
	string str_date, str_time;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {


					fileinfo[pos].name = FindFileData.cFileName;
					fileinfo[pos].size = to_string(FindFileData.nFileSizeLow);
					fileinfo[pos].attribute = to_string(FindFileData.dwFileAttributes);

					FILETIME  ftAccess = FindFileData.ftLastWriteTime;
					SYSTEMTIME stUTC, stLocal;
					FileTimeToSystemTime(&ftAccess, &stUTC);
					SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
					str_date.append(to_string(stLocal.wYear)).append("/").append(to_string(stLocal.wMonth)).append("/").append(to_string(stLocal.wDay));
					str_time.append(to_string(stLocal.wHour)).append(":").append(to_string(stLocal.wMinute)).append(":").append(to_string(stLocal.wSecond));

					fileinfo[pos].date = str_date;
					fileinfo[pos].time = str_time;
					fileinfo[pos++].type = "文件夹";

					str_date.clear();
					str_time.clear();

					//}
				}
			}

			//else if (flag == 0) {
			else {
				string size;
				size.append(to_string((int)Ceil((float)FindFileData.nFileSizeLow / 1024))).append("KB");
				//temp.append(FindFileData.cFileName).append(size).append(to_string(FindFileData.dwFileAttributes));
				fileinfo[pos].name = FindFileData.cFileName;
				fileinfo[pos].size = size;
				fileinfo[pos].attribute = to_string(FindFileData.dwFileAttributes);

				FILETIME  ftAccess = FindFileData.ftLastWriteTime;
				SYSTEMTIME stUTC, stLocal;
				FileTimeToSystemTime(&ftAccess, &stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
				str_date.append(to_string(stLocal.wYear)).append("/").append(to_string(stLocal.wMonth)).append("/").append(to_string(stLocal.wDay));
				str_time.append(to_string(stLocal.wHour)).append(":").append(to_string(stLocal.wMinute)).append(":").append(to_string(stLocal.wSecond));

				fileinfo[pos].date = str_date;
				fileinfo[pos].time = str_time;
				fileinfo[pos++].type = filetype(FindFileData);

				str_date.clear();
				str_time.clear();
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	return pos;
}
void show(info fileinfo[],int pos)
{
	for (int i = 0; i < pos; i++)
	{
		if (fileinfo[i].type == "文件夹")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
				FOREGROUND_BLUE);
			put << fileinfo[i].name << put.setw(32);
			put << fileinfo[i].size << put.setw(10);
			put << fileinfo[i].attribute << put.setw(10);
			put << fileinfo[i].date << put.setw(11);
			put << fileinfo[i].time << put.setw(16) << fileinfo[i].type << "\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
				FOREGROUND_BLUE);
		}
		else
		{
			put << fileinfo[i].name << put.setw(32);
			put << fileinfo[i].size << put.setw(10);
			put << fileinfo[i].attribute << put.setw(10);
			put << fileinfo[i].date << put.setw(11);
			put << fileinfo[i].time << put.setw(16) << fileinfo[i].type << "\n";
		}
	}
}
void ls_S(string path,string option)
{
	info fileinfo[1024];
	int pos=Find(path, fileinfo);
	if (option == "--sort=size")
	{
		for (int i = 0; i < pos; i++)
			for (int j = i + 1; j < pos; j++)
			{
				if (StoI(fileinfo[i].size.substr (0, fileinfo[i].size.find("K",0)))>StoI(fileinfo[j].size.substr(0, fileinfo[j].size.find("K", 0))))
				{
					info temp = fileinfo[i];
					fileinfo[i] = fileinfo[j];
					fileinfo[j] = temp;
				}
			}
	}
	else if ((option == "--sort=atime"))
	{
		for (int i = 0; i < pos; i++)
			for (int j = i + 1; j < pos; j++)
			{
				if (StoI(fileinfo[i].date)>StoI(fileinfo[j].date)|| (StoI(fileinfo[i].date) == StoI(fileinfo[j].date) && StoI(fileinfo[i].time) > StoI(fileinfo[j].time)))
				{
					info temp = fileinfo[i];
					fileinfo[i] = fileinfo[j];
					fileinfo[j] = temp;
				}
			}
	}
	else
		put << option<<"The input is incorrect!" << "\n";
	show(fileinfo,pos);
}

void ls_l(string path)
{
	info fileinfo[1024];
	int pos=Find(path, fileinfo);
	show(fileinfo,pos);
}

void ls_a(string path) {

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //很少用的文件信息读取结构
	string p;
	int i = 0;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {  //比较文件类型是否是文件夹
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
				put << FindFileData.cFileName << put.setw(32);
				i++;
				if (i % 4 == 0)
					put << "\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
			}
			else {
				put << FindFileData.cFileName << put.setw(32);
				i++;
				if (i % 4 == 0)
					put << "\n";
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	put << "\n";
}

void ls_d(string path) {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };
	string p;
	int i = 0;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					put << FindFileData.cFileName << put.setw(32);
					i++;
					if (i % 4 == 0)
						put << "\n";
				}
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回1，否则0
		FindClose(hFind);
	}
	put << "\n";
}
void ls_A(string path) {

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData = { 0 };  //很少用的文件信息读取结构
	string p;
	int i = 0;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					put << FindFileData.cFileName << put.setw(32);
					i++;
					if (i % 4 == 0)
						put << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
				}
			}
			else {
				put << FindFileData.cFileName << put.setw(32);
				i++;
				if (i % 4 == 0)
					put << "\n";
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回1，否则0
		FindClose(hFind);
	}
	put << "\n";
}

void ls_R(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE; //很少用的文件信息读取结构
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		spacenum++;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (spacenum > 0)
						put << put.setw(spacenum * 2) << "|";
					put << FindFileData.cFileName << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					ls_R(p.assign(path).append("\\").append("\\").append(FindFileData.cFileName));
					spacenum--;
				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				if (spacenum > 0)
					put << put.setw(spacenum * 2) << "|" ;
				put << FindFileData.cFileName << "\n";
			}

		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}
}

void ls_m(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE); 
					put << path << put.setw(4) << "," << FindFileData.cFileName << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					ls_m(p.assign(path).append("\\").append(FindFileData.cFileName));
				}
			}
			else if (!(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
				put << path  << put.setw(4) << ",";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
				put << FindFileData.cFileName << "\n";
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}
}

void Mkdir(string folderpath)
{
	if (!CreateDirectoryA(folderpath.c_str(), NULL))
		put << "Fail to create directory!" << "\n";
}

void Mkdir_p(string path)
{
	unsigned int lp = 0, rp = 0;
	BOOL Flag=FALSE;
	string folderpath;
	if (path.find("\\", 4) !=string::npos)
		rp = path.find("\\", 2);
	else
		rp = path.find("/", 2);
	do
	{
		folderpath = folderpath + path.substr(lp, rp - lp);
		if (!CreateDirectoryA(folderpath.c_str(), NULL) && Flag)
			put << "Fail to create directory!"<<"\n";
		lp = rp;
		if (rp < path.length())
		{
			if (path.find('\\', rp + 2) != string::npos)
				rp = path.find('\\', rp + 2);
			else
				rp = path.find('/', rp + 2);
			if (rp == string::npos)
			{
				rp = path.length();
				Flag = TRUE;
			}
		}
	} while (lp != rp);
}

//建立目录的同时设置目录的权限；
void Mkdir_m(string folderpath, string num)
{
	char *end;
	BOOL BFlag = CreateDirectoryA(folderpath.c_str(), NULL);
	if (BFlag == ERROR_ALREADY_EXISTS)
		put << "The goal file has existed!" << "\n";
	else if (BFlag == ERROR_PATH_NOT_FOUND)
		put << "One or more intermediate directories do not exist" << "\n";
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
	HANDLE hFind = CreateFileA(folderpath.c_str(),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, 
		0);
	if (hFind == INVALID_HANDLE_VALUE)
		put << "Fail to create the file!" << "\n";
	CloseHandle(hFind);
}

void touch_a(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFind = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFind,
		(LPFILETIME)NULL,
		&ft,
		(LPFILETIME)NULL);
	CloseHandle(hFind);
}

void touch_m(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFind = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFind,
		(LPFILETIME)NULL,
		(LPFILETIME)NULL,
		&ft);
	CloseHandle(hFind);
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

/*void TimetToFileTime(time_t t, FILETIME &pft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	pft.dwLowDateTime = (DWORD)ll;
	pft.dwHighDateTime = ll >> 32;
}*/

FILETIME DateToFileTime(const char* ptime)
{
	//struct tm stm;
	//2020-01-0100：00：00
	FILETIME ft;
	SYSTEMTIME st;

	memset(&st, 0, sizeof(st));
	st.wYear = atoi(ptime);
	st.wMonth = atoi(ptime + 5);
	st.wDay = atoi(ptime + 8);
	st.wHour = atoi(ptime + 11)-8;
	st.wMinute = atoi(ptime + 14);
	st.wSecond = atoi(ptime + 17);

	SystemTimeToFileTime(&st, &ft);
	return ft;
}

void touch_d(string filepath, const char* ptime)
{
	//const char *str_time = "2011-12-31 11:43:07";
	//FILETIME ft = DateToTimet(ptime);
	FILETIME pft = DateToFileTime(ptime);
	//TimetToFileTime(t, pft);
	HANDLE hFind = CreateFileA(
		filepath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFind == INVALID_HANDLE_VALUE)
		hFind = CreateFileA(
			filepath.c_str(),
			GENERIC_READ | GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
	SetFileTime(hFind,		        // Sets last-write time of the file 
		&pft,           // to the converted current system time 
		&pft,
		&pft);
	CloseHandle(hFind);
}
BOOL DisplayError(BOOL ReadFlag, BOOL WriteFlag, DWORD Readlength, DWORD Writtenlength)
{
	BOOL Flag = TRUE;
	if (FALSE == WriteFlag)
	{
		put << "Terminal failure: Unable to write to  goal file.\n";
		Flag = FALSE;
	}
	else if (FALSE == ReadFlag)
	{
		Flag = FALSE;
		put << "Terminal failure: Unable to read source file.\n";
	}
	else
	{
		if (Readlength != Writtenlength)
		{


			{
				Flag = FALSE;
				put << "Error: dwBytesWritten != dwBytesToWrite\n";
			}
		}
	}
	return Flag;
}
void cp(string sourcefile, string goalfile)
{
	BOOL Flag = TRUE;
	HANDLE m_hFind = (HANDLE)CreateFileA(sourcefile.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	if (m_hFind == INVALID_HANDLE_VALUE)
	{
		m_hFind = NULL;
		put << "Fail to open the source file!" << "\n";
	}
	else {
		HANDLE hFind = (HANDLE)CreateFileA(goalfile.c_str(),                //.cFileName of the write
			GENERIC_WRITE,          // open for writing
			0,                      // do not share
			NULL,                   // default security
			CREATE_NEW,             // create new file only
			FILE_ATTRIBUTE_NORMAL,  // normal file
			NULL);

		DWORD dw = GetLastError();
		if (dw == 183 || dw == 80)
		{
			CHAR YN=' ';
			Flag = FALSE;
			put << "The file has already  existed! \nWhether to create a backup copy:y/n" << "\n";
			put >> YN;
			if (YN == 'y' || YN == 'Y')
			{
				Flag = TRUE;
				hFind = (HANDLE)CreateFileA(goalfile.insert(goalfile.find_last_of("."), "副本").c_str(),  //.cFileName of the write
					GENERIC_WRITE,          // open for writing
					0,                      // do not share
					NULL,                   // default security
					CREATE_NEW,             // create new file only
					FILE_ATTRIBUTE_NORMAL,  // normal file
					NULL);
			}
			getchar();
		}

		if (hFind == INVALID_HANDLE_VALUE)
		{
			Flag = FALSE;
			hFind = NULL;
			put << "Fail to create the goal file!" << "\n";
		}
		else {
			DWORD filesize = GetFileSize(m_hFind, NULL);//源文件的长度
			DWORD dwFileSize = 1024;//每次读取的文件长度
			char *pBuffer = new char[dwFileSize];//接收读取的字节
			DWORD dwReadSize;//实际读取或写入字节数的指针，
			//指向一个DWORD类型变量的指针，用来接收读取的字节数。如果下一个参数为NULL，那么一定要传入这个参数
			DWORD dwBytesWritten = 0;
			BOOL bWriteErrorFlag, bReadErrorFlag;

			while (Flag && (bReadErrorFlag = ReadFile(m_hFind,
				pBuffer,
				dwFileSize,
				&dwReadSize,
				NULL)) && dwReadSize > 0)
			{

				bWriteErrorFlag = WriteFile(
					hFind,           // open file handle
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
			CloseHandle(hFind);
		}
	}
	CloseHandle(m_hFind);
}

void cp_R(string sourcedir, string goaldir)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string sfile, gfile;
	int pos = sourcedir.rfind("\\", sourcedir.length());
	if (pos != string::npos)
		goaldir.append("\\").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	else
		goaldir.append("/").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	HANDLE m_hFind = (HANDLE)CreateDirectoryA(goaldir.c_str(), NULL);
	if (m_hFind == INVALID_HANDLE_VALUE)
	{
		put << "Error" << "\n";
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
					put << "File don't exist:" << FindFileData.cFileName << "\n";
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
			put << "This is not a file,but a directory!Please use \"rmdir\"or \"rm -i(-R)\"" << "\n";
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
			put << "Remove " << FindFileData.cFileName << "?";
			put >> YN;
			if (YN == "Y" || YN == "y")
			{
				RemoveDirectoryA(path.c_str());
				DWORD dw = GetLastError();
				if (dw == 145)
					put << "The directory isn't empty!" << "\n";
			}
			getchar();
		}
		else {
			put << "Remove " << FindFileData.cFileName << "? Y or N:";
			YN = getchar();
			if (YN == "Y" || YN == "y")
				DeleteFileA(path.c_str());
			getchar();
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
				put << "The directory isn't empty!" << "\n";
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
			put << "The directory isn't empty!" << "\n";
		else
			put << "The directory has deleted:" << path << "\n";

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
	{
		if (cwd.rfind("\\", cwd.length()) != string::npos)
			cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
		else
			cwd = cwd.substr(0, cwd.rfind("/", cwd.length()));
	}
	else if (path == "..\\..")
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
			put << "The path isn't a right directory,please check again!" << "\n";
	}
}
void cat(string path, BOOL pFlag)
{
	HANDLE hFind = (HANDLE)CreateFileA(path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	DWORD filesize = GetFileSize(hFind, NULL);//源文件的长度
	DWORD dwFileSize = 1024;//每次读取的文件长度
	char *pBuffer = new char[dwFileSize];//接收读取的字节
	DWORD dwReadSize;//实际读取或写入字节数的指针，
	BOOL Flag = FALSE;
	static COORD curser_position;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	HANDLE hOut=NULL;
	int line = 1;
	char ch = '\n';
	do {
		if (Flag)
		{
			SetConsoleCursorPosition(hOut, curser_position);
		}
		ReadFile(hFind,
			pBuffer,
			dwFileSize,
			&dwReadSize,
			NULL);
		if (!pFlag)
		{
				for (unsigned int i = 0; i < dwReadSize; i++)
					put << pBuffer[i];
				if (dwReadSize != dwFileSize)
					break;
		}
		else
		{
			for (unsigned int i = 0; i < dwReadSize; i++)
			{
				put << pBuffer[i];
				if (pBuffer[i] == '\n')
				{
					put << line;
					line++;
				}
			}
			if (dwReadSize != dwFileSize)
				break;
		}
		Flag = TRUE;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hOut, &bInfo);
		curser_position.X = bInfo.dwCursorPosition.X - 2;
		curser_position.Y = bInfo.dwCursorPosition.Y;

		put <<"More--";
		ch = getchar();
	} while (ch == '\n');
	put << "\n";
	getchar();
	delete[]pBuffer;
	CloseHandle(hFind);
}

void mv(string sourcepath, string goalpath)
{
	//判断goalpath是目录还是文件
	WIN32_FIND_DATAA FindFileData_source = { 0 };
	WIN32_FIND_DATAA FindFileData_goal = { 0 };
	HANDLE hFind_source = INVALID_HANDLE_VALUE;
	HANDLE hFind_goal = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string dir, file;
	hFind_source = FindFirstFileA(p.assign(sourcepath).append("\\*").c_str(), &FindFileData_source);
	hFind_goal = FindFirstFileA(p.assign(goalpath).append("\\*").c_str(), &FindFileData_goal);

	if (hFind_source != INVALID_HANDLE_VALUE&& hFind_goal!= INVALID_HANDLE_VALUE)
	{
		if (!(FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))// source为文件
		{
			if ((FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))// goal 为目录

			{
				cp(sourcepath.c_str(), goalpath.append(sourcepath.substr(sourcepath.find_last_of("\\"), sourcepath.length())).c_str());
				rm(sourcepath.c_str());
			}
			else
			{
				rm(goalpath.c_str());
				rename(sourcepath.c_str(), goalpath.c_str());
			}
		}
		if ((FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) //source为目录
		{
			if (!(FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				put << "ERROR:NOT SUPPORTED" << "\n";
			}
			else
			{

				cp_R(sourcepath, goalpath);
				rm_R(sourcepath);
			}
		}
	}
	else if (hFind_source != INVALID_HANDLE_VALUE && hFind_goal == INVALID_HANDLE_VALUE)
	{
		rename(sourcepath.c_str(), goalpath.c_str());
	}
	else
		put << "ERROR:NOT SUPPORTED" << "\n";
}

int num = -1;
int length = 0;

int flag_num = 0;
FILETIME cmp_time = {};


bool Dir_IsEmpty(string path)
{
	string cp_path;
	cp_path.assign(path).append("(1)");
	CreateDirectoryA(cp_path.c_str(), NULL);
	cp_R(path, cp_path);
	if (RemoveDirectoryA(cp_path.c_str()))
		return true;
	else
		return false;
}


void recursive_find(string path, string parameter) {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData;  //很少用的文件信息读取结构
	string p;

	if ((hFind = FindFirstFileA(p.assign(path).append("\\").append("*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		num++;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {

					recursive_find(p.assign(path).append("\\").append("\\").append(FindFileData.cFileName), parameter);
					num--;
				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				if (strcmp(FindFileData.cFileName, parameter.c_str()) == 0)
				{
					flag_num++;

					cmp_time = FindFileData.ftLastWriteTime;

				}

			}

		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}
}
void  recursive_find_1(string path, string parameter)
{
	flag_num = 0;
	recursive_find(path, parameter);
}
int depth;


bool complex_find_name(WIN32_FIND_DATAA file, string name[], int num)
{
	bool name_bool = false;
	string temp;
	string name_temp;
	temp.append(file.cFileName);
	int i;
	int j = 0;
	char temp_1[10] = {};
	for (i = temp.length() - 1; i > 0; i--)
	{
		if (temp[i] != '.')
		{
			temp_1[j] = temp[i];
			j++;
		}
		else
			break;
	}
	_strrev(temp_1);
	temp = temp_1;

	if (num != 0)
	{
		for (int k = 0; k < num; k++)
		{
			if (name[k] == "")
				name_bool = true;
			else
			{
				name_temp = name[k];
				name_temp.erase(0, 3);
				name_temp.erase(name_temp.end() - 1);

				if (strcmp(temp.c_str(), name_temp.c_str()) == 0)
					name_bool = true;

			}
			if (name_bool)
				break;
		}
	}
	else
		name_bool = true;
	return name_bool;

}
bool complex_find_size(WIN32_FIND_DATAA file, string size)
{
	if (size == "")
		return true;
	else
	{
		string temp = size;
		char unit = temp.at(temp.length() - 1);
		char sign = temp.at(0);
		unsigned int number = 0;
		int currency;

		if (unit == 'b')
		{
			currency = 512;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'c')
		{
			currency = 1;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'w')
		{
			currency = 2;
			temp.erase(temp.end() - 1);
		}
		else if (unit == 'k')
		{
			currency = 1024;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'm')
		{
			currency = 1048576;
			temp.erase(temp.end() - 1);
		}
		else if (unit == 'g')
		{
			currency = 1073741824;
			temp.erase(temp.end() - 1);
		}
		else
		{
			currency = 512;
		}
		if (sign == '-')
		{
			temp.erase(0, 1);
			number = atoi(temp.c_str())*currency;
			if (file.nFileSizeLow < number)
				return true;
		}

		else if (sign == '+')
		{
			temp.erase(0, 1);
			number = atoi(temp.c_str())*currency;
			if (file.nFileSizeLow > number)
				return true;
		}
		else
		{
			number = atoi(temp.c_str())*currency;
			if (file.nFileSizeLow == number)
				return true;
		}
		return false;
	}
}
bool complex_find_empty(WIN32_FIND_DATAA file, bool empty)
{
	if (empty)
		return true;
	else
	{
		if (file.nFileSizeLow == 0)
			return true;
		else
			return false;
	}
}

string Change(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] > 'A'&&str[i] < 'Z')
			str[i] += 32;
	}
	return str;
}


bool complex_find_newer(WIN32_FIND_DATAA file, string newer)
{
	if (newer == "")
		return true;
	else
	{
		if (flag_num == 1)
		{
			if (CompareFileTime(&file.ftLastWriteTime, &cmp_time) == 1)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

bool complex_find_maxdepth(string maxdepth)
{
	if (maxdepth == "")
		return true;
	else
	{
		if (depth < atoi(maxdepth.c_str()) + 2)
			return true;
		else
			return false;
	}

}
bool complex_find_mindepth(string mindepth)
{
	if (mindepth == "")
		return true;
	else
	{
		if (depth > atoi(mindepth.c_str()))
			return true;
		else
			return false;
	}
}
bool complex_find_atime(WIN32_FIND_DATAA file, string atime)
{
	if (atime == "")
		return true;
	else
	{
		if (find_time(file, "-atime", atime))
			return true;
	}
	return false;
}


bool complex_find_mtime(WIN32_FIND_DATAA file, string mtime)
{
	if (mtime == "")
		return true;
	else
	{
		if (find_time(file, "-mtime", mtime))
			return true;
	}
	return false;
}
bool complex_find_amin(WIN32_FIND_DATAA file, string amin)
{
	if (amin == "")
		return true;
	else
	{
		if (find_time(file, "-amin", amin))
			return true;
	}
	return false;
}

bool complex_find_mmin(WIN32_FIND_DATAA file, string mmin)
{
	if (mmin == "")
		return true;
	else
	{
		if (find_time(file, "-mmin", mmin))
			return true;
	}
	return false;
}
bool complex_find_iname(WIN32_FIND_DATAA file, string iname[], int num)
{

	if (num != 0)
	{
		string iname_temp[20];
		for (int k = 0; k < num; k++)
		{
			iname_temp[k] = iname[k];
			iname_temp[k] = Change(iname_temp[k]);
		}
		if (complex_find_name(file, iname_temp, num))
			return true;
		else
			return false;
	}
	else
		return true;

}

void complex_find(string path, string name[], string size, string iname[], string maxdepth, string mindepth, string atime, string amin, string mtime, string mmin, string newer, bool empty, int name_length, int iname_length)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA FindFileData;  //很少用的文件信息读取结构
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\").append("*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		depth++;
		do {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (depth > 1)
						put << "|" << put.setw(depth * 2);
					put << FindFileData.cFileName << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					complex_find(p.assign(path).append("\\").append("\\").append(FindFileData.cFileName), name, size, iname, maxdepth, mindepth, atime, amin, mtime, mmin, newer, empty, name_length, iname_length);
					depth--;

				}
			}
			else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {

				if (complex_find_size(FindFileData, size) && complex_find_name(FindFileData, name, name_length) && complex_find_maxdepth(maxdepth) && complex_find_mindepth(mindepth) && complex_find_atime(FindFileData, atime)
					&& complex_find_mtime(FindFileData, mtime) && complex_find_amin(FindFileData, amin) && complex_find_mmin(FindFileData, mmin) && complex_find_empty(FindFileData, empty) && complex_find_iname(FindFileData, iname, iname_length) && complex_find_newer(FindFileData, newer))



				{
					if (depth > 1)
						put << "|" << put.setw(depth * 2);
					put << FindFileData.cFileName << "\n";
				}
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);  //寻找下一个，成功返回0，否则-1
		FindClose(hFind);
	}

}
void complex_find_depth(string path, string name[], string size, string iname[], string maxdepth, string mindepth, string atime, string amin, string mtime, string mmin, string newer, bool empty, int name_length, int iname_length)
{
	depth = 0;
	complex_find(path, name, size, iname, maxdepth, mindepth, atime, amin, mtime, mmin, newer, empty, name_length, iname_length);
}

bool find_time(WIN32_FIND_DATAA file, string time_option, string time_str)
{
	SYSTEMTIME  st;//当前系统时间
	FILETIME ft;//文件时间
	string temp = time_str;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	int exchange = 1;
	int delta_time;//文件时间与系统时间之差

	ULARGE_INTEGER fi, si;
	if (strcmp(time_option.c_str(), "-atime") == 0 || strcmp(time_option.c_str(), "-amin") == 0)
	{
		fi.LowPart = file.ftLastAccessTime.dwLowDateTime;
		fi.HighPart = file.ftLastAccessTime.dwHighDateTime;
		si.LowPart = ft.dwLowDateTime;
		si.HighPart = ft.dwHighDateTime;
	}
	if (strcmp(time_option.c_str(), "-mtime") == 0 || strcmp(time_option.c_str(), "-mmin") == 0)
	{
		fi.LowPart = file.ftLastWriteTime.dwLowDateTime;
		fi.HighPart = file.ftLastWriteTime.dwHighDateTime;
		si.LowPart = ft.dwLowDateTime;
		si.HighPart = ft.dwHighDateTime;
	}
	

	if (strcmp(time_option.c_str(), "-atime") == 0 || strcmp(time_option.c_str(), "-mtime") == 0)
		exchange = 60 * 24;
	if (strcmp(time_option.c_str(), "-atime") == 0 || strcmp(time_option.c_str(), "-amin") == 0)
	{
		delta_time = (LONGLONG)((si.QuadPart - 116444736000000000) / 10000000) - ((fi.QuadPart - 116444736000000000) / 10000000);
	}
	if (strcmp(time_option.c_str(), "-mtime") == 0 || strcmp(time_option.c_str(), "-mmin") == 0)
	{
		delta_time = (LONGLONG)((si.QuadPart - 116444736000000000) / 10000000) - ((fi.QuadPart - 116444736000000000) / 10000000);
	}
	char temp_char = temp.at(0);

	if (temp_char == '-')
	{
		temp.erase(0, 1);
		if (delta_time < 60 * exchange*atoi(temp.c_str()))
		{
			return true;
		}

	}
	else if (temp_char == '+')
	{
		temp.erase(0, 1);

		if (delta_time > 60 * exchange* atoi(temp.c_str()))
		{
			return true;
		}

	}
	else
	{
		if (delta_time == 60 * exchange*atoi(temp.c_str()))
			return true;
	}
	return false;
}
bool Error(string newer)
{
	bool error = false;
	if (newer != "" && flag_num > 1)
	{
		put << "ERROR:THE INPUT FILENAME IS NOT UNIQUE" << "\n";
		error = true;
	}
	if (newer != ""&&flag_num == 0)
	{
		put << "ERROR:FILENAME NOT EXIST" << "\n";
		error = true;
	}
	return error;
}
