#include "Selectors.h"


Selectors::Selectors() {
	selectorsList = new String[ARRAY_SIZE];
	occupiedCells = 0;
}


Selectors::Selectors(const Selectors& other) {
	if (other.selectorsList == nullptr) {
		selectorsList = nullptr;
		occupiedCells = 0;
		return;
	}
	else {
		occupiedCells = other.occupiedCells;
		selectorsList = new String[ARRAY_SIZE];
		for (size_t i = 0; i < occupiedCells; i++) {
			selectorsList[i] = other.selectorsList[i];
		}
	}
}


Selectors::Selectors(Selectors&& other) noexcept {
	if (other.selectorsList == nullptr) {
		selectorsList = nullptr;
		occupiedCells = 0;
		return;
	}
	else {
		occupiedCells = other.occupiedCells;
		selectorsList = new String[ARRAY_SIZE];
		
		for (size_t i = 0; i < occupiedCells; i++) {
			selectorsList[i] = std::move(other.selectorsList[i]);
		}
	}
}


Selectors::~Selectors() {
	delete[] selectorsList;
}


void Selectors::push_back(const String& str) {
	if (occupiedCells < ARRAY_SIZE) {
		selectorsList[occupiedCells] = str;
		occupiedCells++;
	}
}


void Selectors::push_back(String&& str) {
	if (occupiedCells < ARRAY_SIZE) {
		selectorsList[occupiedCells] = std::move(str);
		occupiedCells++;
	}
}


Selectors& Selectors::operator = (const Selectors& other) {
	if (this == &other) {
		return *this;
	}
	if (selectorsList != nullptr) {
		delete[] selectorsList;
	}
	if (other.selectorsList == nullptr) {
		selectorsList = nullptr;
		return *this;
	}
	else {
		occupiedCells = other.occupiedCells;
		selectorsList = new String[ARRAY_SIZE];
		
		for (size_t i = 0; i < occupiedCells; i++) {
			selectorsList[i] = other.selectorsList[i];
		}
	}
	return *this;
}
