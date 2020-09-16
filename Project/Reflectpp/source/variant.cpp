// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant.h"
#include "type.h"

variant::variant() :
	m_data{ nullptr },
	m_is_owner{ false },
	m_type{ nullptr }
{
}

variant::~variant()
{
	if (m_is_owner && m_data != nullptr)
	{
		m_type->get_factory().destroy(m_data);
		m_data = nullptr;
	}
}

variant::variant(const variant& copy) :
	m_data{ copy.m_type->get_factory().Copy(copy.m_data) },
	m_is_owner{ true },
	m_type{ copy.m_type }
{
}

variant& variant::operator=(const variant& copy)
{
	m_data = copy.m_type->get_factory().copy(copy.m_data);
	m_is_owner = true;
	m_type = copy.m_type;

	return *this;
}

variant::operator bool() const
{
	return is_valid();
}

void variant::clear() noexcept
{
	if (m_is_owner && is_valid())
		m_type->get_factory().destroy(m_data);

	m_data = nullptr;
	m_is_owner = false;
	m_type = nullptr;
}

type& variant::get_type() const noexcept
{
	//Reflectpp::Assert(m_Type != nullptr, "Variant::GetType() : invalid variant\n");
	return *m_type;
}

bool variant::is_valid() const noexcept
{
	return m_data != nullptr;
}

variant::variant(void* data, bool is_owner, type* type) noexcept :
	m_data{ data },
	m_is_owner{ is_owner },
	m_type{ type }
{
}