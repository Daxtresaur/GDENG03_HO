struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};


cbuffer constant : register(b0)
{
    float m_angle;
};


VS_OUTPUT vsmain( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.position = input.position;
	//output.position = lerp(input.position, input.position1, (sin(m_angle) + 1.0f) / 2.0f);
    output.color = input.color;
	//output.color1 = input.color1;

    return output;
}