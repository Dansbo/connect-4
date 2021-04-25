	jmp Timer_end

!macro PRINT_DECIMAL .num {
	lda .num
	lsr
	lsr
	lsr
	lsr
	ora #$30
	jsr CHROUT
	lda .num
	and #$0F
	ora #$30
	jsr CHROUT
}

Reset
	stz ticks
	stz seconds
	stz minutes
	ldx #30
	ldy #29
	jsr Go_XY
	ldx #<Game
	ldy #>Game
	jsr Print_Str		;Print game time label
	lda Timer_enabled
	bne @Timer
	jmp @end


@Timer
	sed			;Enter decimal mode
	lda ticks
	clc
	adc #1
	cmp #$60
	bne @next_tick
	stz ticks
	bra @update_seconds

@next_tick
	sta ticks
	jmp @end

@update_seconds
	lda seconds
	clc
	adc #1
	cmp #$60
	bne @next_second
	stz seconds
	bra @update_minute

@next_second
	sta seconds
	bra @print

@update_minute
	lda minutes
	clc
	adc #1
	cmp #$90
	bne @next_minute
	stz minutes
	bra @print

@next_minute
	sta minutes

@print
	cld			;Exit decimal mode
	ldx #35
	ldy #49
	+PRINT_DECIMAL minutes
	ldx #<Colon
	ldy #>Colon
	jsr Print_Str
	+PRINT_DECIMAL seconds

@end:
	rts

Timer_end
