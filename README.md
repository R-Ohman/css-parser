# css-parser

A simple engine for CSS processing.
Reads CSS sections interspersed with command sections from the standard input. 

Available commands:
**** - resume CSS reading;
? - print the number of CSS sections;
i,S,? - print the number of selectors for section number i (numbers start with 1), if there is no such block skip;
i,A,? - print the number of attributes for section no. i, if there is no such block or section skip;
i,S,j - output the j-th selector for the i-th block (section and attribute numbers start with 1) if there is no section or selector skip;
i,A,n - output for the i-th section the value of the attribute named n, if there is no such skip;
n,A,? - print the total (for all blocks) number of occurrences of the attribute named n. (Within a single block, duplicates should be removed at the loading stage). 0 is possible;
z,S,? - print the total (for all blocks) number of occurrences of the selector z. 0 is possible;
z,E,n - print the value of the attribute named n for selector z, in case of multiple occurrences of selector z we take the last one. If none, skip;
i,D,* - delete the entire section i (i.e. separators+attributes), when done correctly write out deleted;
i,D,n - remove the attribute named n from the i-th section, if the operation leaves the section empty it should also be removed (along with any selectors), when done correctly write deleted.
