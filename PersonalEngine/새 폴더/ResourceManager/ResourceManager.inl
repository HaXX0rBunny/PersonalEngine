#include "ShaderResource.h"

template<typename T>
inline T* ResourceManager::GetResource(const std::string& filename)
{
    // �̹� �ε�� ���ҽ��� �ִ��� Ȯ��
    auto it = ResourceContainer.find(filename);
    if (it != ResourceContainer.end()) {
        // �̹� �ε�� ���ҽ��� ������ ī���� ���� �� ��ȯ

        Resource* existingResource = it->second;
        //existingResource->SetCounter(existingResource->GetCounter() + 1);
        return static_cast<T*>(existingResource->GetData());
    }

    // ���ο� ���ҽ� �ε� �� ĳ��
 
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
            Rsr->Load(baseFilename);  // baseFilename�� �����Ͽ� vert�� frag�� ��� �ε�
        }
        break;
    default:
        std::cout << "FILE LOAD FAILED" << "\n";
        return nullptr;
    }

    if (Rsr) {
        // ���ҽ� �ε� �� ĳ��
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
