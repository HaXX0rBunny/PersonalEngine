#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void MyMatTranslate(glm::mat4& translateMtx, glm::vec3 pos);
void MyMatRotate(glm::mat4& rotateMtx, float angle);
void MyMatScale(glm::mat4& scaleMtx, glm::vec3 scale);

void MyMatConcat(glm::mat4& Mtx, glm::mat4& Mtx2, glm::mat4& Mtx3);