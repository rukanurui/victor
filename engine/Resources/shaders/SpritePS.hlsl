#include "Sprite.hlsli"

Texture2D<float4> tex : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[



float4 main(VSOutput input) : SV_TARGET
{
	return tex.Sample(smp,input.uv) * color;
	//return float4 (1,1,1,1);
}

