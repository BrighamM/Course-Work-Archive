#define MAX_SHADER_MATRICES 25
//
// Array of instance transforms used by the ShaderInstancing technique.
matrix InstanceTransforms[MAX_SHADER_MATRICES];
matrix InstanceRotations[MAX_SHADER_MATRICES];

float4x4 View;
float4x4 Projection;

//
// Lighting parameters (actually, not parameters, hard-coded)
vector vEye = {0.0f, 0.0f, 5000.0f, 0.0f};
vector vLightPosition = {0.0f, 0.0f, 3000.0f, 0.0f};
vector ltDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};

//
// Texture sampler for the particle
texture Texture;
sampler TextureSampler = sampler_state
{
	texture = <Texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	
	AddressU = Clamp;
    AddressV = Clamp;
};

struct VertexShaderInput
{
    vector Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
    vector Normal : NORMAL;
};

struct VertexShaderOutput
{
    vector Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
    vector wPosition : COLOR0;
    vector Normal : COLOR1;
    
};

VertexShaderOutput VSMain(VertexShaderInput input,float instanceIndex : TEXCOORD1)
{
    VertexShaderOutput output;
	vector worldPosition = mul(input.Position,InstanceTransforms[instanceIndex]);
	input.Normal.w = 0.0f;
	input.Normal = mul(input.Normal,InstanceRotations[instanceIndex]);
	
    vector viewPosition = mul(worldPosition, View);   
    output.Position = mul(viewPosition, Projection);
    
    //
    // Pass along the texture coords & normal
    output.TexCoord = input.TexCoord;
    output.Normal = input.Normal;
    output.wPosition = worldPosition;

    return output;
}

vector PSMain(VertexShaderOutput input) : COLOR0
{
    //
    // do the lighting calculation
    vector vLight = normalize(vLightPosition - input.wPosition);
    vector vViewing = normalize(input.wPosition - vEye);
    
    //
    // Diffuse component
    float IDiff = dot(vLight,input.Normal);
    IDiff = saturate(IDiff);
    
    return ltDiffuse*IDiff * tex2D(TextureSampler, input.TexCoord);
}

technique T0
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader = compile ps_2_0 PSMain();
    }
}
