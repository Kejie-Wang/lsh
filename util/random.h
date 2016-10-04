#ifndef _LSH_RAMDOM_H_
#define _LSH_RAMDOM_H_

#include <cstdlib>
#include <cmath>
#include <cassert>

namespace lsh
{

/**
*  Generate a uniform random variable between min and max
*  @param min: The lower bound
*  @param max: The upper bound
*/
double genUniformRandom(double min, double max)
{
	assert(min < max);
	double f = (double)rand() / RAND_MAX;
	return min + f*(max-min);
}

/** 
*  Generate a standard gaussiam random varible
*  Use Box–Muller method X = sqrt(-2*ln(U))*cos(2*PI*V) where U, V are distributed uniformly on (0,1)
*/
double genGaussianRandom()
{
	double x1, x2;
	do
	{
		x1 = genUniformRandom(0.0, 1.0);
	}while(x1==0);	//log(0) is not allowed
	x2 = genUniformRandom(0.0, 1.0);
	const double PI = asin(1)*2;
	return sqrt(-2*log(x1))*cos(2*PI*x2);
}

/**
*  Generate a random fixed random vector
*/
std::vector<double> genGaussianRandVec(int veclen)
{
	std::vector<double> vec;
	vec.reserve(veclen);
	while(veclen--)
		vec.push_back(genGaussianRandom());

	return vec;
}


std::vector<int> genUniformRandIntVec(int min, int max, int veclen)
{
	int len = max - min;
	assert(len <= RAND_MAX);

	std::vector<int> vec;
	vec.reserve(veclen);
	for(int i=0;i<veclen;++i)
	{
		int t = rand()%len;
		vec.push_back(t + min);
	}
}

}

#endif //_LSH_RAMDOM_H_