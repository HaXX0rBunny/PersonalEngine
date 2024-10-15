#include "ShaderResource.h"

template<typename T>
inline T* ResourceManager::GetResource(const std::string& filename)
{

    auto it = ResourceContainer.find(filename);
    if (it != ResourceContainer.end()) {


        Resource* existingResource = it->second;
        //existingResource->SetCounter(existingResource->GetCounter() + 1);
        return static_cast<T*>(existingResource->GetData());
    }

 
    Resource* Rsr = nullptr;
    FileExt ext = GetFileExt(filename);
    switch (ext) {
    case FileExt::png:
    case FileExt::jpg:
        Rsr = new TextResource();
        std::cout << "ResourceManager.inl 24: Created TextResource at " << Rsr << std::endl;
        break;
    case FileExt::wav:
    case FileExt::mp3:
        std::cout << "ResourceManager.inl 24: Created MusicResource at " << Rsr << std::endl;
        Rsr = new MusicResource();
        break;
    case FileExt::vert:
    case FileExt::frag:
        if (ResourceContainer.find(filename) == ResourceContainer.end()) {
            std::string baseFilename = filename.substr(0, filename.find_last_of('.'));
            Rsr = new ShaderResource();

            std::cout << "ResourceManager.inl 24: Created ShaderResource at " << Rsr << std::endl;
            Rsr->Load(baseFilename);  
        }
        break;
    default:
        std::cout << "FILE LOAD FAILED" << "\n";
        return nullptr;
    }

    if (Rsr) {

        Rsr->Load(filename);
        if (Rsr->GetData() != nullptr) {
            ResourceContainer[filename] = Rsr;
            Rsr->SetCounter(1);
            return static_cast<T*>(Rsr->GetData());
        }
        else {
            delete Rsr;
            return nullptr;
        }
    }

    return nullptr;
}
