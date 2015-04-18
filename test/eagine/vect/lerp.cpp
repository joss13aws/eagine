/**
 *  .file test/eagine/vect/lerp.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_lerp
#include <boost/test/unit_test.hpp>

#include <eagine/vect/lerp.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_lerp)

template <typename T, unsigned N, bool V>
void test_vect_lerp_TNV(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N], b[N];

		typename eagine::vect::data<T, N, V>::type u = {}, v = {};

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(2);
			u[i] = a[i];
			b[i] = std::rand() / T(2);
			v[i] = b[i];
		}

		T t = T(0);

		eagine::vect::lerp<T, N, V> _lerp;

		while(t <= T(1))
		{
			typename eagine::vect::data<T, N, V>::type w =
				_lerp(u, v, t);

			for(unsigned i=0; i<N; ++i)
			{
				BOOST_ASSERT(test_vect_data_close(
					w[i],
					a[i]*(1-t)+b[i]*t)
				);
			}

			t += T(1)/T(1+std::rand() % 1000);
		}
	}
}

template <typename T, bool V>
void test_vect_lerp_TV(void)
{
	test_vect_lerp_TNV<T, 1, V>();
	test_vect_lerp_TNV<T, 2, V>();
	test_vect_lerp_TNV<T, 3, V>();
	test_vect_lerp_TNV<T, 4, V>();
	test_vect_lerp_TNV<T, 5, V>();
	test_vect_lerp_TNV<T, 6, V>();
	test_vect_lerp_TNV<T, 7, V>();
	test_vect_lerp_TNV<T, 8, V>();
}

template <typename T>
void test_vect_lerp_T(void)
{
	test_vect_lerp_TV<T, true>();
	test_vect_lerp_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_lerp_apply)
{
	test_vect_lerp_T<float>();
	test_vect_lerp_T<double>();
}


BOOST_AUTO_TEST_SUITE_END()
