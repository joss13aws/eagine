/**
 *  .file devel/test11.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/ecs/eck_map_normal.hpp>
#include <eagine/ecs/storage_normal.hpp>
#include <eagine/ecs/manager.hpp>
//------------------
#include <eagine/base/guid.hpp>
#include <eagine/base/error.hpp>
//------------------

namespace EAGine {
namespace ecs {


} // namespace ecs
} // namespace EAGine

struct cmp_1
 : EAGine::ecs::component<cmp_1>
{
	int i;

	cmp_1(int x)
	 : i(x)
	{ }
};

struct cmp_2
 : EAGine::ecs::component<cmp_2>
{
	double d;

	cmp_2(double x)
	 : d(x)
	{ }
};

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::ecs;

		manager<base::guid> m;

		m.register_component_type<cmp_1>(
			base::make_shared<normal_entity_component_map<base::guid>>(),
			base::make_shared<normal_component_storage<cmp_1>>()
		);

		m.register_component_type<cmp_2>(
			base::make_shared<normal_entity_component_map<base::guid>>(),
			base::make_shared<normal_component_storage<cmp_2>>()
		);

		std::cout << sizeof(base::guid) << std::endl;

		base::guid e1, e2, e3;

		if(m.has<cmp_1>(e1)) std::cout << "has" << std::endl;
		else std::cout << "has not" << std::endl;

		m.add(e1, cmp_1(123));
		m.add(e2, cmp_1(234), cmp_2(45.67));
		m.add(e3, cmp_2(78.9));

		m.for_each<cmp_1, cmp_2>(
			[](const base::guid& e, const cmp_1* c1, const cmp_2* c2) -> void
			{
				std::cout << e << "|" << c1 << "|" << c2 << std::endl;
			}
		);

		if(m.has<cmp_1>(e1)) std::cout << "has" << std::endl;
		else std::cout << "has not" << std::endl;

		std::cout << m.ro<cmp_1>(e1)->i << std::endl;

		m.remove<cmp_1>(e1);

		std::cout << m.ro<cmp_1>(e2)->i << std::endl;
		std::cout << m.ro<cmp_2>(e2)->d << std::endl;

		std::function<void(const cmp_1&, cmp_2&)> func =
			[](const cmp_1& c1, cmp_2& c2) -> void
			{
				c2.d = c1.i * 0.1;
			};

		m.for_one(e2, func);
		std::cout << m.ro<cmp_1>(e2)->i << std::endl;

		m.for_one<cmp_1, cmp_2>(
			e3,
			[](const cmp_1& c1, const cmp_2& c2) -> void
			{
				std::cout << c1.i << " | " << c2.d << std::endl;
			}
		);

		if(m.has<cmp_1>(e1)) std::cout << "has" << std::endl;
		else std::cout << "has not" << std::endl;

		m.add(e3, cmp_1(345));
		std::cout << m.ro<cmp_1>(e3)->i << std::endl;

		m.unregister_component_type<cmp_1>();

		std::cout << m.ro<cmp_2>(e2)->d << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}