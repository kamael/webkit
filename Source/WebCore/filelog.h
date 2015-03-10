#ifndef Filelog_H
#define Filelog_H

#include <fstream>

static void FileLog(const char* s)
{
    static std::ofstream FileOut("/home/haha/code/file.log");
    FileOut << s << std::endl;
}

#endif
