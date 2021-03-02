        jmp Bin2vera_end
; *************************** Global variables ********************************
Board   !text   "connect4board.bin"
Pieces  !text   "connect4pcs.bin"
Sprites !text   "spriteattrib.bin"
Binend:

;******************************************************************************
; Sets Address and Bank number for VERA
;******************************************************************************
; Uses: A, X, Y
;******************************************************************************
!macro LOAD_VERA .addr, .bank {
        ldy #>.addr
        ldx #<.addr
        lda #.bank+2
        jsr LOAD
}
;******************************************************************************
; Sets lenght of filename and address for SETNAM routine
;******************************************************************************
; Uses: A, X, Y
;******************************************************************************

!macro SET_NAME .len, .addr {
        lda #.len
        ldx #<.addr
        ldy #>.addr
        jsr SETNAM
}

Init_VERA:
        lda #0                  ;Set screen mode 40x30 (320x240)
        jsr Screen_set_mode

        lda #$01                ;Black background and white text
        sta COLORPORT

        lda #PET_CLEAR          ;Clear screen
        jsr CHROUT

        rts

Load_bins:
        lda #$06                ; Map height/ width disabled ,  Bitmap mode 4BPP
        sta VERA_L0_CONFIG

        stz VERA_L0_MAPBASE     ; Map base disabled

        lda #$20                ; image start address (($04000 >> 11) = 2) << 2
        sta VERA_L0_TILEBASE

        stz VERA_L0_HSCROLL_H

        stz VERA_L0_HSCROLL_L
        stz VERA_L0_VSCROLL_L

        stz VERA_L0_VSCROLL_H

        lda #1                  ; Logical file number
        ldx #8                  ; Device 8 = SDcard
        ldy #0                  ; 0=ignore address in bin file

        jsr SETLFS

        +SET_NAME (Pieces-Board), Board

        +LOAD_VERA $4000, 0     ;LOAD to VERA address $04000

        lda #%01110001          ; Current field = 0, enable sprite, layers enabled and output mode 1
        sta VERA_DC_VIDEO

        +SET_NAME (Sprites-Pieces), Pieces

        +LOAD_VERA $D600, 0     ;LOAD to VERA address $0D600

        +SET_NAME (Binend-Sprites), Sprites

        +LOAD_VERA $FC08, 1

        rts

Bin2vera_end:
