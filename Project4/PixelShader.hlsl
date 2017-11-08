#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

texture2D tex : register(t0);
SamplerState texSample : register(s0);

struct _Material
{
    float4 emissive;
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float specularPower;
    bool useTexture;
    float2 padding;
};
 
cbuffer MaterialProperties : register(b0)
{
    _Material material;
};

struct Light
{
    float4 pos;
    float4 dir;
    float4 color;
    float spotAngle;
    float3 attenuation; //x = constAtt, y = linAtt, z = quadAtt
    int lightType;
    bool enabled;
    int2 padding;
};
 
cbuffer LightProperties : register(b1)
{
    float4 eyePos;
    float4 globalAmbient;
    Light lights[3];
};

struct LightResult
{
    float4 diffuse;
    float4 specular;
};

float4 Diffuse(Light light, float3 lightVec, float3 surfaceNorm)
{
    float ndotl = max(0, dot(surfaceNorm, lightVec));

    return light.color * ndotl;
}

float4 Specular(Light light, float3 viewVec, float3 lightVec, float3 surfaceNorm)
{
    float3 phong = normalize(reflect(-lightVec, surfaceNorm));
    float rdotv = max(0, dot(phong, viewVec));

    return light.color * pow(rdotv, material.specularPower);
}

float Attenuation(Light light, float d)
{
    return 1.0f / (light.attenuation.x + light.attenuation.y * d + light.attenuation.z * d * d);
}

LightResult PointLight(Light light, float3 viewVec, float4 pointShade, float3 surfaceNorm)
{
    LightResult result;
 
    float3 lightVec = (light.pos - pointShade).xyz;
    float distance = length(lightVec);
    lightVec = lightVec / distance;
 
    float attenuation = Attenuation(light, distance);
 
    result.diffuse = Diffuse(light, lightVec, surfaceNorm) * attenuation;
    result.specular = Specular(light, viewVec, lightVec, surfaceNorm) * attenuation;
 
    return result;
}

LightResult DirectionalLight(Light light, float3 viewVec, float4 pointShade, float3 surfaceNorm)
{
    LightResult result;
 
    float3 lightVec = -light.dir.xyz;
 
    result.diffuse = Diffuse(light, lightVec, surfaceNorm);
    result.specular = Specular(light, viewVec, lightVec, surfaceNorm);
 
    return result;
}

float SpotCone(Light light, float3 lightVec)
{
    float minCos = cos(light.spotAngle);
    float maxCos = (minCos + 1.0f) / 2.0f;
    float cosAngle = dot(light.dir.xyz, -lightVec);
    return smoothstep(minCos, maxCos, cosAngle);
}

LightResult SpotLight(Light light, float3 viewVec, float4 pointShade, float3 surfaceNorm)
{
    LightResult result;
 
    float3 lightVec = (light.pos - pointShade).xyz;
    float distance = length(lightVec);
    lightVec = lightVec / distance;
 
    float attenuation = Attenuation(light, distance);
    float spotIntensity = SpotCone(light, lightVec);
 
    result.diffuse = Diffuse(light, lightVec, surfaceNorm) * attenuation * spotIntensity;
    result.specular = Specular(light, viewVec, lightVec, surfaceNorm) * attenuation * spotIntensity;
 
    return result;
}

LightResult ComputeLighting(float4 pointShade, float3 surfaceNorm)
{
    float3 viewVec = normalize(eyePos - pointShade).xyz;
 
    LightResult totalResult = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
 
    [unroll]
    for (int i = 0; i < 3; ++i)
    {
        LightResult result = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
 
        if (!lights[i].enabled)
            continue;
         
        switch (lights[i].lightType)
        {
            case DIRECTIONAL_LIGHT:
            {
                    result = DirectionalLight(lights[i], viewVec, pointShade, surfaceNorm);
            }
            break;

            case POINT_LIGHT:
            {
                    result = PointLight(lights[i], viewVec, pointShade, surfaceNorm);
            }
            break;

            case SPOT_LIGHT:
            {
                    result = SpotLight(lights[i], viewVec, pointShade, surfaceNorm);
            }
            break;
        }

        totalResult.diffuse += result.diffuse;
        totalResult.specular += result.specular;
    }
 
    totalResult.diffuse = saturate(totalResult.diffuse);
    totalResult.specular = saturate(totalResult.specular);
 
    return totalResult;
}

struct INPUT_PIXEL
{
	float4 posWS : POSITIONWS;
    float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normals : NORMALS;
	float2 uv : UV;
};


float4 main(INPUT_PIXEL input) : SV_TARGET
{
    LightResult light = ComputeLighting(input.posWS, normalize(input.normals));
     
    float4 emissive = material.emissive;
    float4 ambient = material.ambient * globalAmbient;
    float4 diffuse = material.diffuse * light.diffuse;
    float4 specular = material.specular * light.specular;
 
    float4 texColor = { 1, 1, 1, 1 };
     
    if (material.useTexture)
    {
        texColor = tex.Sample(texSample, input.uv);
        if (texColor.a < 0.5f)
            discard;
    }
 
    float4 finalColor = (emissive + ambient + diffuse + specular) * texColor;

    return finalColor;
}


//float4 main(INPUT_PIXEL input) : SV_TARGET
//{
//    float4 texColor = tex.Sample(texSample, input.uv);

//    if (texColor.a < 0.5f)
//        discard;

//    return texColor;
//}