/**
 *  @file eagine/vect/array_raf.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_ARRAY_REF_1308281038_HPP
#define EAGINE_VECT_ARRAY_REF_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename D, typename T, unsigned N>
struct _ary_ref_hlp;

template <typename T, unsigned N>
struct _ary_ref_hlp<_ary_data<T, N>, T, N>
{
	const T* _v;

	inline
	_ary_ref_hlp(const _ary_data<T, N>& d)
	noexcept
	 : _v(d._v)
	{ }
};

template <typename D, typename T, unsigned N>
struct _ary_ref_hlp
{
	T _v[N];

	inline
	_ary_ref_hlp(const D& d)
	noexcept
	{
		for(unsigned i=0; i<N; ++i)
		{
			_v[i] = d[i];
		}
	}
};

// array_ref
template <typename T, unsigned N>
struct array_ref
 : _ary_ref_hlp<typename data<T, N>::type, T, N>
{
	using _ary_ref_hlp<typename data<T, N>::type, T, N>::_ary_ref_hlp;

	inline
	const T* data(void) const
	noexcept
	{
		return this->_v;
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard
