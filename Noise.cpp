#include "Noise.h"
#include <stdlib.h>
#include <time.h>

#define HASH_CODE_MAX       (256)
#define HASH_CODE_TABLE_NUM     (HASH_CODE_MAX*2)
#define COUNTOF(a) ( sizeof( a ) / sizeof( a[0] ) )

int g_HashCode[HASH_CODE_TABLE_NUM] = {};

float Noise::Wavelet(float t, float a) {
	float C = 1 - (3 * powf(t, 2)) + (2 * (powf(fabsf(t), 3)));
	float L = a * t;
	float W = C * L;
	return W;
}

float Noise::PerlinNoise(float t, float a) {
    srand((unsigned)time(NULL));

	float Rand = (rand() % 2001 - 1000);
    Rand = Rand / 1000;
	float noise = Wavelet(t, a) + t * ((Rand + Wavelet(t, a)) - Wavelet(t, a));
	return noise;
}

float Noise::TwoDimensionalWavelet(float x, float y, float ax, float ay) {

	float Cx = 1 - (3 * powf(x, 2)) + (2 * (powf(fabsf(x), 3)));
	float Cy = 1 - (3 * powf(y, 2)) + (2 * (powf(fabsf(y), 3)));
	float L = ax * x + ay * y;
	float W = Cx * Cy * L;

	return W;
}

float Noise::ThreeDimensionalWavelet(float x, float y, float z, float ax, float ay, float az)
{
	float Cx = 1 - (3 * powf(x, 2)) + (2 * (powf(fabsf(x), 3)));
	float Cy = 1 - (3 * powf(y, 2)) + (2 * (powf(fabsf(y), 3)));
	float Cz = 1 - (3 * powf(z, 2)) + (2 * (powf(fabsf(z), 3)));
	float L = ax * x + ay * y + az * z;
	float W = Cx * Cy * Cz * L;

	return W;
}

void SettingHash(unsigned int seed)
{
    //乱数ライブラリ初期化.
    srand(seed);

    //ハッシュコード初期化.
    memset(g_HashCode, 0, sizeof(unsigned int) * COUNTOF(g_HashCode));

    //ランダムテーブル生成.
    const int TABLE_NUM = HASH_CODE_MAX;
    unsigned int randomTable[TABLE_NUM] = {};
    for (int i = 0; i < COUNTOF(randomTable); ++i) {
        randomTable[i] = rand() % HASH_CODE_MAX;
    }

    //ハッシュコード生成.
    for (int i = 0; i < COUNTOF(g_HashCode); ++i) {
        g_HashCode[i] = randomTable[i % TABLE_NUM];
    }
}

float Noise::Fade(float t) {
    //Ken Perlin氏(パーリンノイズを作った人)が考えだした補間関数.
    //6x^5 - 15x^4 + 10x^3.
    return (6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3));
}

float Noise::Lerp(float a, float b, float t) {
    return (a + (b - a) * t);
}

unsigned int GetHash(int x, int y) {
    x %= HASH_CODE_MAX;
    y %= HASH_CODE_MAX;
    return g_HashCode[x + g_HashCode[y]];
}

float Noise::SampleGrad(unsigned int hash, float a, float b) {

    unsigned int key = hash % 0x4;
    switch (key)
    {
    case 0x0:   return a;   //a * 1.0f + b * 0.0f.
    case 0x1:   return -a;  //a * -1.0f + b * 0.0f.
    case 0x2:   return -b;  //a * 0.0f + b * -1.0f.
    case 0x3:   return b;   //a * 0.0f + b * 1.0f.
    };
    return 0.0f;
}

float Noise::SecondPNoise(float x, float z) {

    //整数部と小数部に分ける.
    int xi = (int)floorf(x);
    int zi = (int)floorf(z);
    float xf = x - xi;
    float zf = z - zi;

    //格子点からハッシュを取り出し，その値を基に勾配を取得する.
    float a00 = SampleGrad(GetHash(xi, zi), xf, zf);
    float a10 = SampleGrad(GetHash(xi + 1, zi), xf - 1.0f, zf);
    float a01 = SampleGrad(GetHash(xi, zi + 1), xf, zf - 1.0f);
    float a11 = SampleGrad(GetHash(xi + 1, zi + 1), xf - 1.0f, zf - 1.0f);

    //補間をかける.
    xf = Fade(xf);
    zf = Fade(zf);

    //位置に合わせて格子点のどの点から一番影響を受けるかを決める.
    //(勾配関数内で内積を取っているので，ベクトルの向きによっては負の値が出る．範囲は-1.0f~1.0f).
    //(なので，正の値にするために1.0fを足して2.0fで割っている).
    return (Lerp(Lerp(a00, a10, xf), Lerp(a01, a11, xf), zf) + 1.0f) / 2.0f;
}

float Noise::SampleOctavePerlinNoise(float x, float y) {

    float a = 1.0f;
    float f = 1.0f;
    float maxValue = 0.0f;
    float totalValue = 0.0f;
    float per = 0.5f;
    for (int i = 0; i < 5; ++i) {
        totalValue += a * SecondPNoise(x * f, y * f);
        maxValue += a;
        a *= per;
        f *= 2.0f;
    }
    return totalValue / maxValue;
}