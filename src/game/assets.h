#include <iostream>
#include <fstream>
#include <map>
#include <zlib.h>
#include <map>
#include <vector>
#include <SDL.h>

using namespace std;

#ifndef THGAME_ASSETS_H
#define THGAME_ASSETS_H

class Assets{
private:
    static Assets Instance;

    typedef struct {
        Uint32 FilePointer;
        Uint32 OriginSize;
        Uint32 CompressedSize;
    } DataTableHeader;

    typedef struct {
        Uint32 AssetsCount;
        DataTableHeader StringTable;
        DataTableHeader AssestsTableHeader;
    } GameDataHeader;

    typedef struct {
        Uint32 FilePointer;
        Uint32 OriginSize;
        Uint32 CompressedSize;
        Uint32 NamePointer;
        char Type[4];
    } AssestTableHeader;

    typedef struct {
        Uint32 FilePointer;
        Uint32 OriginSize;
        Uint32 CompressedSize;
        bool Loaded;
        char* MemoryPointer;
    } AssetTableInfo;

    typedef map<string,AssetTableInfo> AssetsTable;

    AssetsTable AssetsList;

private:
    Assets();

public:
    static Assets* GetInstance();

    bool GetAssetsList();

    SDL_RWops* GetAsset(const string& name);

    bool LoadAssetFromFile(const string& name);

    void CleanUp();
};

#endif //UNTITLED_ASSETS_H
