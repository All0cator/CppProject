#pragma once

#include <vector>

#include "Member.h"

class Hierarchable
{
private:

	std::vector<Member> members;

protected:
	
	Hierarchable();

	// Registers Int member to this hierarchable
	static void MemberInt(Hierarchable & h, int * i, int min, int max, std::string name = "int");

	// Registers Float member to this hierarchable
	static void MemberFloat(Hierarchable & h, float * f, float min, float max, std::string name = "float", unsigned int numDecimalPlaces = 2);

	// Registers Char member to this hierarchable
	static void MemberChar(Hierarchable & h, char * c);

	// Registers Double member to this hierarchable
	static void MemberDouble(Hierarchable & h, double * d);

	// Registers Unsigned int member to this hierarchable
	static void MemberUInt(Hierarchable & h, unsigned int * ui);

	// Registers another Hierarchable as member to this hierarchable
	static void MemberHierarchable(Hierarchable & h, Hierarchable & memberH);

	virtual void HierarchySetMembers() = 0;
	void HierarchyResetMembers() {};

public:
	static std::vector<Member>& HierarchyGetMembers(Hierarchable & h);

};