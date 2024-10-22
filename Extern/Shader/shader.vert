#version 460

layout (location = 0) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec3 aColor; // 컬러 변수는 attribute position 1을 가집니다.
layout (location = 2) in vec2 aTexCoord; //Texture value have attribute Position 2 

out vec3 ourColor; // 컬러를 fragment shader로 출력
out vec2 TexCoord; // texture Shader output

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main()
{
    //gl_Position = projection*transform*vec4(aPos, 1.0);
    gl_Position = projection*view*transform*vec4(aPos, 1.0);
    ourColor = aColor; // vertex data로부터 가져오 컬러 입력을 ourColor에 설정
    TexCoord = vec2(aTexCoord.x, aTexCoord.y); // 
}