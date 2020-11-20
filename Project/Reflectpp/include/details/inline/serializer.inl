// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	inline void reflectpp::serializer::save(const T& object) noexcept
	{
		save(variant(object));
	}

	template<typename T>
	inline void reflectpp::serializer::load(T& object) const noexcept
	{
		auto var = variant(object);
		load(var);
	}
}
