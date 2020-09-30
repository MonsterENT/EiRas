#ifndef COMMON_HLSL
#define COMMON_HLSL

inline float SmithJointGGXVisibilityTerm (float NdotL, float NdotV, float roughness)
{
    float a = roughness;
    float lambdaV = NdotL * (NdotV * (1 - a) + a);
    float lambdaL = NdotV * (NdotL * (1 - a) + a);

    return 0.5f / (lambdaV + lambdaL + 1e-5f);
}

inline float GGXTerm (float NdotH, float roughness)
{
    float a2 = roughness * roughness;
    float d = (NdotH * a2 - NdotH) * NdotH + 1.0f; 
    return 1.0f / 3.14159f * a2 / (d * d + 1e-7f);
}

#endif