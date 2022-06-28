#include "generaAleatorio.h"
#include <math.h>

GeneracionAleatorio::GeneracionAleatorio(int nObs, int ba1, int ba2, int alt, int anch):
	nObstaculos(nObs),
	base1(ba1),
	base2(ba2),
	alto(alt),
	ancho(anch)
{
	matriz = std::vector<int>(anch * alt, 0);
}

std::vector<int> GeneracionAleatorio::generaObstaculo()
{
	for (int i = 0; i < nObstaculos; i++)
	{
		std::pair<float, float> result = halton2d(base1, base2, i + 2);
		int x = (int)floor(result.first * ancho);
		int y = (int)floor(result.first * alto);
		matriz[y * ancho + x] = 1;
	}

	return matriz;
}



float GeneracionAleatorio::halton1d(int base, int index)
{
	float result = 0;
	int denominator = 1;
	while (index > 0)
	{
		denominator = denominator * base;
		result = result + (index % base) / denominator;
		index = (int)floor(index / base);
	}
	return result;
}

std::pair<float, float> GeneracionAleatorio::halton2d(int base1, int base2, int index)
{
	float x = halton1d(base1, index);
	float y = halton1d(base2, index);
	return std::pair<int, int>(x,y);
}
