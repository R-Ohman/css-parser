#pragma once
#include "includes.h"
#include "Selectors.h"
#include "Attributes.h"

class Section
{
	bool attributeExists(const String& attrName);
	bool selectorExists(const String& selName);
	
public:
	List<Attributes> attributes;
	List<Selectors> selectors;

	Section();
	Section(const Section& other);

	Section& operator = (const Section& other);
	Section& operator = (Section&& other) noexcept;

	void PushAttribute(const String& attr);
	void PushSelector(const String& sel);
};
