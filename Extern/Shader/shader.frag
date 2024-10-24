#version 460

out vec4 FragColor;  

in vec3 ourColor;    // 버텍스 셰이더에서 전달된 보간된 색상
in vec2 TexCoord;    // 버텍스 셰이더에서 전달된 텍스처 좌표

uniform sampler2D ourTexture; // 텍스처 샘플러
uniform vec4 spriteColor;     // 스프라이트의 색상 (RGBA)

void main()
{
    // 텍스처에서 색상을 샘플링
    vec4 texColor = texture(ourTexture, TexCoord);
	
	
    // 텍스처 컬러와 스프라이트 컬러를 곱함
    // spriteColor는 RGB와 알파 값을 모두 포함
    // FragColor = vec4(ourColor,1);
    FragColor = texColor * spriteColor;
	if (FragColor.a < 0.3)
		discard;
}
