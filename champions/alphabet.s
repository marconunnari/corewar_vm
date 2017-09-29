.name "alphabet"
.comment "affiche alphabet"

#store the player number as argument of live function
sti r1, %:live, %1

#letter = 97 (code for letter 'a')
ld %97, r2
ld %1, r3
startwhile:
	
	#print letter
	aff r2
	
	#call live
	live: live %42
	
	#if letter == 120 break
	xor r2, %122, r4
	zjmp %:endwhile
	
	#increase letter
	add r2, r3, r2
	
	#next iteration
	xor %0, %0, r4
	fork %:startwhile
	zjmp %:startwhile

endwhile:
