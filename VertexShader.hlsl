struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;

};

struct VS_OUTPUT
{
    float4 position : POSITION;
    float3 color : COLOR;

};

VS_OUTPUT main( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.position = input.position;
    output.color = input.color;


	return output;
}