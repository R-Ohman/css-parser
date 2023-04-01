#include <iostream>
#include "includes.h"
#include "Section.h"
#include "Functions.h"

void ReadCSS(List<Section>& sections);


void ReadCommands(List<Section>& sections, bool& read) {
	String inputLine;
	while (true) {

		// Read the line while it is empty or it contains non correct number of commas
		do {
			std::cin >> inputLine;
			
			// Check if it is the end of the file
			if (inputLine.GetLength() == 1 && inputLine[0] == 1) {
				read = false;
				return;
			}
		} while (inputLine.GetLength() < 1 || (inputLine.CountChar(',') != 2 && inputLine.CountChar(',') != 0));
		
		
		if (inputLine == "****") {
			ReadCSS(sections);
			return;
		}
		else if (inputLine == "?") {
			// Print the number of CSS sections
			std::cout << "? == " << sections.GetSize() << std::endl;
		}
		else if (inputLine.containString(",E,") > 0) {
			// z,E,n
			AttrValueOfSelector(inputLine, sections);
		}
		else if (inputLine.containString(",D,") > 0) {
			if (inputLine.FindChar('*', 4) < inputLine.GetLength()) {
				// i,D,*
				DeleteSection(inputLine, sections);
			}
			else {
				//i,D,n
				DeleteAttrFromSection(inputLine, sections);
			}
		}
		else if (inputLine.containString(",S,") > 0) {
			if (inputLine.containString(",S,?") > 0) {
				if (inputLine[0] >= '0' && inputLine[0] <= '9') {
					// i,S,?
					CountSelectorsOfSection(inputLine, sections);
				}
				else {
					// z,S,?
					CountSelectorInSections(inputLine, sections);
				}
			}
			else {
				// i,S,j
				SelectorOfSection(inputLine, sections);
			}
		}
		else if (inputLine.containString(",A,") > 0) {
			if (inputLine.containString(",A,?") > 0) {
				if (inputLine[0] >= '0' && inputLine[0] <= '9') {
					// i,A,?
					CountAttrOfSection(inputLine, sections);
				}
				else {
					// n,A,?
					CountAttrInSections(inputLine, sections);
				}
			}
			else if (inputLine[0] >= '0' && inputLine[0] <= '9') {
				// i,A,n
				AttrValueOfSection(inputLine, sections);
			}
		}
	}
}


void GetAttributes(String& inputLine, List<Section>& sections, Section& currentSection) {
	int countAttr;
	String* attrArray;
	// If inputLine contains '{', cut it
	if (inputLine.FindChar('{', 0) < inputLine.GetLength()) {
		inputLine = inputLine.CutString(inputLine.FindChar('{', 0) + 1, inputLine.GetLength());
	}
	// If inputLine contains '}', all attributes are in it
	if (inputLine.FindChar('}', 0) < inputLine.GetLength()) {
		countAttr = inputLine.CountChar(':');
		attrArray = inputLine.CutString(0, inputLine.FindChar('}', 0)).SplitByChar(';');
	}
	else {
		// Read attributes wtile '}' is not found in inputLine
		while (inputLine.FindChar('}', 0) == inputLine.GetLength()) {
			int countAttr = inputLine.CountChar(':');
			String* attrArray = inputLine.SplitByChar(';');

			for (int i = 0; i < countAttr; i++) {
				currentSection.PushAttribute(attrArray[i]);
			}
			delete[] attrArray;
			std::cin >> inputLine;
		}
		// inputLine contains '}', so we need to cut it
		countAttr = inputLine.CountChar(':');
		attrArray = inputLine.CutString(0, inputLine.FindChar('}', 0)).SplitByChar(';');
	}
	
	for (int i = 0; i < countAttr; i++) {
		currentSection.PushAttribute(attrArray[i]);
	}
	delete[] attrArray;
	
	// Section is ready
	sections.PushBack(currentSection);
}


void GetSelectors(List<Section>& sections, String& inputLine, bool& read) {
	Section currentSection;
	
	// Skip empty lines
	while (inputLine.GetLength() == 0) {
		std::cin >> inputLine;
	}

	// If the line is a command, then read the command
	if (inputLine == "????") {
		ReadCommands(sections, read);
		return;
	}
	
	// Read selectors while "{" is not found in the line
	while (inputLine.FindChar('{', 0) == inputLine.GetLength()) {
		int countSelectors = inputLine.CountWords();
		String* selectorsArray = inputLine.SplitByChar(',');
		
		for (int i = 0; i < countSelectors; i++) {
			currentSection.PushSelector(selectorsArray[i]);
		}
		delete[] selectorsArray;
		std::cin >> inputLine;
	}
	
	// The last line with selectors (contain "{")
	int countSelectors = inputLine.CutString(0, inputLine.FindChar('{', 0)).CountWords();
	String* selectorsArray = inputLine.CutString(0, inputLine.FindChar('{', 0)).SplitByChar(',');

	for (int i = 0; i < countSelectors; i++) {
		currentSection.PushSelector(selectorsArray[i]);
	}
	delete[] selectorsArray;
	
	GetAttributes(inputLine, sections, currentSection);
	return;
}


void ReadCSS(List<Section>& sections) {
	String inputLine;
	bool read = true;
	// One iteration for one section
	do {
		std::cin >> inputLine;
		// Check if it's the end of file
		if (inputLine.GetLength() > 0 && inputLine[0] == 1) {
			return;
		}
		GetSelectors(sections, inputLine, read);
		//printSections(sections);
	} while (read);
}


int main()
{
	List<Section> sections;
	ReadCSS(sections);
	return 0;
}
