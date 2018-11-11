
/*

Codehorses has just hosted the second Codehorses Cup. 
This year, the same as the previous one, organizers are giving T-shirts for the winners.

The valid sizes of T-shirts are either "M" or from 0 to 3 "X" followed by "S" or "L". 
For example, sizes "M", "XXS", "L", "XXXL" are valid and "XM", "Z", "XXXXL" are not.

There are n winners to the cup for both the previous year and the current year. 
Ksenia has a list with the T-shirt sizes printed for the last year cup and is yet to send the new list to the printing office.

Organizers want to distribute the prizes as soon as possible, so now Ksenia is required not to write the whole list from the scratch 
but just make some changes to the list of the previous year. 
In one second she can choose arbitrary position in any word and replace its character with some uppercase Latin letter. 
Ksenia can't remove or add letters in any of the words.

What is the minimal number of seconds Ksenia is required to spend to change the last year list to the current one?

The lists are unordered. 
That means, two lists are considered equal if and only if the number of occurrences of any string is the same in both lists.

Input
The first line contains one integer n (1≤n≤100) — the number of T-shirts.
The i-th of the next n lines contains ai — the size of the i-th T-shirt of the list for the previous year.
The i-th of the next n lines contains bi — the size of the i-th T-shirt of the list for the current year.
It is guaranteed that all the sizes in the input are valid. It is also guaranteed that Ksenia can produce list b from the list a.

Output
Print the minimal number of seconds Ksenia is required to spend to change the last year list to the current one. 
If the lists are already equal, print 0.

Examples
input
3
XS
XS
M
XL
S
XS
output
2

input
2
XXXL
XXL
XXL
XXXS
output
1

input
2
M
XS
XS
M
output
0

*/

