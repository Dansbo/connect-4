        jmp Bin2vera_end
; *************************** Global variables ********************************
Board   !bin   "connect4board.bin"
Pieces  !bin   "connect4pcs.bin"

Init_VERA:
        lda #0                  ;Set screen mode 40x30 (320x240)
        jsr Screen_set_mode

        lda #$01                ;Black background and white text
        sta COLORPORT

        lda #PET_CLEAR          ;Clear screen
        jsr CHROUT

        rts

Bin2vera_end:
