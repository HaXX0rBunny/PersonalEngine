#include "Matrix.h"



void MyMatTranslate(glm::mat4& translateMtx, const glm::vec3 pos)
{
    //glm::mat4 result(1.0f);
    //result[3] = glm::vec4(translation, 1.0f); // 마지막 열에 위치값 추가
    //return result;
    translateMtx = glm::translate(glm::mat4(1.0f), pos);
}


void MyMatRotate(glm::mat4& rotateMtx, float angle)
{/*
    float cosTheta = cos(angleInRadians);
    float sinTheta = sin(angleInRadians);
    glm::vec3 normalizedAxis = glm::normalize(axis);

    float x = normalizedAxis.x;
    float y = normalizedAxis.y;
    float z = normalizedAxis.z;

    result[0][0] = cosTheta + x * x * (1 - cosTheta);
    result[0][1] = x * y * (1 - cosTheta) - z * sinTheta;
    result[0][2] = x * z * (1 - cosTheta) + y * sinTheta;

    result[1][0] = y * x * (1 - cosTheta) + z * sinTheta;
    result[1][1] = cosTheta + y * y * (1 - cosTheta);
    result[1][2] = y * z * (1 - cosTheta) - x * sinTheta;

    result[2][0] = z * x * (1 - cosTheta) - y * sinTheta;
    result[2][1] = z * y * (1 - cosTheta) + x * sinTheta;
    result[2][2] = cosTheta + z * z * (1 - cosTheta);*/
    rotateMtx = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}


void MyMatScale(glm::mat4& scaleMtx, const glm::vec3 scale)
{/*
    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;*/
    scaleMtx = glm::scale(glm::mat4(1.0f), scale);
}


void MyMatConcat(glm::mat4& Mtx, glm::mat4& Mtx2, glm::mat4& Mtx3)
{
    Mtx = Mtx2 * Mtx3;

}

//glm::mat4 MyOrtho(float left, float right, float bottom, float top, float near, float far) {
//    glm::mat4 result(1.0f);  // 단위 행렬로 시작
//
//    result[0][0] = 2.0f / (right - left);
//    result[1][1] = 2.0f / (top - bottom);
//    result[2][2] = -2.0f / (far - near);
//
//    result[3][0] = -(right + left) / (right - left);
//    result[3][1] = -(top + bottom) / (top - bottom);
//    result[3][2] = -(far + near) / (far - near);
//
//    return result;
//}