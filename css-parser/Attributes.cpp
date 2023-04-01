#include "Attributes.h"


Attribute::Attribute() : name(), values() {}


Attribute::Attribute(const String& name, const String& values) : name(name), values(values) {}


Attribute::Attribute(String&& name, String&& values) {
	this->name = std::move(name);
	this->values = std::move(values);
}

Attribute::Attribute(const Attribute& other) : name(other.name), values(other.values) {}


Attribute::Attribute(Attribute&& other) noexcept {
	this->name = std::move(other.name);
	this->values = std::move(other.values);
}


Attribute& Attribute::operator = (const Attribute& other) {
	if (this == &other) return *this;
	name = other.name;
	values = other.values;
	return *this;
}


Attribute& Attribute::operator = (Attribute&& other) noexcept {
	if (this == &other) return *this;
	name = std::move(other.name);
	values = std::move(other.values);
	return *this;
}

Attributes::Attributes() {
	attributesList = new Attribute[ARRAY_SIZE];
	occupiedCells = 0;
}


Attributes::Attributes(const Attributes& other) {
	attributesList = new Attribute[ARRAY_SIZE];
	occupiedCells = other.occupiedCells;

	for (size_t i = 0; i < other.occupiedCells; i++) {
		attributesList[i] = other.attributesList[i];
	}
}


Attributes::~Attributes() {
	delete[] attributesList;
}


void Attributes::push_back(const Attribute& attr) {
	if (occupiedCells < ARRAY_SIZE) {
		attributesList[occupiedCells] = attr;
		occupiedCells++;
	}
}

void Attributes::push_back(Attribute&& attr) {
	if (occupiedCells < ARRAY_SIZE) {
		attributesList[occupiedCells] = std::move(attr);
		occupiedCells++;
	}
}


Attributes& Attributes::operator = (const Attributes& other) {
	if (this == &other) {
		return *this;
	}

	delete[] attributesList;
	attributesList = new Attribute[ARRAY_SIZE];
	occupiedCells = other.occupiedCells;

	for (size_t i = 0; i < other.occupiedCells; i++) {
		attributesList[i] = other.attributesList[i];
	}

	return *this;
}
