	jmp Timer_end

Reset
	stz ticks
	stz seconds
	stz minutes
	ldx #30
	ldy #29
	jsr Go_XY
	ldx #<Game
	ldy #>Game
	jsr Print_Str
	jmp @end


@Timer
	lda Timer_enabled
	bne +
	jmp @end
+







@end:
	rts

Timer_end
