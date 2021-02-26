!cpu w65c02

*=$0801
	!word	$080C			; Pointer to next BASIC line
	!word	$000A			; Line number $000A = 10
	!byte	$9E			; SYS BASIC token
	!pet	" $810",0		; Address where ASM starts
	!word	$0000			; EOF BASIC program
*=$0810

; ************************** Global Constants *********************************
