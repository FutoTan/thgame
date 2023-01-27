#include "assets.h"

using namespace std;

Assets Assets::Instance;

Assets::Assets() = default;

bool Assets::GetAssetsList(){
    try {
        ifstream fs;
        fs.open("./game.dat", ios::in|ios::binary);
        GameDataHeader game_data_header{};
        fs.seekg( 4);
        fs.read((char *)&game_data_header,sizeof(game_data_header));

        DataTableHeader string_table = game_data_header.StringTable;
        auto* string_table_compressed = (unsigned char*)malloc(string_table.CompressedSize);
        fs.seekg(string_table.FilePointer);
        fs.read((char *)string_table_compressed,string_table.CompressedSize);
        char* string_table_origin = (char *)malloc(string_table.OriginSize);
        uncompress((Bytef*)string_table_origin,(uLongf*)&string_table.OriginSize,
                   string_table_compressed,string_table.OriginSize);
        free(string_table_compressed);

        DataTableHeader assests_table_header = game_data_header.AssestsTableHeader;
        auto* assests_table_header_compressed = (unsigned char*)malloc(assests_table_header.CompressedSize);
        fs.seekg(assests_table_header.FilePointer);
        fs.read((char *)assests_table_header_compressed,assests_table_header.CompressedSize);
        auto* assests_table_header_origin = new AssestTableHeader[game_data_header.AssetsCount];
        uncompress((Bytef*)assests_table_header_origin,(uLongf*)&assests_table_header.OriginSize,
                   assests_table_header_compressed,assests_table_header.OriginSize);
        free(assests_table_header_compressed);

        for (int i=0;i<game_data_header.AssetsCount;i++){
            string name = string_table_origin+assests_table_header_origin[i].NamePointer;
            name.append(".").append(assests_table_header_origin[i].Type);
            AssetsList.insert(AssetsTable::value_type{name,AssetTableInfo(
                    {assests_table_header_origin[i].FilePointer,
                     assests_table_header_origin[i].OriginSize,
                     assests_table_header_origin[i].CompressedSize})});
            }
        free(string_table_origin);
        fs.close();
        return true;
    }catch (const char* e){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"GetAssetsList error: %s",e);
        return false;
    }
}

SDL_RWops* Assets::GetAsset(const string& name){
    SDL_RWops* rwops;
    if (!AssetsList[name].Loaded){
        LoadAssetFromFile(name);
    }
    if (!AssetsList.contains(name)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Get asset %s error: no such file.",name.c_str());
    }
    rwops = SDL_RWFromMem(
            AssetsList[name].MemoryPointer, (int)
                    AssetsList[name].OriginSize);
    return rwops;
}

bool Assets::LoadAssetFromFile(const std::string &name) {
    try{
        ifstream fs;
        fs.open("./game.dat", ios::in|ios::binary);
        Uint32 _pointer = AssetsList[name].FilePointer;
        Uint32 _origin_size = AssetsList[name].OriginSize;
        Uint32 _compressed_size = AssetsList[name].CompressedSize;
        auto* assest_compressed = (unsigned char*)malloc(_compressed_size);
        fs.seekg(_pointer);
        fs.read((char *)assest_compressed,_compressed_size);
        auto* assest_origin = (char *)malloc(_origin_size);
        uncompress((Bytef*)assest_origin,(uLongf*)&_origin_size,assest_compressed,
                   _origin_size);
        free(assest_compressed);
        //free(assest_origin);
        AssetsList[name].Loaded = true;
        AssetsList[name].MemoryPointer = assest_origin;
        fs.close();
        return true;
    }catch (const char* e){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Get asset %s error: %s",name.c_str(),e);
        return false;
    }
}

void Assets::CleanUp() {
    for (const auto& asset:AssetsList){
        free(asset.second.MemoryPointer);
    }
}

Assets* Assets::GetInstance() {
    return &Assets::Instance;
}