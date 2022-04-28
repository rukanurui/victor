#include "Sprite.hlsli"

Texture2D<float4> tex : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[

float WhiteNoise(float2 coord) {
	return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.645);
}




float4 main(VSOutput input) : SV_TARGET
{

	//
	float2 samplePoint = input.uv;
	float4 Tex = tex.Sample(smp, samplePoint);
	samplePoint.x += 0.01;
	Tex.r = tex.Sample(smp, samplePoint).r;
	
	
	//float vignette = length(float2(0.5, 0.5) - input.uv);
	//vignette = clamp(vignette - 0.2, 0, 1);
//	Tex.rgb -= vignette;


	//������
	float sinv = sin(input.uv.y * 2 + Bar * -0.1);
	float steped = step(0.99, sinv * sinv);	

	Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 50.0 + Bar * 1.0)) * 0.05;
	Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 100.0 + Bar * 2.0)) * 0.08;
	Tex.rgb += steped * 0.1;
	



	//�m�C�Y
	float noise = WhiteNoise(input.uv * Time) - 0.5;
	Tex.rgb += float3(noise, noise, noise);




	//samplePoint -= float2(0.5, 0.5);
	//float distPower = pow(length(samplePoint), Distortion);
	//samplePoint *= float2(distPower, distPower);
	//samplePoint += float2(0.5, 0.5);
	//float4 Tex = tex.Sample(smp, samplePoint);

	return Tex;

		//�����܂�
	//return tex.Sample(smp,input.uv) * color;
	//return float4 (1,1,1,1);
}

