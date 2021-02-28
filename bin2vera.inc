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
        lda #$1F
        sta VERA_ADDR_H
        lda #$20
        sta VERA_ADDR_M
        stz VERA_ADDR_L

        lda #%11000001
        sta VERA_DATA0

        stz VERA_DATA0
        stz VERA_DATA0
        stz VERA_DATA0
        stz VERA_DATA0

        lda #%00010000
        sta VERA_DATA0

        stz VERA_DATA0
        stz VERA_DATA0
        stz VERA_DATA0
        stz VERA_DATA0

        lda #1
        ldx #8
        ldy #0

        jsr SETLFS

        lda #(Pieces-Board)
        ldx #<Board
        ldy #>Board
        jsr SETNAM

        ldy #$40
        ldx #$00
        lda #$02
        jsr LOAD
        rts

Bin2vera_end:
