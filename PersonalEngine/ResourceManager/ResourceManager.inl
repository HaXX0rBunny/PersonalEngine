template<typename T>
inline T* ResourceManager::GetResource(const std::string& filename)
{
    // 이미 로드된 리소스가 있는지 확인
    auto it = ResourceContainer.find(filename);
    if (it != ResourceContainer.end()) {
        // 이미 로드된 리소스가 있으면 카운터 증가 후 반환
        Resource* existingResource = it->second;
        existingResource->SetCounter(existingResource->GetCounter() + 1);
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
    default:
        std::cout << "FILE LOAD FAILED" << "\n";
        return nullptr;
    }

    // 리소스가 로드되면 컨테이너에 추가하고 반환
    if (Rsr) {
        Rsr->Load(filename);
        if (Rsr->GetData() != nullptr) {
            ResourceContainer[filename] = Rsr;
            Rsr->SetCounter(1); // 새로 로드된 리소스의 카운터 초기화
            return static_cast<T*>(Rsr->GetData());
        }
        else {
            delete Rsr; // 로드 실패 시 메모리 해제
            return nullptr;
        }
    }

    return nullptr; // 로드 실패 시
}
