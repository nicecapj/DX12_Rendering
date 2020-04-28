#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity()
{

}

void Entity::AddType(const type_info& InType)
{
	auto it = std::find(Types.cbegin(), Types.cend(), InType);

	if (it == Types.cend())
	{
		TypeId <<= 2;
		TypeId |= InType.hash_code() >> 62;

		Types.emplace_back(InType);
	}
}

size_t Entity::GetId()
{
	return TypeId & Index;
}

bool Entity::IsEqualTypeId(size_t InTypeId)
{
	return TypeId != 0 && TypeId == InTypeId;
}