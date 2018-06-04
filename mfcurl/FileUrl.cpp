#include "stdafx.h"
#include "FileUrl.h"
#include <string>


string FileUrl::GetName()
{
	return _name;
}

string FileUrl::GetFile()
{
	return _file;
}

int FileUrl::GetLine()
{
	return _line;
}

void FileUrl::SetName(string * name)
{
	this->_name = *name;
}

void FileUrl::SetLine(int *line)
{
	this->_line = *line;
}

void FileUrl::SetFile(string * file)
{
	this->_file = *file;
}

FileUrl::FileUrl()
{

}

FileUrl::FileUrl(string name, string file, int line)
{
	SetName(&name);
	SetFile(&file);
	SetLine(&line);
}


FileUrl::~FileUrl()
{
}
