#include "Matrix.h"



void MyMatTranslate(glm::mat4& translateMtx, const glm::vec3 pos)
{
    translateMtx = glm::translate(glm::mat4(1.0f), pos);
}


void MyMatRotate(glm::mat4& rotateMtx, float angle)
{
    rotateMtx = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}


void MyMatScale(glm::mat4& scaleMtx, const glm::vec3 scale)
{
    scaleMtx = glm::scale(glm::mat4(1.0f), scale);
}


void MyMatConcat(glm::mat4& Mtx, glm::mat4& Mtx2, glm::mat4& Mtx3)
{
    Mtx = Mtx2 * Mtx3;

}
