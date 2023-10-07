#include "FileHandling.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <map>
#include <shlobj.h>
using namespace std;

char **convertToCharArr (vector<string> paths){
    short size = paths.size();

    char **returnArr =(char**)malloc(sizeof(char*)*(size+1));

    for (int i = 0; i < size + 1; i++){

        if(i == size){
            returnArr[i] = nullptr;
            break;
        }

        short innerLength = paths[i].size();
        char *InnerArr =(char*)malloc(sizeof(char)*innerLength+1);

        for (int j = 0; j < innerLength+1; j++) {
            if(j == innerLength){
                InnerArr[j] = '\0';
                break;
            }
            InnerArr[j] = paths[i][j];
        }
        returnArr[i] = InnerArr;
    }
    return returnArr;
}

char **getWindowsDrives(){

    DWORD Drives = GetLogicalDrives();
    vector<string> DriveList;
    int start = 65;
    string path;

    for(int i = 0; i < 26; i++){
        if(Drives & (1 << i)){
            char DriveLetter = char(start + i);
            string DriveLetterInString(1, DriveLetter);
            path = DriveLetterInString + ":\\";
            DriveList.push_back(path);
        }
    }
    return convertToCharArr(DriveList);
}

map<string,_GUID> InitalizeKnownFolderGuidsMapForWindows(){
    map<string,_GUID> KnownFolderGuidsMap;

    KnownFolderGuidsMap["Desktop"] = {0xB4BFCC3A, 0xDB2C, 0x424C, 0xB0, 0x29, 0x7F, 0xE9, 0x9A, 0x87, 0xC6, 0x41};
    KnownFolderGuidsMap["Documents"] = {0xFDD39AD0, 0x238F, 0x46AF, 0xAD, 0xB4, 0x6C, 0x85, 0x48, 0x03, 0x69, 0xC7};
    KnownFolderGuidsMap["Downloads"] = {0x374DE290, 0x123F, 0x4565, 0x91, 0x64, 0x39, 0xC4, 0x92, 0x5E, 0x46, 0x7B};
    KnownFolderGuidsMap["Pictures"] = {0x33E28130, 0x4E1E, 0x4676, 0x83, 0x5A, 0x98, 0x39, 0x5C, 0x3B, 0xC3, 0xBB};
    KnownFolderGuidsMap["Videos"] = {0x18989B1D, 0x99B5, 0x455B, 0x84, 0x1C, 0xAB, 0x7C, 0x74, 0xE4, 0xDD, 0xFC};

    return KnownFolderGuidsMap;
}

char **getKnownWindowsFolders(){

    const map<string,_GUID>& KnownFolderGuidsMap = InitalizeKnownFolderGuidsMapForWindows();
    vector<string> paths;

    for (const pair<string, _GUID> it: KnownFolderGuidsMap) {
        wchar_t* path;
        HRESULT folderPath = SHGetKnownFolderPath(it.second, 0, nullptr, &path);

        if(folderPath != S_OK){
            if(folderPath ==  E_FAIL) {
                paths.push_back(it.first + "does not have a path or may be a virtual folder");

            }else if(folderPath == E_INVALIDARG) {
                paths.push_back(it.first + "is not present on the system");

            }else{
                paths.push_back("There was an error looking up the path for " + it.first);
                continue;
            }
        }
        wstring ws(path);
        string str(ws.begin(), ws.end());
        paths.push_back(it.first);
        paths.push_back(str);
    }

    return convertToCharArr(paths);
}

void clearArrayMemory(char** arrayToFree){
    int k = 0;
    while (true){
        if (arrayToFree[k] != nullptr ){
            char *tempPtr = arrayToFree[k++];
            free(tempPtr);
            continue;
        }
        break;
    }
    free(arrayToFree);
}

