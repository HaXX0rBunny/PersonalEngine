#version 460

out vec4 FragColor;  

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture; //GLSL 그래픽 쉐이딩 랭귀지 

//uniform vec4 ourColor;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
/*텍스처 컬러를 샘플링하기 위해 GLSL의 texture 함수를 사용합니다. 
이 함수는 첫 번째 파라미터로 텍스처 sampler를 받고 두 번째 파라미터로 해당 텍스처 좌표를 받습니다. 
그런 다음 texture 함수는 앞서 설정했던 텍스처 파라미터를 사용하여 해당 컬러 값을 샘플링합니다. 
이 fragment shader의 출력은 (보간된) 텍스처 좌표에서 (필터링된) 텍스처의 컬러입니다.*/