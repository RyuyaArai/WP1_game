#pragma once
#include <DirectXMath.h>
#include <wrl.h>

class Noise {

private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	float Wavelet(float t, float a);
	float PerlinNoise(float t, float a);
	float TwoDimensionalWavelet(float x, float y, float ax, float ay);
	float ThreeDimensionalWavelet(float x, float y, float z, float ax, float ay, float az);

	float Fade(float t);

	float Lerp(float a, float b, float t);

	float SampleGrad(unsigned int hash, float a, float b);

	float SecondPNoise(float x, float z);

	float SampleOctavePerlinNoise(float x, float y);

private:
	static const int SampleHashCodeMax;
	static const int SampleHashCodeTavleNum;

};

