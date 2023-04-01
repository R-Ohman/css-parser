#pragma once
#include "includes.h"

class Selectors {
public:
	String* selectorsList;
	unsigned int occupiedCells;

	Selectors();
	Selectors(const Selectors& other);
	Selectors(Selectors&& other) noexcept;
	~Selectors();

	void push_back(const String& str);
	void push_back(String&& str);

	Selectors& operator = (const Selectors& other);
};