#ifndef FILEHANDLING_FILEHANDLING_H
#define FILEHANDLING_FILEHANDLING_H

#include<string>
#include<vector>
#include <windows.h>
#include <shlobj.h>
using namespace std;

char **getWindowsDrives();

char **getKnownWindowsFolders();

void clearArrayMemory(char** arrayToFree);

#endif //FILEHANDLING_FILEHANDLING_H
