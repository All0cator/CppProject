#include "Hierarchable.h"

Hierarchable::Hierarchable()
{}

void Hierarchable::MemberInt(Hierarchable & h, int* i)
{
	Member m;
	
	if (i == nullptr)
	{
		m.
	}
	m.data = (void*)i;
}

void Hierarchable::MemberFloat(Hierarchable & h, float* f)
{

}

void Hierarchable::MemberChar(Hierarchable & h, char* c)
{

}

void Hierarchable::MemberDouble(Hierarchable & h, double* d)
{

}

void Hierarchable::MemberUInt(Hierarchable & h, unsigned int* ui)
{

}

void Hierarchable::MemberHierarchable(Hierarchable & h, Hierarchable & memberH)
{

}

std::vector<Member>& Hierarchable::HierarchyGetMembers(Hierarchable & h)
{
	return h.members;
}