#include "ResourceManager.h"

ResourceManager* ResourceManager::Instance_ = nullptr;

ResourceManager::~ResourceManager()
{

}

ResourceManager::FileExt ResourceManager::GetFileExt(const std::string& filename)
{
    std::string ext = filename.substr(filename.find_last_of(".") + 1);

    if (ext == "png")
        return FileExt::png;
    if (ext == "jpg")
        return FileExt::jpg;
    if (ext == "mp3")
        return FileExt::mp3;
    if (ext == "wav")
        return FileExt::wav;
    if (ext == "frag")
        return FileExt::frag;
    if (ext == "vert")
        return  FileExt::vert;
    return FileExt::unvalid;
}
void ResourceManager::UnloadResource(const std::string& filename)
{
    auto it = ResourceContainer.find(filename);
    if (it != ResourceContainer.end())
    {
        // 카운터를 감소시키고 0이 되면 리소스를 언로드
        if (it->second->GetCounter() > 0) {
            it->second->SetCounter(it->second->GetCounter() - 1);
        }

        // 카운터가 0이 된 경우에만 리소스를 언로드
        if (it->second->GetCounter() <= 0) {
            it->second->Unload();
            delete it->second;
            ResourceContainer.erase(it);
        }
    }
}

void ResourceManager::Clear()
{
    for (auto& it : ResourceContainer) {
        it.second->Unload();
        delete it.second;
        
    }
    ResourceContainer.clear();
    delete Instance_;
    Instance_ = nullptr;
}