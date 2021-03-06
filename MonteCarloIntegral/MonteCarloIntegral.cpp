// MonteCarloIntegral.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

using namespace std;

const int numPoints = 100000;

struct aux {
	double y(double x) {
		double aux;
		try {
			aux = log(sqrt(x));
		}
		catch (int e) {
			printf("Error");
		}

		return aux;
	}
};

bool isInsideY(double x, double y, aux function) {
	return (y <= function.y(x)) && y>0;
}

double findBound(aux function, double x1, double x2) {
	double fy[numPoints];
	int max = 0;
	double max_value = -std::numeric_limits<double>::min();

	for (int i = 0; i < numPoints; i++) {
		fy[i] = function.y((i*(x2 - x1) / numPoints) + x1);
	}

	for (int i = 0; i < numPoints; i++) {
		if (fy[i]>=max_value) {
			max = i;
			max_value = fy[i];
		}
	}

	return 1.1*max_value;
}

double monteCarloArea(aux function, double x1, double x2, double bound) {
	int pointsInside = 0;
	double x = 0, y = 0; // y in [0, bound]
						 // x in  [x1, x2]

	for (int i = 0; i < numPoints; i++) {
		y = ((double)rand() / RAND_MAX)*bound;
		x = ((double)rand() / RAND_MAX)*(x2 - x1) + x1;

		//printf("x: %f y: %f\n", x, y);

		if (isInsideY(x, y, function)) {
			pointsInside++;
		}
	}

	return ((double)pointsInside / numPoints)*bound*(x2-x1);
}


int main()
{
	aux a;

	double bound = findBound(a, 1.0, 4.0);

	printf("BOUND: %f\n", bound);

	double area = monteCarloArea(a, 1.0, 4.0, bound);

	printf("AREA: %f\n", area);

	getchar();
    return 0;
}

