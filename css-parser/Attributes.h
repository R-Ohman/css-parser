#pragma once
#include "includes.h"

class Attribute {
public:
	String name;
	String values;

	Attribute();

	Attribute(const String& name, const String& values);
	Attribute(String&& name, String&& values);

	Attribute(const Attribute& other);
	Attribute(Attribute&& other) noexcept;

	Attribute& operator = (const Attribute& other);
	Attribute& operator = (Attribute&& other) noexcept;
};


class Attributes {
public:
	Attribute* attributesList;
	unsigned int occupiedCells;

	Attributes();
	Attributes(const Attributes& other);
	~Attributes();

	void push_back(const Attribute& attr);
	void push_back(Attribute&& attr);

	Attributes& operator = (const Attributes& other);
};