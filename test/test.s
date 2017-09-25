.name "test"
.comment "test"

sti r1, %:live, %1
live: live %1
ld %98, r2
st r2, r4
st r2, 42
aff r4

#live %42        # 01 | 00 00 00 2a

#ld 42, r1       # 02 | d0 | 00 2a | 01
#ld %42, r1      # 02 | 90 | 00 00 00 2a | 01

#st r1, r2       # 03 | 50 | 01 | 02
#st r1, 100      # 03 | 70 | 01 | 00 64

#add r1, r2, r3  # 04 | 54 | 01 | 02 | 03

#and r1, r2, r3  # 06 | 54 | 01 | 02 | 03
#and 42, r2, r3  # 06 | d4 | 00 2a | 02 | 03
#and %42, r2, r3 # 06 | 94 | 00 00 00 2a | 02 | 03

#zjmp %42        # 09 | 00 2a #!!direct in 2 bytes because index

#ldi r1, r2, r3  # 0a | 54 | 01 | 02 | 03
#ldi %42, r2, r3 # 0a | 94 | 00 2a | 02 | 03
#ldi 42, r2, r3  # 0a | d4 | 00 2a | 02 | 03
#ldi 42, %42, r3 # 0a | e4 | 00 2a | 00 2a | 03

#sti r1, r2, r3  # 0b | 54 | 01 | 02 | 03
#sti r1, %42, r3 # 0b | 64 | 01 | 00 2a | 03

#fork %42        # 0c | 00 2a
