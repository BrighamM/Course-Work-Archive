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
    //vector vLight = normalize(vLightPosition - worldPosition);
    //vector vViewing = normalize(worldPosition - vEye);
    
    //
    // Diffuse component
    //float IDiff = dot(vLight,input.Normal);
    //IDiff = saturate(IDiff);
    
    //
    // Specular component
    //vector vReflection=reflect(vLight,input.Normal);
    //vector vReflection=2.0*dot(vLight,input.Normal)*input.Normal-vLight;
    //float ISpec = pow(dot(vViewing,vReflection),25.0);
    //ISpec = saturate(ISpec);
    
    //
    // Combine the lighting components
    //output.Color=ltDiffuse*IDiff + ltDiffuse*ISpec;
    
    //
    // Pass along the texture coords & normal
    output.TexCoord = input.TexCoord;
    output.Normal = input.Normal;
    output.wPosition = worldPosition;

    return output;
}

vector PSMain(VertexShaderOutput input) : COLOR0
{
    //return tex2D(TextureSampler, input.TexCoord) * input.Color;
    
    //
    // do the lighting calculation
    vector vLight = normalize(vLightPosition - input.wPosition);
    vector vViewing = normalize(input.wPosition - vEye);
    
    //
    // Diffuse component
    float IDiff = dot(vLight,input.Normal);
    IDiff = saturate(IDiff);
    
    //
    // Specular component
    vector vReflection=reflect(vLight,input.Normal);
    float ISpec = pow(dot(vViewing,vReflection),25.0);
    ISpec = saturate(ISpec);
    
    return (ltDiffuse*IDiff + ltDiffuse*ISpec) * tex2D(TextureSampler, input.TexCoord);
}

technique T0
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader = compile ps_2_0 PSMain();
    }
}
