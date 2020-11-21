// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE void reflectpp::serializer::save(const T& object) const REFLECTPP_NOEXCEPT
	{
		save(variant(object));
	}

	template<typename T>
	REFLECTPP_INLINE void reflectpp::serializer::load(T& object) const REFLECTPP_NOEXCEPT
	{
		auto var = variant(object);
		load(var);
	}
}
