#version 460

out vec4 FragColor;  
in vec3 ourColor;    // 버텍스 셰이더에서 전달된 보간된 색상
in vec2 TexCoord;    // 버텍스 셰이더에서 전달된 텍스처 좌표

uniform sampler2D ourTexture; // 텍스처 샘플러
uniform vec4 spriteColor;     // 스프라이트의 색상 (RGBA)
uniform bool useTexture;      // 텍스처 사용 여부를 결정하는 uniform 변수 추가

void main()
{
    if(useTexture)
    {
        // 스프라이트 렌더링
        vec4 texColor = texture(ourTexture, TexCoord);
        FragColor = texColor * spriteColor;
        if(FragColor.a < 0.3)
            discard;
    }
    else
    {
        // 콜리전 박스 렌더링
        FragColor = vec4(ourColor, 1.0);
    }
}