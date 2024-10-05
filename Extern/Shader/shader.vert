#version 460

layout (location = 0) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec3 aColor; // 컬러 변수는 attribute position 1을 가집니다.
out vec3 ourColor; // 컬러를 fragment shader로 출력
void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor; // vertex data로부터 가져오 컬러 입력을 ourColor에 설정
}