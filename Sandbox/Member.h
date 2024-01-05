#pragma once

#include <string>

static enum Type
{
	TYPE_CHAR = 0,
	TYPE_INTEGER = 1,
	TYPE_UINT = 2,
	TYPE_FLOAT = 3,
	TYPE_DOUBLE = 4,
	TYPE_HIERARCHABLE = 5,
	TYPE_NULL = 6
};
class Member
{
public:
	bool isReadOnly;
	Type type;
	void* data;
	std::string name;
};

class MemberNumerical : public Member
{
public:
	void* min;
	void* max;
	std::string format;
};

class MemberAlphabetical : public Member
{
public:
	unsigned int width;
};

class MemberArray1D : public Member
{
public:
	unsigned int width;
};

class MemberArray2D : public Member
{
public:
	unsigned int width;
	unsigned int height;
};