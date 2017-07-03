.name "test"
.comment "test"

sti r1, %:lab1, %1
lab1: live %42
fork: fork %:lab1
ld %42,r1
ld %42,r1
ld %42,r1
ld %42,r1
ld %424242,r1
sti r1, %:fork, %1
