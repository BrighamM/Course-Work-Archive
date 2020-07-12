
sampler TextureSampler;

struct PS_INPUT
{
	float2 TexCoord : TEXCOORD0;
};


//
// Computes the sepia tone for the image
vector PS_SepiaTone(PS_INPUT input) : COLOR0
{
	vector inColor = tex2D(TextureSampler,input.TexCoord);
	vector outColor=0;
	
	outColor.r=(inColor.r*0.393 + inColor.g*0.769 + inColor.b*0.189);
	outColor.g=(inColor.r*0.349 + inColor.g*0.686 + inColor.b*0.168);
	outColor.b=(inColor.r*0.272 + inColor.g*0.534 + inColor.b*0.131);
	
	return outColor;
}

technique Technique1
{
    pass Pass1
    {
        PixelShader = compile ps_2_0 PS_SepiaTone();
    }
}
