# css-parser

A simple engine for CSS processing without using the Standard Template Library. Reads CSS sections interspersed with command sections from the standard input.

## Available commands

- `****` - Resume CSS reading.
- `?` - Print the number of CSS sections.
- `i,S,?` - Print the number of selectors for section number `i` (numbers start with 1). If there is no such block, skip.
- `i,A,?` - Print the number of attributes for section number `i`. If there is no such block or section, skip.
- `i,S,j` - Output the `j`-th selector for the `i`-th block (section and attribute numbers start with 1). If there is no section or selector, skip.
- `i,A,n` - Output the value of the attribute named `n` for the `i`-th section. If there is no such block or section, skip.
- `n,A,?` - Print the total (for all blocks) number of occurrences of the attribute named `n`. Within a single block, duplicates should be removed at the loading stage. 0 is possible.
- `z,S,?` - Print the total (for all blocks) number of occurrences of the selector `z`. 0 is possible.
- `z,E,n` - Print the value of the attribute named `n` for selector `z`. In case of multiple occurrences of selector `z`, we take the last one. If none, skip.
- `i,D,*` - Delete the entire section `i` (i.e., separators + attributes). When done correctly, write out "deleted".
- `i,D,n` - Remove the attribute named `n` from the `i`-th section. If the operation leaves the section empty, it should also be removed (along with any selectors). When done correctly, write "deleted".

