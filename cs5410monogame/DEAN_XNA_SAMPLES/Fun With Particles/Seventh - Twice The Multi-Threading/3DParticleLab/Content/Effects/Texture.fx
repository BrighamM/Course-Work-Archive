
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
    vector Normal : NORMAL;
    float2 TexCoord : TEXCOORD0;
    float InstanceIndex : TEXCOORD1;
};

struct VertexShaderOutput
{
    vector Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
};

VertexShaderOutput VSMain(VertexShaderInput input)
{
    VertexShaderOutput output;

	vector worldPosition = mul(input.Position,InstanceTransforms[input.InstanceIndex]);
	input.Normal.w = 0.0f;
	input.Normal = mul(input.Normal,InstanceRotations[input.InstanceIndex]);
	
    vector viewPosition = mul(worldPosition, View);   
    output.Position = mul(viewPosition, Projection);

	//
	// Just pass along the texture coordinates
    output.TexCoord = input.TexCoord;
    
    return output;
}

vector PSMain(VertexShaderOutput input) : COLOR0
{
	return tex2D(TextureSampler,input.TexCoord);
}

technique T0
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader = compile ps_2_0 PSMain();
    }
}
