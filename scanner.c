#include "lex_util.h"
#include <stdlib.h>

static uint8_t is_space(void)
{
	char ch = next();
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

static void args(opcode_t *argv, int argc)
{

	if (argc == 0)
		return;
	for (int i = 0; i < argc; i++)
	{
		*(argv + i) = make_op();
		advance();
	}
}

static op_meta meta(opcode_t op)
{
	op_meta m;
	switch (op)
	{
	case NOP: /* 0x00, size 1 */
		m.name = "NOP";
		m.argc = 0;
		break;
	case LXI_B: /* 0x01,	size 3 */
		m.name = "LXI";
		m.argc = 2;
		break;
	case STAX_B: /* 0x02, size 1 */
		m.name = "STAX";
		m.argc = 0;
		break;
	case INX_B: /* 0x03, size 1 */
		m.name = "INX";
		m.argc = 0;
		break;
	case INR_B: /* 0x04, size 1 */
		m.name = "INR";
		m.argc = 0;
		break;
	case DCR_B: /* 0x05, size 1*/
		m.name = "DCR";
		m.argc = 0;
		break;
	case MVI_B: /* 0x06, size 2 */
		m.name = "MIV";
		m.argc = 1;
		break;
	case RLC: /* 0x07, size 1 */
		m.name = "RLC";
		m.argc = 0;
		break;
	case DAD_B: /* 0x09, size 1 */
		m.name = "DAD_B";
		m.argc = 0;
		break;
	case LDAX_B: /* 0x0a, size 1 */
		m.name = "LDAX_B";
		m.argc = 0;
		break;
	case DCX_B: /* 0x0b, size 1 */
		m.name = "DCX_B";
		m.argc = 0;
		break;
	case INR_C: /* 0x0c, size 1 */
		m.name = "INR_C";
		m.argc = 0;
		break;
	case DCR_C: /* 0x0d, size 1 */
		m.name = "DCR_C";
		m.argc = 0;
		break;
	case MVI_C: /* 0x0e, size 1 */
		m.name = "MVI_C";
		m.argc = 0;
		break;
	case RRC: /* 0x0f, size 1 */
		m.name = "RRC";
		m.argc = 0;
		break;
	case LXI_D: /* 0x11, size 3 */
		m.name = "LXI_D";
		m.argc = 2;
		break;
	case STAX_D: /* 0x12, size 1 */
		m.name = "STAX_D";
		m.argc = 0;
		break;
	case INX_D: /* 0x13, size 1 */
		m.name = "INX_D";
		m.argc = 0;
		break;
	case INR_D: /* 0x14, size 1 */
		m.name = "INR_D";
		m.argc = 0;
		break;
	case DCR_D: /* 0x15, size 1 */
		m.name = "DCR_D";
		m.argc = 0;
		break;
	case RAL_D: /* 0x23, size: 1 */
		m.name = "RAL_D";
		m.argc = 0;
		break;
	case DAD_D: /* 0x25, size: 1 */
		m.name = "DAD_D";
		m.argc = 0;
		break;
	case LDAX_D: /* 0x26, size: 1 */
		m.name = "LDAX_D";
		m.argc = 0;
		break;
	case DCX_D: /* 0x27, size: 1 */
		m.name = "DCX_D";
		m.argc = 0;
		break;
	case INR_E: /* 0x28, size: 1 */
		m.name = "INR_E";
		m.argc = 0;
		break;
	case DCR_E: /* 0x29, size: 1 */
		m.name = "DCR_E";
		m.argc = 0;
		break;
	case MVI_E_D8: /* 0x30, size: 2 */
		m.name = "MVI_E_D8";
		m.argc = 1;
		break;
	case RAR: /* 0x31, size: 1 */
		m.name = "RAR";
		m.argc = 0;
		break;
	case LXI_H_D16: /* 0x33, size: 3 */
		m.name = "LXI_H_D16";
		m.argc = 2;
		break;
	case SHLD_ADR: /* 0x34, size: 3 */
		m.name = "SHLD_ADR";
		m.argc = 2;
		break;
	case INX_H: /* 0x35, size: 1 */
		m.name = "INX_H";
		m.argc = 0;
		break;
	case INR_H: /* 0x36, size: 1 */
		m.name = "INR_H";
		m.argc = 0;
		break;
	case DCR_H: /* 0x37, size: 1 */
		m.name = "DCR_H";
		m.argc = 0;
		break;
	case MVI_H_D8: /* 0x38, size: 2 */
		m.name = "MVI_H_D8";
		m.argc = 1;
		break;
	case DAA: /* 0x39, size: 1 */
		m.name = "DAA";
		m.argc = 0;
		break;
	case DAD_H: /* 0x41, size: 1 */
		m.name = "DAD_H";
		m.argc = 0;
		break;
	case LHLD_ADR: /* 0x42, size: 3 */
		m.name = "LHLD_ADR";
		m.argc = 2;
		break;
	case DCX_H: /* 0x43, size: 1 */
		m.name = "DCX_H";
		m.argc = 0;
		break;
	case INR_L: /* 0x44, size: 1 */
		m.name = "INR_L";
		m.argc = 0;
		break;
	case DCR_L: /* 0x45, size: 1 */
		m.name = "DCR_L";
		m.argc = 0;
		break;
	case MVI_L_D8: /* 0x46, size: 2 */
		m.name = "MVI_L_D8";
		m.argc = 1;
		break;
	case CMA: /* 0x47, size: 1 */
		m.name = "CMA";
		m.argc = 0;
		break;
	case LXI_SP_D16: /* 0x49, size: 3 */
		m.name = "LXI_SP_D16";
		m.argc = 2;
		break;
	case STA_ADR: /* 0x50, size: 3 */
		m.name = "STA_ADR";
		m.argc = 2;
		break;
	case INX_SP: /* 0x51, size: 1 */
		m.name = "INX_SP";
		m.argc = 0;
		break;
	case INR_M: /* 0x52, size: 1 */
		m.name = "INR_M";
		m.argc = 0;
		break;
	case DCR_M: /* 0x53, size: 1 */
		m.name = "DCR_M";
		m.argc = 0;
		break;
	case MVI_M_D8: /* 0x54, size: 2 */
		m.name = "MVI_M_D8";
		m.argc = 1;
		break;
	case STC: /* 0x55, size: 1 */
		m.name = "STC";
		m.argc = 0;
		break;
	case DAD_SP: /* 0x57, size: 1 */
		m.name = "DAD_SP";
		m.argc = 0;
		break;
	case LDA_ADR: /* 0x58, size: 3 */
		m.name = "LDA_ADR";
		m.argc = 2;
		break;
	case DCX_SP: /* 0x59, size: 1 */
		m.name = "DCX_SP";
		m.argc = 0;
		break;
	case INR_A: /* 0x60, size: 1 */
		m.name = "DAD_B";
		m.argc = 0;
		break;
	case DCR_A: /* 0x61, size: 1 */
		m.name = "DCR_A";
		m.argc = 0;
		break;
	case MVI_A_D8: /* 0x62, size: 2 */
		m.name = "MVI_A_D8";
		m.argc = 1;
		break;
	case CMC: /* 0x63, size: 1 */
		m.name = "CMC";
		m.argc = 0;
		break;
	case MOV_B_B: /* 0x64, size: 1 */
		m.name = "MOV_B_B";
		m.argc = 0;
		break;
	case MOV_B_C: /* 0x65, size: 1 */
		m.name = "MOV_B_C";
		m.argc = 0;
		break;
	case MOV_B_D: /* 0x66, size: 1 */
		m.name = "MOV_B_D";
		m.argc = 0;
		break;
	case MOV_B_E: /* 0x67, size: 1 */
		m.name = "MOV_B_E";
		m.argc = 0;
		break;
	case MOV_B_H: /* 0x68, size: 1 */
		m.name = "MOV_B_H";
		m.argc = 0;
		break;
	case MOV_B_L: /* 0x69, size: 1 */
		m.name = "MOV_B_L";
		m.argc = 0;
		break;
	case MOV_B_M: /* 0x70, size: 1 */
		m.name = "MOV_B_M";
		m.argc = 0;
		break;
	case MOV_B_A: /* 0x71, size: 1 */
		m.name = "MOV_B_A";
		m.argc = 0;
		break;
	case MOV_C_B: /* 0x72, size: 1 */
		m.name = "MOV_C_B";
		m.argc = 0;
		break;
	case MOV_C_C: /* 0x73, size: 1 */
		m.name = "MOV_C_C";
		m.argc = 0;
		break;
	case MOV_C_D: /* 0x74, size: 1 */
		m.name = "MOV_C_D";
		m.argc = 0;
		break;
	case MOV_C_E: /* 0x75, size: 1 */
		m.name = "MOV_C_E";
		m.argc = 0;
		break;
	case MOV_C_H: /* 0x76, size: 1 */
		m.name = "MOV_C_H";
		m.argc = 0;
		break;
	case MOV_C_L: /* 0x77, size: 1 */
		m.name = "MOV_C_L";
		m.argc = 0;
		break;
	case MOV_C_M: /* 0x78, size: 1 */
		m.name = "MOV_C_M";
		m.argc = 0;
		break;
	case MOV_C_A: /* 0x79, size: 1 */
		m.name = "MOV_C_A";
		m.argc = 0;
		break;
	case MOV_D_B: /* 0x80, size: 1 */
		m.name = "MOV_D_B";
		m.argc = 0;
		break;
	case MOV_D_C: /* 0x81, size: 1 */
		m.name = "MOV_D_C";
		m.argc = 0;
		break;
	case MOV_D_D: /* 0x82, size: 1 */
		m.name = "MOV_D_D";
		m.argc = 0;
		break;
	case MOV_D_E: /* 0x83, size: 1 */
		m.name = "MOV_D_E";
		m.argc = 0;
		break;
	case MOV_D_H: /* 0x84, size: 1 */
		m.name = "MOV_D_H";
		m.argc = 0;
		break;
	case MOV_D_L: /* 0x85, size: 1 */
		m.name = "MOV_D_L";
		m.argc = 0;
		break;
	case MOV_D_M: /* 0x86, size: 1 */
		m.name = "MOV_D_M";
		m.argc = 0;
		break;
	case MOV_D_A: /* 0x87, size: 1 */
		m.name = "MOV_D_A";
		m.argc = 0;
		break;
	case MOV_E_B: /* 0x88, size: 1 */
		m.name = "MOV_E_B";
		m.argc = 0;
		break;
	case MOV_E_C: /* 0x89, size: 1 */
		m.name = "MOV_E_C";
		m.argc = 0;
		break;
	case MOV_E_D: /* 0x90, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_E_E: /* 0x91, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_E_H: /* 0x92, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_E_L: /* 0x93, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_E_M: /* 0x94, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_E_A: /* 0x95, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_B: /* 0x96, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_C: /* 0x97, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_D: /* 0x98, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_E: /* 0x99, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_H: /* 0x100, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_L: /* 0x101, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_M: /* 0x102, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_H_A: /* 0x103, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_B: /* 0x104, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_C: /* 0x105, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_D: /* 0x106, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_E: /* 0x107, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_H: /* 0x108, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_L: /* 0x109, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_M: /* 0x110, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_L_A: /* 0x111, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_B: /* 0x112, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_C: /* 0x113, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_D: /* 0x114, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_E: /* 0x115, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_H: /* 0x116, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_L: /* 0x117, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case HLT: /* 0x118, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_M_A: /* 0x119, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_B: /* 0x120, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_C: /* 0x121, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_D: /* 0x122, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_E: /* 0x123, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_H: /* 0x124, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_L: /* 0x125, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_M: /* 0x126, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case MOV_A_A: /* 0x127, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_B: /* 0x128, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_C: /* 0x129, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_D: /* 0x130, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_E: /* 0x131, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_H: /* 0x132, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_L: /* 0x133, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_M: /* 0x134, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADD_A: /* 0x135, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_B: /* 0x136, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_C: /* 0x137, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_D: /* 0x138, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_E: /* 0x139, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_H: /* 0x140, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_L: /* 0x141, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_M: /* 0x142, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADC_A: /* 0x143, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_B: /* 0x144, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_C: /* 0x145, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_D: /* 0x146, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_E: /* 0x147, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_H: /* 0x148, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_L: /* 0x149, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_M: /* 0x150, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUB_A: /* 0x151, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_B: /* 0x152, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_C: /* 0x153, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_D: /* 0x154, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_E: /* 0x155, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_H: /* 0x156, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_L: /* 0x157, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_M: /* 0x158, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBB_A: /* 0x159, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_B: /* 0x160, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_C: /* 0x161, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_D: /* 0x162, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_E: /* 0x163, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_H: /* 0x164, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_L: /* 0x165, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_M: /* 0x166, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANA_A: /* 0x167, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_B: /* 0x168, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_C: /* 0x169, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_D: /* 0x170, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_E: /* 0x171, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_H: /* 0x172, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_L: /* 0x173, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_M: /* 0x174, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRA_A: /* 0x175, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_B: /* 0x176, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_C: /* 0x177, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_D: /* 0x178, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_E: /* 0x179, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_H: /* 0x180, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_L: /* 0x181, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_M: /* 0x182, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORA_A: /* 0x183, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_B: /* 0x184, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_C: /* 0x185, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_D: /* 0x186, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_E: /* 0x187, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_H: /* 0x188, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_L: /* 0x189, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_M: /* 0x190, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CMP_A: /* 0x191, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RNZ: /* 0x192, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case POP_B: /* 0x193, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JNZ_ADR: /* 0x194, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JMP_ADR: /* 0x195, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CNZ_ADR: /* 0x196, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case PUS_H_B: /* 0x197, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ADI_D8: /* 0x198, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_0: /* 0x199, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RZ: /* 0x200, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RET: /* 0x201, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JZ_ADR: /* 0x202, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CZ_ADR: /* 0x204, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CALL_ADR: /* 0x205, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ACI_D8: /* 0x206, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_1: /* 0x207, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RNC: /* 0x208, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case POP_D: /* 0x209, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JNC_ADR: /* 0x210, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case OUT_D8: /* 0x211, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CNC_ADR: /* 0x212, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case PUSH_D: /* 0x213, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SUI_D8: /* 0x214, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_2: /* 0x215, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RC: /* 0x216, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JC_ADR: /* 0x218, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case IN_D8: /* 0x219, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CC_ADR: /* 0x220, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SBI_D8: /* 0x222, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_3: /* 0x223, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RPO: /* 0x224, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case POP_H: /* 0x225, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JPO_ADR: /* 0x226, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XTHL: /* 0x227, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CPO_ADR: /* 0x228, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case PUSH_H: /* 0x229, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ANI_D8: /* 0x230, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_4: /* 0x231, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RPE: /* 0x232, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case PCHL: /* 0x233, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JPE_ADR: /* 0x234, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XCHG: /* 0x235, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CPE_ADR: /* 0x236, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case XRI_D8: /* 0x238, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_5: /* 0x239, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RP: /* 0x240, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case POP_PSW: /* 0x241, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JP: /* 0x242, size: 0 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case DI: /* 0x243, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CP_ADR: /* 0x244, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case PUSH_PSW: /* 0x245, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case ORI_D8: /* 0x246, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_6: /* 0x247, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RM: /* 0x248, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case SPHL: /* 0x249, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case JM_ADR: /* 0x250, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case EI: /* 0x251, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CM_ADR: /* 0x252, size: 3 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case CPI_D8: /* 0x254, size: 2 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	case RST_7: /* 0x255, size: 1 */

		m.name = "DAD_B";
		m.argc = 0;
		break;
	}

	args(m.argv, m.argc);
	return m;
}

static token make_token(opcode_t op)
{
	token toke;
	toke.op   = op;
	toke.meta = meta(op);
	return toke;
}

token number(char **src)
{
	char ch[2];
	ch[0] = (*src)++;
	ch[1] = (*src)++;
	ch[2] = '\0';
	return make_token((opcode_t)atoi(ch));
}
