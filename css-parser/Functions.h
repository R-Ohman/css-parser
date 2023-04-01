#pragma once
#include "Section.h"
#include "Selectors.h"
#include "Attributes.h"
#include "includes.h"


unsigned int StringToNumber(const String& line);

// z,E,n - print "n" attribute's value of selector "z"
void AttrValueOfSelector(String& inputLine, const List<Section>& sections);

// i,A,n - print "n" attribute's value of section #i (skip if no such attribute)
void AttrValueOfSection(const String& inputLine, const List<Section>& sections);

// i,S,? - print count of selectors in section #i (skip if 0)
void CountSelectorsOfSection(const String& inputLine, const List<Section>& sections);

// z,S,? - print count of selectors with name "z" (skip if 0)
void CountSelectorInSections(const String& inputLine, const List<Section>& sections);

// i,A,? - print count of attributes in section #i (skip if 0)
void CountAttrOfSection(const String& inputLine, const List<Section>& sections);

// n,A,? - print count of attributes with name "n" (skip if 0)
void CountAttrInSections(const String& inputLine, const List<Section>& sections);

// i,D,* - delete section #i (skip if no such section)
void DeleteSection(const String& inputLine, List<Section>& sections);

// i,D,n - delete attribute with name "n" from section #i (skip if no such attribute)
void DeleteAttrFromSection(const String& inputLine, List<Section>& sections);

// i,S,j - print selector #j of section #i (skip if no such selector)
void SelectorOfSection(const String& inputLine, const List<Section>& sections);

void printSections(const List<Section>& sections);

