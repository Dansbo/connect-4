        jmp TextUIend

; *************************** Functions ***************************************
;******************************************************************************
;Move text cursor
;******************************************************************************
Go_XY:
	phx            		;Switching X and Y around so X is
	phy            		;Horizontal position and Y is
	plx            		;Vertical as we know from graphing
	ply

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
        ldx #31
        ldy #0
        jsr Go_XY

        ldx #<@player
        ldy #>@player
        jsr Print_Str

        ldx #31
        ldy #2
        jsr Go_XY

        ldx #<@choose
        ldy #>@choose
        jsr Print_Str

        ldx #31
        ldy #3
        jsr Go_XY

        ldx #<@column
        ldy #>@column
        jsr Print_Str

        ldx #38
        ldy #0
        jsr Go_XY

        lda Player
        bne @2

        lda #$1C                ;Change foreground color to red
        jsr CHROUT

        ldx #<@num1
        ldy #>@num1
        jsr Print_Str
        bra @end

@2      lda #$1F                ;Change foreground color to blue
        jsr CHROUT

        ldx #<@num2
        ldy #>@num2
        jsr Print_Str


@end    lda #$05                ;Change foreground color to white
        jsr CHROUT
        rts

@player 	!pet    "player ",0
@choose 	!pet    "choose a",0
@column 	!pet    "column!",0
@num1   	!pet    "1",0
@num2   	!pet    "2",0


TextUIend
