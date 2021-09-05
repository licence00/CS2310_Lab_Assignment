load RCA16b.hdl;
output-file RCA16b.out,
//compare-to RCA16b.cmp,
output-list x%B1.16.1 y%B1.16.1 z%B1.16.1 AorS%B2.1.2 OF%B2.1.2;


set x 1212,
set y 6742,//%B0100110000100001
set AorS 0,
eval,
output;

set x 2555,
set y 89,
set AorS 1,
eval,
output;

set x 32767,
set y 1,
set AorS 1,
eval,
output;

set x 32767,
set y 2,
set AorS 1,
eval,
output;


set x %B1010110010101100,
set y %B1000110100110101,
set AorS 0,
eval,
output;

set x %B0111111111111111,
set y %B0111111111111011,
set AorS 0,
eval,
output;

set x -32767,
set y 2,
set AorS 0,
eval,
output;

set x 32767,
set y 2,
set AorS 0,
eval,
output;
