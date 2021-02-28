        jmp Bin2vera_end
; *************************** Global variables ********************************
Board   !text   "connect4board.bin"
Pieces  !text   "connect4pcs.bin"
binend:

Init_VERA:
        lda #0                  ;Set screen mode 40x30 (320x240)
        jsr Screen_set_mode

        lda #$01                ;Black background and white text
        sta COLORPORT

        lda #PET_CLEAR          ;Clear screen
        jsr CHROUT

        rts

Load_Board:
        lda #$06                ;Map Height/width disabled, 4BPP
        sta VERA_L0_CONFIG

        +VERA_SET_ADDR $1F200, INC1

        stz VERA_L0_MAPBASE     ;Map base disabled

        lda #$20                ; image start address (($04000 >> 11) = 2) << 2
        sta VERA_L0_TILEBASE

        stz VERA_L0_HSCROLL_L
        stz VERA_L0_VSCROLL_L
        stz VERA_L0_VSCROLL_H

        lda #1			; Logical file number
	ldx #8			; Device 8 = sd card
	ldy #0			; 0=ignore address in bin file
				; 1=use address in bin file
	jsr SETLFS

        lda #(Pieces-Board)
        ldx #<Board
        ldy #>Board
        jsr SETNAM

        ldy #$40		; VERA HIGH/MID address
	ldx #$00		; VERA LOW address
	lda #$02		; VERA BANK + 2
	jsr LOAD

        rts

Bin2vera_end:
