.globalmain
.data

.text

main mov r0,#0xe608; instruccion de transferencia de informacion
	 mov r0,#0x400f; r0=0x400fe608     r0=0x400fe608  - 0x1000
	 mov r1,#0x1000; habilitar PORTN
	 str r1[r0]; de registros a memoria
	 ; isa instruction set architecture
