!cpu w65c02
	+SYS_LINE
;********************************Inclusions************************************
!src	"cx16stuff/cx16.inc"
!src	"cx16stuff/vera0.9.inc"
!src	"bin2vera.inc"

	jsr Init_VERA
	rts
