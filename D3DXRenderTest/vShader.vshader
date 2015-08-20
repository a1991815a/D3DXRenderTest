float4x4 tMatrix;
float4x4 mMatrix;
float4x4 vMatrix;
float4x4 pMatrix;

//bool isSpirte;

struct VS_INPUT{
	float3 inPosition : POSITION;
	float4 inColor : COLOR;
	float3 inNormal : NORMAL;
	float inPSize : PSIZE;
	float2 inTexcoord : TEXCOORD0;
};

struct VS_OUTPUT{
	float4 outPosition : POSITION;
	float4 outColor : COLOR;
	float outPSize : PSIZE;
	float2 outTexcoord : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input){
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 coord = float4(input.inPosition, 1.0f);

	coord = mul(coord, tMatrix);
	coord = mul(coord, mMatrix);
	coord = mul(coord, vMatrix);
	coord = mul(coord, pMatrix);
	output.outPosition = coord;
	output.outColor = input.inColor;
	output.outPSize = input.inPSize;
	output.outTexcoord = float2(input.inTexcoord.x, 1.0f-input.inTexcoord.y);
	return output;
}