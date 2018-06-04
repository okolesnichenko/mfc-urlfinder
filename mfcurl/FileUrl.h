#pragma once
#include <string>
using namespace std;

class FileUrl
{
private:
	string _name;
	string _file;
	int _line;

public:
	string GetName();
	string GetFile();
	int GetLine();
	void SetName(string *);
	void SetFile(string *);
	void SetLine(int *);

	FileUrl();
	FileUrl(string, string, int);
	~FileUrl();
};

