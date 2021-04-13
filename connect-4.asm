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
!src	"TextUI.inc"
!src	"winscenarios.inc"

	jmp main

!src	"globals.inc"

;***********************************Main***************************************

main
	jsr Init_VERA
	jsr Load_bins

Init_IRQ:
	lda IRQVec
	sta default_irq_vector
	lda IRQVec+1
	sta default_irq_vector+1 	;Save current IRQ Vector to new memory address

	sei				;Stop interrupts while replacing Vector
	lda #<Custom_IRQ
	sta IRQVec
	lda #>Custom_IRQ
	sta IRQVec+1
	lda #$01			;Make VERA only set IRQ at VSync
	sta VERA_IEN
	cli				;Enable interrupts now Custom Vector is set.

@Main_loop:
	wai				;Wait for IRQ PROBLEM ATM!!
	lda Vsync_enabled
	beq @Main_loop			;If not vsync then wait for vsync
	jsr TextUI
	jsr GETIN
	cmp #0				;If no input wait for input
	beq @Main_loop
	cmp #$51			;If Q then exit game
	beq @Quit
	stz Vsync_enabled		;Reset Vsync_enabled
	bra @Main_loop			;Unexpected keystroke back to loop

@Quit:
	sei				;Disable IRQ while restoring default_irq_vector
	lda default_irq_vector
	sta IRQVec
	lda default_irq_vector+1
	sta IRQVec+1
	cli				;Reenable IRQ
	rts

Custom_IRQ
	lda VERA_ISR
	and #$01
	beq @continue			;Non Vsync continue to normal IRQ
	lda #1
	sta Vsync_enabled


@continue
	jmp (default_irq_vector)
