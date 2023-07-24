#ifndef RANDOM_INL
#define RANDOM_INL

#include "Random.hpp"


template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::Random()
	: rEng(std::random_device{}())
{ }

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::Random(const typename Destribution::param_type& params) : Random()
{
	SetRange(params);
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
ReturnType Random<ReturnType, RandomEngine, Destribution, T0>::GetRandomNumber()
{
	return distribution(rEng);
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
template <class ... Args, typename>
Random<ReturnType, RandomEngine, Destribution, T0>& Random<ReturnType, RandomEngine, Destribution, T0>::SetParams(Args&&... args)
{
	typename Destribution::param_type new_range(std::forward<Args>(args)...);
	distribution.param(new_range);
	return *this;
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>& Random<ReturnType, RandomEngine, Destribution, T0>::SetParams(const typename Destribution::param_type& params)
{
	distribution.param(params);
	return *this;
}


template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::operator ReturnType()
{
	return GetRandomNumber();
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::~Random()
{ }


template <class ReturnType, class RandomEngine, class Destribution, typename T0>
ReturnType Random<ReturnType, RandomEngine, Destribution, T0>::operator()()
{
	return GetRandomNumber();
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::Random(const Random& rand) : Random()
{
	*this = rand;
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>::Random(Random&& rand) noexcept
{
	*this = rand;
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>& Random<ReturnType, RandomEngine, Destribution, T0>::operator=(const Random& rand)
{
	rEng.seed(std::random_device{}());
	distribution.param(rand.distribution.param());
	return *this;
}

template <class ReturnType, class RandomEngine, class Destribution, typename T0>
Random<ReturnType, RandomEngine, Destribution, T0>& Random<ReturnType, RandomEngine, Destribution, T0>::operator=(Random&& rand) noexcept
{
	return *this = rand;
}


namespace compileTimeRandom
{
	constexpr int CurrentTimeSeconds()
	{
		const char* time = __TIME__;
		int hours = time[0] * 10 + time[1];
		int minutes = time[3] * 10 + time[4];
		int seconds = time[6] * 10 + time[7];
		return hours * 3600 + minutes * 60 + seconds;
	}

	constexpr int cRandom(unsigned int counter)
	{
		unsigned int seed = CurrentTimeSeconds();

		for (unsigned int i = 0; i <= counter; i++)
			seed = (8253729 * seed + 2396403);

		return static_cast<int>(seed) % 32768;
	}



#define CompileTRandom() compileTimeRandom::cRandom(__COUNTER__)
}

#endif

