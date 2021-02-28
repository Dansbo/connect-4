!cpu w65c02
;******************************* Boiler plate *********************************
*=$801
	!word	$080C			; Pointer to next BASIC line
	!word	$0001			; Line number $0001 = 1
	!byte	$9E			; SYS BASIC token
	!pet	" $810",0		; Address where ASM starts
	!word	$0000			; EOF BASIC program
*=$810
;********************************Inclusions************************************
!src	"cx16stuff/cx16.inc"
!src	"cx16stuff/vera0.9.inc"
!src	"bin2vera.inc"

	jsr Init_VERA
	jsr Load_bins
	rts
