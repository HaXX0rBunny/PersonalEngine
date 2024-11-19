#include "BombComponent.h"
#include "../GameObject/GameObject.h"
#include "../CManager/ComponentManager.h"
int BombComp::EffectCount = 0;
BombComp::BombComp(GameObject* owner) : LogicComponent(owner) {
    own->ObjectTag = GameObject::Tag::Bomb;
    startTime = glfwGetTime();
    LifeTime = 3.0f;
    isExploded = false;
    BombPower = 0;
    Bombtype = Default;

}

BombComp::~BombComp() {

}

void BombComp::Update() {
    if (!isExploded) {
        LifeTime -= float(Time::delta_time);
        if (LifeTime <= 0) {
            Explode();
        }
    }
}
void BombComp::Explode() {
    if (isExploded) return;
    isExploded = true;

    ProcessExplosion();
    GameObjectManager::Instance()->RemoveObj(own->GetName());
}

bool BombComp::IsPlayerWhitelisted(const std::string& playerName) const
{
    return std::find(WhiteList.begin(), WhiteList.end(), playerName) != WhiteList.end();
}

void BombComp::oustWhiteList(const std::string& cr_instr)
{
    auto it = std::find(WhiteList.begin(), WhiteList.end(), cr_instr);
    if (it != WhiteList.end())
        WhiteList.erase(it);
}

void BombComp::SetWhiteList()
{
  
    auto objects = GameObjectManager::Instance()->AllObj();
    TransformComp* bombTransform = own->GetComponent<TransformComp>();


    for (const auto& obj : objects) {
        if (obj.second->ObjectTag == GameObject::Tag::Player) {
            TransformComp* playerTransform = obj.second->GetComponent<TransformComp>();
            glm::vec3 playerPos = playerTransform->GetPos();
            glm::vec3 bombPos = bombTransform->GetPos();
            // 폭탄과 플레이어 사이의 거리 계산
            float distance = glm::distance(
                glm::vec2(bombPos.x, bombPos.y),
                glm::vec2(playerPos.x, playerPos.y)
            );

            // 일정 거리 내에 있는 플레이어를 WhiteList에 추가
            if (distance < 40.0f) {  // 적절한 거리값으로 조정
                WhiteList.push_back(obj.second->GetName());
            }

        }
    }

}

const std::list<std::string>& BombComp::GetWhiteList()
{
    return WhiteList;
}
void BombComp::LoadFromJson(const json& data)
{
}


json BombComp::SaveToJson()
{
    return json();
}

BaseRTTI* BombComp::CreateBombComp()
{
    return nullptr;
}

void BombComp::ProcessExplosion() {
    const glm::vec2 directions[] = {
        glm::vec2(1.0f, 0.0f),   // 오른쪽
        glm::vec2(-1.0f, 0.0f),  // 왼쪽
        glm::vec2(0.0f, 1.0f),   // 위
        glm::vec2(0.0f, -1.0f)   // 아래
    };

    // 중심점 폭발 이펙트 생성
    CreateExplosionEffect(own->GetComponent<TransformComp>()->GetPos());

    // 각 방향으로의 폭발
    for (const auto& dir : directions) {
        for (int i = 1; i <= BombPower; i++) {
            glm::vec2 explosionPos = CalculateExplosionPosition(dir, i);
            CreateExplosionEffect(explosionPos);

            auto colliders = CheckCollisionAtPosition(explosionPos);
            if (HandleCollisions(colliders)) break;
        }
    }
}
void BombComp::CreateExplosionEffect(const glm::vec2& position) {
    // 폭발 이펙트용 게임 오브젝트 생성
    EffectCount++;
    GameObject* effect = new GameObject("ExplosionEffect_" + std::to_string(EffectCount));
    //std::cout << BombCount << std::endl;
    // Transform 컴포넌트 설정
    auto transform = effect->AddComponent<TransformComp>();
    transform->SetPos({ position ,-5});
    transform->SetScale( 40.0f, 40.0f); // 폭발 이펙트 크기 설정

    // 스프라이트 컴포넌트 추가
    auto sprite = effect->AddComponent<SpriteComp>();
    sprite->SetTexture(); // 폭발 스프라이트 설정

    //// 애니메이션 컴포넌트 추가 (있다면)
    //auto anim = effect->AddComponent<AnimationComponent>();
    //anim->AddClip("explosion", 0.5f); // 0.5초 동안 재생되는 폭발 애니메이션
    //anim->Play("explosion");

    // 일정 시간 후 이펙트 제거
    float effectDuration = 0.5f; // 이펙트 지속 시간
    auto explosionComp = effect->AddComponent<ExplosionEffectComponent>();
    explosionComp->SetDuration(0.5f);
}

glm::vec2 BombComp::CalculateExplosionPosition(const glm::vec2& direction, int distance) {
    glm::vec2 currentPos = own->GetComponent<TransformComp>()->GetPos();
    return currentPos + direction * (float)(distance * 32);
}

std::vector<GameObject*> BombComp::CheckCollisionAtPosition(const glm::vec2& pos) {
    std::vector<GameObject*> colliders;
    auto objects = GameObjectManager::Instance()->AllObj();

    for (auto& obj : objects) {
        if (obj.second->GetName() == own->GetName()) continue;

        auto collComp = obj.second->GetComponent<CollisionComp>();
        if (!collComp) continue;

        // AABB 충돌 검사
        glm::vec2 explosionMin = pos - glm::vec2(16.0f);
        glm::vec2 explosionMax = pos + glm::vec2(16.0f);

        glm::vec2 objPos = obj.second->GetComponent<TransformComp>()->GetPos();
        glm::vec2 objSize = obj.second->GetComponent<TransformComp>()->GetScale();
        glm::vec2 objMin = objPos - (objSize * 0.5f);
        glm::vec2 objMax = objPos + (objSize * 0.5f);

        if (explosionMin.x <= objMax.x && explosionMax.x >= objMin.x &&
            explosionMin.y <= objMax.y && explosionMax.y >= objMin.y) {
            colliders.push_back(obj.second);
        }
    }

    return colliders;
}

void BombComp::SetPower(const int& ci_in)
{
    BombPower = ci_in;
}

void BombComp::reduceEffect()
{
    EffectCount--;
}

bool BombComp::HandleCollisions(const std::vector<GameObject*>& colliders) {
    bool hitWall = false;
    //BombFlameEffect collision evenet
    for (auto* obj : colliders) {
        auto tag = obj->ObjectTag;

        if (tag == GameObject::Tag::Block) {
            GameObjectManager::Instance()->GetObj(obj->GetName())->GetComponent<BlockComp>()->DestoryBlock();
            hitWall = true;
        }
        else if (tag == GameObject::Tag::Wall)
        {
            hitWall = true;
        }
        else if (tag == GameObject::Tag::Bomb) {
            // 연쇄 폭발
            auto bombComp = obj->GetComponent<BombComp>();
            if (bombComp && !bombComp->isExploded) {
                bombComp->Explode();
            }
        }
        else if (tag == GameObject::Tag::Player || tag == GameObject::Tag::Enemy) {
            std::cout << "Player Dead" << std::endl;
            //GameObjectManager::Instance()->RemoveObj(obj->GetName());
        }
        //else if (tag == GameObject::Tag::Item) {
        //    GameObjectManager::Instance()->RemoveObj(obj->GetName());
        //}
        else
            return false;
    }

    return hitWall;
}

ExplosionEffectComponent::ExplosionEffectComponent(GameObject* owner) : LogicComponent(owner), duration(0.5f), currentTime(0.0f) {

}

ExplosionEffectComponent::~ExplosionEffectComponent()
{
    //own->GetComponent<BombComp>()->reduceEffect();
}

void ExplosionEffectComponent::LoadFromJson(const json& data)
{
}

json ExplosionEffectComponent::SaveToJson()
{
    return json();
}

BaseRTTI* ExplosionEffectComponent::CreateBombComp()
{
    return nullptr;
}
