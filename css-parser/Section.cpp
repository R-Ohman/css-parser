#include "Section.h"


Section::Section() : attributes(), selectors() {}


Section::Section(const Section& other) : attributes(other.attributes), selectors(other.selectors) {}


Section& Section::operator = (const Section& other) {
	if (this == &other) {
		return *this;
	}
	attributes = other.attributes;
	selectors = other.selectors;
	return *this;
}


Section& Section::operator = (Section&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	attributes = std::move(other.attributes);
	selectors = std::move(other.selectors);
	
	other.attributes = List<Attributes>();
	other.selectors = List<Selectors>();
	return *this;
}


void Section::PushAttribute(const String& attr)
{
	String attrName = attr.CutString(0, attr.FindChar(':', 0)).DeleteSpaces();
	if (attrName == "") {
		return;
	}
	String newAttrValue = attr.CutString(attr.FindChar(':', 0) + 1, attr.GetLength()).DeleteSpaces();
	
	for (const auto& attrBlock : attributes) {
		for (size_t attrNum = 0; attrNum < attrBlock.occupiedCells; attrNum++) {
			// If attribute already exists, change its value
			if (attrBlock.attributesList[attrNum].name == attrName)
			{
				attrBlock.attributesList[attrNum].values = newAttrValue;
				return;
			}
		}
	}
	// If block with attributes is full (or doesn't exist), create new one
	if (attributes.GetSize() == 0 ||
		attributes.Back().occupiedCells == ARRAY_SIZE
		) {
		attributes.PushBack(Attributes());
	}
	attributes.Back().push_back(Attribute(attrName, newAttrValue));
}


void Section::PushSelector(const String& sel)
{
	String selectorName = sel.DeleteSpaces();
	if (selectorName == "" || selectorExists(selectorName)) {
		return;
	}
	
	if (selectors.GetSize() == 0 || 
		selectors.Back().occupiedCells == ARRAY_SIZE) {
		selectors.PushBack(Selectors());
	}
	selectors.Back().push_back(selectorName);
}


bool Section::attributeExists(const String& attrName)
{
	for (const auto& attrBlock : attributes) {
		for (size_t attrNum = 0; attrNum < attrBlock.occupiedCells; attrNum++) {
			if (attrBlock.attributesList[attrNum].name == attrName) {
				return true;
			}
		}
	}
	return false;
}


bool Section::selectorExists(const String& selName)
{
	for (const auto& selBlock : selectors) {
		for (size_t selNum = 0; selNum < selBlock.occupiedCells; selNum++) {
			if (selBlock.selectorsList[selNum] == selName) {
				return true;
			}
		}
	}
	return false;
}