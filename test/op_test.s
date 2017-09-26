.name "test"
.comment "test"

sti r1, %:live, %1
live: live %1
fork %42        # 0c | 00 2a

sti r1, %:live, %1
live: live %1
lfork %42        # 0c | 00 2a

add r1, r2, r3  # 04 | 54 | 01 | 02 | 03

sub r1, r2, r3  # 04 | 54 | 01 | 02 | 03

ld %97, r1
ld 97, r1       # 02 | d0 | 00 2a | 01

lld %97, r1
lld 97, r1       # 02 | d0 | 00 2a | 01

live %42        # 01 | 00 00 00 2a

st r1, r2       # 03 | 50 | 01 | 02
st r1, 100      # 03 | 70 | 01 | 00 64

and r1, r2, r3  # 06 | 54 | 01 | 02 | 03
and 42, r2, r3  # 06 | d4 | 00 2a | 02 | 03
and %42, r2, r3 # 06 | 94 | 00 00 00 2a | 02 | 03

or r1, r2, r3  # 06 | 54 | 01 | 02 | 03
or 42, r2, r3  # 06 | d4 | 00 2a | 02 | 03
or %42, r2, r3 # 06 | 94 | 00 00 00 2a | 02 | 03

xor r1, r2, r3  # 06 | 54 | 01 | 02 | 03
xor 42, r2, r3  # 06 | d4 | 00 2a | 02 | 03
xor %42, r2, r3 # 06 | 94 | 00 00 00 2a | 02 | 03

sti r1, r2, r3  # 0b | 54 | 01 | 02 | 03
sti r1, %42, r3 # 0b | 64 | 01 | 00 2a | 03

ldi r1, r2, r3  # 0a | 54 | 01 | 02 | 03
ldi %42, r2, r3 # 0a | 94 | 00 2a | 02 | 03
ldi 42, r2, r3  # 0a | d4 | 00 2a | 02 | 03
ldi 42, %42, r3 # 0a | e4 | 00 2a | 00 2a | 03

lldi r1, r2, r3  # 0a | 54 | 01 | 02 | 03
lldi %42, r2, r3 # 0a | 94 | 00 2a | 02 | 03
lldi 42, r2, r3  # 0a | d4 | 00 2a | 02 | 03
lldi 42, %42, r3 # 0a | e4 | 00 2a | 00 2a | 03

zjmp %42        # 09 | 00 2a #!!direct in 2 bytes because index
