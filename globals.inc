	jmp globals_end
;******************************************************************************
;				Constants
;******************************************************************************
IRQVec = $0314


;******************************************************************************
;				Variables
;******************************************************************************
Board   		!text   "connect4board.bin"
Pieces  		!text   "connect4pcs.bin"
Sprites 		!text   "spriteattrib.bin"
Binend:
Player  		!byte   0
default_irq_vector	!word	0
Vsync_enabled		!byte	0
Timer_enabled		!byte	0
ticks			!byte	0
seconds			!byte	0
minutes			!byte	0
Game			!pet 	"game time:",0
Colon			!pet	":"


globals_end
