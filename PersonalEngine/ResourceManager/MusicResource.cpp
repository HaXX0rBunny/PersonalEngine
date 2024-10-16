#include "MusicResource.h"


MusicResource::MusicResource()
{
    mAudio = '\0';
    mGroup = '\0';
}

void MusicResource::Load(const std::string& filename)
{
}

void MusicResource::Unload()
{
}

void* MusicResource::GetData() const
{
    return nullptr;
}
