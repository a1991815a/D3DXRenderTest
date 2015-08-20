sampler BaiscSampler;
bool isSprite;

struct PS_INPUT{
	float4 inColor : COLOR;
	float2 inTexcoord : TEXCOORD0;
};

struct PS_OUTPUT{
	float4 outColor : COLOR;
};

PS_OUTPUT main(PS_INPUT input){
	PS_OUTPUT output = (PS_OUTPUT)0;
	if(!isSprite)
	{
		output.outColor = input.inColor;
	}else{
		output.outColor = tex2D(BaiscSampler, input.inTexcoord);
	}

	return output;
}