        jmp TextUIend

; *************************** Functions ***************************************
;******************************************************************************
;Move text cursor
;******************************************************************************
Go_XY:
	stx TMP1		;Switching X and Y around so X is
	sty TMP2		;Horizontal position and Y is
	ldx TMP2		;Vertical as we know from graphing
	ldy TMP1

	clc
	jsr PLOT
	rts

;******************************************************************************
;Print string function
;******************************************************************************
Print_Str:
	stx TMP1
	sty TMP2
	ldy #0

@Doprint
	lda (TMP1), Y
	beq @Printdone
	jsr CHROUT
	iny
	jmp @Doprint

@Printdone
	rts


TextUI:
        ldx #3
        ldy #4
        jsr Go_XY

        ldx #<@columns
        ldy #>@columns
        jsr Print_Str

        rts

@columns        !pet    "1   2   3   4   5   6   7",0



TextUIend