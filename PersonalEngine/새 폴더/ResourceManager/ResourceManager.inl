#include "ShaderResource.h"

template<typename T>
inline T* ResourceManager::GetResource(const std::string& filename)
{
    // 이미 로드된 리소스가 있는지 확인
    auto it = ResourceContainer.find(filename);
    if (it != ResourceContainer.end()) {
        // 이미 로드된 리소스가 있으면 카운터 증가 후 반환

        Resource* existingResource = it->second;
        //existingResource->SetCounter(existingResource->GetCounter() + 1);
        return static_cast<T*>(existingResource->GetData());
    }

    // 새로운 리소스 로드 및 캐싱
 
    Resource* Rsr = nullptr;
    FileExt ext = GetFileExt(filename);
    switch (ext) {
    case FileExt::png:
    case FileExt::jpg:
        Rsr = new TextResource();
        break;
    case FileExt::wav:
    case FileExt::mp3:
        Rsr = new MusicResource();
        break;
    case FileExt::vert:
    case FileExt::frag:
        if (ResourceContainer.find(filename) == ResourceContainer.end()) {
            std::string baseFilename = filename.substr(0, filename.find_last_of('.'));
            Rsr = new ShaderResource();
            Rsr->Load(baseFilename);  // baseFilename만 전달하여 vert와 frag를 모두 로드
        }
        break;
    default:
        std::cout << "FILE LOAD FAILED" << "\n";
        return nullptr;
    }

    if (Rsr) {
        // 리소스 로드 후 캐싱
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
