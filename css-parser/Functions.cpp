#include "Functions.h"


unsigned int StringToNumber(const String& line) {
	int number = 0;
	for (size_t i = 0; i < line.GetLength(); i++) {
		number = number * 10 + (line[i] - '0');
	}
	return number;
}


void AttrValueOfSelector(String& inputLine, const List<Section>& sections) {
	// selector,E,attrName
	String selector = inputLine.CutString(0, inputLine.FindChar(',', 0));
	String attrName = inputLine.CutString(inputLine.FindChar(',', 0) + 3, inputLine.GetLength());
	
	if (selector == "" || attrName == "") {
		return;
	}
	
	String attrValue = "";
	
	for (const auto& section : sections) {
		// If section has global attributes
		if (section.selectors.GetSize() == 1 && section.selectors[0].occupiedCells == 0) {
			for (const auto& attrBlock : section.attributes) {
				for (size_t attrNum = 0; attrNum < attrBlock.occupiedCells; attrNum++) {
					if (attrBlock.attributesList[attrNum].name == attrName)
					{
						attrValue = attrBlock.attributesList[attrNum].values;
					}
				}
			}
		}
		
		// Look for selector, if found, look for attribute
		for (size_t selBlockNum = section.selectors.GetSize(); selBlockNum-- > 0;) {
			for (size_t selNum = 0; selNum < section.selectors[selBlockNum].occupiedCells; selNum++) {
				if (section.selectors[selBlockNum].selectorsList[selNum] == selector) {
					for (const auto& attrBlock : section.attributes) {
						for (size_t attrNum = 0; attrNum < attrBlock.occupiedCells; attrNum++) {
							if (attrBlock.attributesList[attrNum].name == attrName)
							{
								attrValue = attrBlock.attributesList[attrNum].values;
							}
						}
					}
				}
			}
		}
	}
	if (attrValue != "") {
		std::cout << inputLine << " == " << attrValue << std::endl;
	}
}


void AttrValueOfSection(const String& inputLine, const List<Section>& sections) {
	// sectionNumber,A,attr
	String attr = inputLine.CutString(inputLine.FindChar(',', 0) + 3, inputLine.GetLength());
	if (attr == "") {
		return;
	}
	
	unsigned int sectionNumber = StringToNumber(inputLine.CutString(0, inputLine.FindChar(',', 0))) - 1;
	String value = "";
	// Look for attribute with name "attr" and print its value
	for (const auto& attrBlock : sections[sectionNumber].attributes) {
		for (size_t attrNum = attrBlock.occupiedCells; attrNum-- > 0;) {
			if (attrBlock.attributesList[attrNum].name == attr)
			{
				value = attrBlock.attributesList[attrNum].values;
			}
		}
	}
	if (value != "") {
		std::cout << inputLine << " == " << value << std::endl;
	}
}


void CountSelectorsOfSection(const String& inputLine, const List<Section>& sections) {
	// sectionNumber,S,?
	unsigned int sectionNumber = StringToNumber(inputLine.CutString(0, inputLine.FindChar(',', 0))) - 1;
	if (sectionNumber < sections.GetSize()) {
		int counter = 0;
		
		for (const auto& selBlock : sections[sectionNumber].selectors)
		{
			counter += selBlock.occupiedCells;
		}
		
		std::cout << inputLine << " == " << counter << std::endl;
	}
}


void CountSelectorInSections(const String& inputLine, const List<Section>& sections) {
	// selectorToCount,S,?
	String selectorToCount = inputLine.CutString(0, inputLine.FindChar(',', 0));
	if (selectorToCount == "") {
		return;
	}
	int counter = 0;
	
	for (const auto& section : sections) {
		for (const auto& selBlock : section.selectors) {
			for (size_t selNum = 0; selNum < selBlock.occupiedCells; selNum++) {
				if (selBlock.selectorsList[selNum] == selectorToCount) {
					counter++;
				}
			}
		}
	}
	std::cout << inputLine << " == " << counter << std::endl;
}


void CountAttrOfSection(const String& inputLine, const List<Section>& sections) {
	// sectionNumber,A,?
	unsigned int sectionNumber = StringToNumber(inputLine.CutString(0, inputLine.FindChar(',', 0))) - 1;
	
	if (sectionNumber < sections.GetSize()) {
		int counter = 0;
		for (const auto& attrBlock : sections[sectionNumber].attributes) {
			counter += attrBlock.occupiedCells;
		}
		std::cout << inputLine << " == " << counter << std::endl;
	}
}


void CountAttrInSections(const String& inputLine, const List<Section>& sections) {
	// attr,A,?
	String attr = inputLine.CutString(0, inputLine.FindChar(',', 0));
	if (attr == "") {
		return;
	}
	int counter = 0;
	
	for (const auto& section : sections) {
		for (const auto& attrBlock : section.attributes) {
			for (size_t attrNum = 0; attrNum < attrBlock.occupiedCells; attrNum++) {
				if (attrBlock.attributesList[attrNum].name == attr) {
					counter++;
				}
			}
		}
	}
	std::cout << inputLine << " == " << counter << std::endl;
}


void DeleteSection(const String& inputLine, List<Section>& sections) {
	// sectionNumber,D,*
	String number = inputLine.CutString(0, inputLine.FindChar(',', 0));
	if (number == "") {
		return;
	}
	
	unsigned int sectionNumber = StringToNumber(number) - 1;
	if (sectionNumber < sections.GetSize()) {
		std::cout << inputLine << " == deleted" << std::endl;
		sections.Remove(sectionNumber);
	}
}


void DeleteAttrFromSection(const String& inputLine, List<Section>& sections) {
	// sectionNumber,D,attrName
	String number = inputLine.CutString(0, inputLine.FindChar(',', 0));
	String attrName = inputLine.CutString(inputLine.FindChar(',', 0) + 3, inputLine.GetLength());
	if (number == "" || attrName == "") {
		return;
	}
	
	unsigned int sectionNumber = StringToNumber(number) - 1;
	if (sectionNumber > sections.GetSize() - 1) {
		return;
	}
	
	for (size_t attrBlockNum = 0; attrBlockNum < sections[sectionNumber].attributes.GetSize(); attrBlockNum++) {
		for (size_t attrNum = 0; attrNum < sections[sectionNumber].attributes[attrBlockNum].occupiedCells; attrNum++) {
			if (sections[sectionNumber].attributes[attrBlockNum].attributesList[attrNum].name == attrName) {
				// If there is only one attribute in the block
				if (sections[sectionNumber].attributes[attrBlockNum].occupiedCells <= 1) {
					// If there is only one block of attributes, delete the whole section, else delete the block
					if (sections[sectionNumber].attributes.GetSize() == 1) {
						sections.Remove(sectionNumber);
					}
					else {
						sections[sectionNumber].attributes.Remove(attrBlockNum);
					}
				}
				else {
					// If the attribute is not the last one in the block, move the last attribute to the place of the deleted one
					if (attrNum < sections[sectionNumber].attributes[attrBlockNum].occupiedCells - 1) {
						sections[sectionNumber].attributes[attrBlockNum].attributesList[attrNum].name =
										sections[sectionNumber].attributes[attrBlockNum].attributesList[sections[sectionNumber]
																			.attributes[attrBlockNum].occupiedCells - 1].name;
						sections[sectionNumber].attributes[attrBlockNum].attributesList[attrNum].values =
										sections[sectionNumber].attributes[attrBlockNum].attributesList[sections[sectionNumber]
																			.attributes[attrBlockNum].occupiedCells - 1].values;
					}
					else {
						// If the attribute is the last one in the block, just delete it
						sections[sectionNumber].attributes[attrBlockNum].attributesList[attrNum].name = "";
						sections[sectionNumber].attributes[attrBlockNum].attributesList[attrNum].values = "";
					}
					(sections[sectionNumber].attributes[attrBlockNum].occupiedCells)--;
				}
				std::cout << inputLine << " == deleted" << std::endl;
				return;
			}
		}
	}
}


void SelectorOfSection(const String& inputLine, const List<Section>& sections) {
	// numberSection,S,numberSelector
	String numberSection = inputLine.CutString(0, inputLine.FindChar(',', 0));
	String numberSelector = inputLine.CutString(inputLine.FindChar(',', 0) + 3, inputLine.GetLength());
	if (numberSection == "" || numberSelector == "") {
		return;
	}
	
	unsigned int sectionInd = StringToNumber(numberSection) - 1;
	unsigned int selectorInd = StringToNumber(numberSelector) - 1;
	
	if (sectionInd < sections.GetSize()) {
		unsigned int countSelectors = 0;
		for (const auto& selBlock : sections[sectionInd].selectors) {
			for (size_t selNum = 0; selNum < selBlock.occupiedCells; selNum++) {
				if (countSelectors == selectorInd) {
					std::cout << inputLine << " == " << selBlock.selectorsList[selNum] << std::endl;
					return;
				}
				countSelectors++;
			}
		}
	}
}


void printSections(const List<Section>& sections) {
	int i = 0;
	for (const auto& section : sections) {
		std::cout << "\nSection #" << ++i << std::endl;
		std::cout << "Selectors: " << std::endl;
		for (const auto& selBlock : section.selectors) {
			for (size_t k = 0; k < selBlock.occupiedCells; k++) {
				std::cout << "\t(" << selBlock.selectorsList[k] << ")\n";
			}
		}
		std::cout << "\nAttributes: " << std::endl;
		for (const auto& attrBlock : section.attributes) {
			for (size_t k = 0; k < attrBlock.occupiedCells; k++) {
				std::cout << "\t(" << attrBlock.attributesList[k].name << ") : (" << attrBlock.attributesList[k].values << ")\n";
			}
		}
		std::cout << std::endl;
	}
}
