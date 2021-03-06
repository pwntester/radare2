#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>

#include <v810_disas.h>

static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	int ret = R_TRUE;
	struct v810_cmd cmd;

	ret = v810_decode_command (buf, &cmd);

	snprintf (op->buf_asm, R_ASM_BUFSIZE, "%s %s", cmd.instr, cmd.operands);
	op->size = ret;

	return ret;
}

RAsmPlugin r_asm_plugin_v810 = {
	.name = "v810",
	.license = "LGPL3",
	.desc = "V810 disassembly plugin",
	.arch = "v810",
	.bits = 32,
	.init = NULL,
	.fini = NULL,
	.disassemble = &disassemble,
	.modify = NULL,
	.assemble = NULL
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_v810
};
#endif
