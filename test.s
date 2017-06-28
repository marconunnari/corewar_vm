.name "test"
.comment "test"

l1: ld %42, r2
ld :l1, r2
st r2, 100
