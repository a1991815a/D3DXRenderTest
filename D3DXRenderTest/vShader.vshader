float4x4 tMatrix;
float4x4 mMatrix;
float4x4 vMatrix;
float4x4 pMatrix;

struct VS_INPUT{
	float3 inPosition : POSITION;
};

struct VS_OUTPUT{
	float4 outPosition : POSITION;
	float4 outColor : COLOR;
};

VS_OUTPUT vmain(VS_INPUT input){
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 coord = float4(input.inPosition, 1.0f);
	coord = mul(coord, tMatrix);
	coord = mul(coord, mMatrix);
	coord = mul(coord, vMatrix);
	coord = mul(coord, pMatrix);
	output.outPosition = coord;
	output.outColor = float4(1.0f, 0.0f, 0.0f, 1.0f);

	return output;
}