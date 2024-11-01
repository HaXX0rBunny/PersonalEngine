#version 460

layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aLine;  
out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;
uniform float fwidth_Line;

void main()
{ 
    // 회전 행렬 추출 (3x3 부분만)
    mat3 rotMat = mat3(transform);
    
    // 기본 위치 변환
    vec4 transformedPos = transform * vec4(aPos, 1.0);
    
    // offset 계산 (회전 방향 고려)
    float offset = fwidth_Line * 0.01;
    if(aLine > 0.0)
    {
        vec2 offsetDir;
        if(aLine == 1.0) offsetDir = normalize(rotMat * vec3(-1.0, -1.0, 0.0)).xy;
        else if(aLine == 2.0) offsetDir = normalize(rotMat * vec3(-1.0, 1.0, 0.0)).xy;
        else if(aLine == 3.0) offsetDir = normalize(rotMat * vec3(1.0, 1.0, 0.0)).xy;
        else if(aLine == 4.0) offsetDir = normalize(rotMat * vec3(1.0, -1.0, 0.0)).xy;
        
        transformedPos.xy += offsetDir * offset;
    }
    
    gl_Position = projection * view * transformedPos;
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}