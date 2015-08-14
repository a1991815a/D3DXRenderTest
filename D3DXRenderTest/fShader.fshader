struct PS_INPUT{
	float4 inColor : COLOR;
};

struct PS_OUTPUT{
	float4 outColor : COLOR;
};

PS_OUTPUT fmain(PS_INPUT input){
	PS_OUTPUT output = (PS_OUTPUT)0;
	output.outColor = input.inColor;

	return output;
}