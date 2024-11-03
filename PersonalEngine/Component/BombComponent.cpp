#include "BombComponent.h"
#include "../GameObject/GameObject.h"
#include "../CManager/ComponentManager.h"
int BombComp::BombCount = 0;
BombComp::BombComp(GameObject* owner) : LogicComponent(owner) {
    startTime = glfwGetTime();
    LifeTime = 3.0f;
    isExploded = false;
    BombPower = 1;
    Bombtype = Default;
    BombCount++;
}

BombComp::~BombComp() {
    BombCount--;
}

void BombComp::Update() {
    if (!isExploded) {
        LifeTime -= Time::delta_time;
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
        glm::vec2(1.0f, 0.0f),   // ������
        glm::vec2(-1.0f, 0.0f),  // ����
        glm::vec2(0.0f, 1.0f),   // ��
        glm::vec2(0.0f, -1.0f)   // �Ʒ�
    };

    // �߽��� ���� ����Ʈ ����
    CreateExplosionEffect(own->GetComponent<TransformComp>()->GetPos());

    // �� ���������� ����
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
    // ���� ����Ʈ�� ���� ������Ʈ ����

    GameObject* effect = new GameObject("ExplosionEffect_" + std::to_string(BombCount));

    // Transform ������Ʈ ����
    auto transform = effect->AddComponent<TransformComp>();
    transform->SetPos({ position ,5});
    transform->SetScale( 32.0f, 32.0f); // ���� ����Ʈ ũ�� ����

    // ��������Ʈ ������Ʈ �߰�
    auto sprite = effect->AddComponent<SpriteComp>();
    sprite->SetTexture(); // ���� ��������Ʈ ����

    //// �ִϸ��̼� ������Ʈ �߰� (�ִٸ�)
    //auto anim = effect->AddComponent<AnimationComponent>();
    //anim->AddClip("explosion", 0.5f); // 0.5�� ���� ����Ǵ� ���� �ִϸ��̼�
    //anim->Play("explosion");

    // ���� �ð� �� ����Ʈ ����
    float effectDuration = 0.5f; // ����Ʈ ���� �ð�
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

        // AABB �浹 �˻�
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

bool BombComp::HandleCollisions(const std::vector<GameObject*>& colliders) {
    bool hitWall = false;

    for (auto* obj : colliders) {
        auto tag = obj->ObjectTag;

        if (tag == GameObject::Tag::Wall) {
            GameObjectManager::Instance()->RemoveObj(obj->GetName());
            hitWall = true;
        }
        else if (tag == GameObject::Tag::Bomb) {
            // ���� ����
            auto bombComp = obj->GetComponent<BombComp>();
            if (bombComp && !bombComp->isExploded) {
                bombComp->Explode();
            }
        }
        else if (tag == GameObject::Tag::Player || tag == GameObject::Tag::Enemy) {
            std::cout << "Player Dead" << std::endl;
            //GameObjectManager::Instance()->RemoveObj(obj->GetName());
        }
    }

    return hitWall;
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
