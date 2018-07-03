
.cpu cortex-m0
.thumb

.thumb_func
.global _start
_start:
stacktop: .word 0x20001000
.word hang
.word hang
.word hang
.thumb_func
hang:   b .
nop
nop
nop
.end

