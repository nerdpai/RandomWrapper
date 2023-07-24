#ifndef RANDOM_HPP
#define RANDOM_HPP

#if __cplusplus < 201103L
#error "No support for pre C++11"
#endif

#include <random>
#include <type_traits>



template<
	class ReturnType = int,
	class RandomEngine = std::mt19937,
	class Destribution = std::uniform_int_distribution<int>,
	typename = std::enable_if_t<
					std::is_same_v<ReturnType, typename Destribution::result_type>
				>
>
class Random
{
	Destribution distribution;
	RandomEngine rEng;

public:

	Random();

	Random(const typename Destribution::param_type& params);

	ReturnType GetRandomNumber();

	template <
		class... Args,
		typename = std::enable_if_t<
						std::is_constructible_v<
										typename Destribution::param_type,
										Args&&...
									>
						>
	>
	Random& SetParams(Args&&... args);

	Random& SetParams(const typename Destribution::param_type& params);

	operator ReturnType();

	ReturnType operator()();

	virtual ~Random();

	Random(const Random& rand);

	Random(Random&& rand) noexcept;

	Random& operator =(const Random& rand);

	Random& operator =(Random&& rand) noexcept;
};

#include"Random.tcc"
#endif

