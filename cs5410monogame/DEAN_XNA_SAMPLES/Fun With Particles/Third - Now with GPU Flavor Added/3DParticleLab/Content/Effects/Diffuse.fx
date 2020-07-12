float4x4 View;
float4x4 Projection;

//
// Instance specific transformations
matrix mRotation;
float Scale;
float3 Translation;

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
};

struct VertexShaderOutput
{
    vector Position : POSITION0;
    vector Color : COLOR0;
};

VertexShaderOutput VSMain(VertexShaderInput input)
{
    VertexShaderOutput output;
	vector worldPosition = mul(input.Position,mRotation);
	input.Normal.w = 0.0f;
	input.Normal = mul(input.Normal,mRotation);
	
    matrix mScale = {Scale,0,0,0, 
					0,Scale,0,0, 
					0,0,Scale,0, 
					0,0,0,1};
					
	worldPosition = mul(worldPosition,mScale);
	
	matrix mTranslation = {1,0,0,0, 
						   0,1,0,0, 
						   0,0,1,0, 
						   Translation.x,Translation.y,Translation.z,1};
	worldPosition = mul(worldPosition, mTranslation);	
    vector viewPosition = mul(worldPosition, View);   
    output.Position = mul(viewPosition, Projection);
    
    //
    // do the lighting calculation
    vector vLight = normalize(vLightPosition - worldPosition);
    vector vViewing = normalize(worldPosition - vEye);
    
    //
    // Diffuse component
    float IDiff = dot(vLight,input.Normal);
    IDiff = saturate(IDiff);
    output.Color = ltDiffuse*IDiff;
    
    return output;
}

vector PSMain(VertexShaderOutput input) : COLOR0
{
	return input.Color;
}

technique T0
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader = compile ps_2_0 PSMain();
    }
}
