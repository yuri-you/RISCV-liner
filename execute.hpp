#ifndef EXECUTE_HPP
#define EXECUTE_HPP
#include"register.hpp"
#include"instruction_fetch.hpp"
#include"instruction_decode.hpp"
struct EX {
	unsigned result;
	command op;
	unsigned rd, rpc, rst2;
	MEM* document;
	EX() {}
	EX(const ID& other) {
		if (other.op == _OUT) {
			op = other.op;
			result = other.immediate;
			return;
		}
		rst2 = other.rst2;
		rd = other.rd;
		document = other.document;
		rpc=other.rpc;
		op = other.op;
		switch (op) {
		case _AUIPC:result = rpc + other.immediate; rpc += 4;; break;
		case _JAL:result = rpc + 4; rpc += other.immediate; break;
		case _JALR:result = rpc + 4; rpc = (other.rst1 + other.immediate) & (~1); break;
		case _BEQ: {
			if (other.rst1 == other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _BNE: {
			if (other.rst1 != other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _BLT: {
			if ((int)other.rst1 < (int)other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _BGE: {
			if ((int)other.rst1 >= (int)other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _BLTU: {
			if (other.rst1 < other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _BGEU: {
			if (other.rst1 >= other.rst2)rpc += other.immediate;
			else rpc += 4;
			break;
		}
		case _SB:case _SW:case _SH:
		case _LB: case _LH:case _LW:case _LBU:case _LHU:
		case _ADDI:result = other.rst1 + other.immediate; rpc += 4; break;
		case _SLTI:result = ((int)other.rst1 < (int)other.immediate) ? 1 : 0; rpc += 4; break;
		case _SLTIU:result = (other.rst1 < other.immediate) ? 1 : 0; rpc += 4; break;
		case _XORI:result = other.rst1 ^ other.immediate;  rpc += 4; break;
		case _ORI:result = other.rst1 | other.immediate; rpc += 4; break;
		case _ANDI:result = other.rst1 & other.immediate; rpc += 4; break;
		case _SLLI: {
			if (!(other.immediate & (1U << 5))) {
				result = other.rst1 << other.immediate;
			}
			rpc += 4;
			break;
		}
		case _SRLI: {
			if (!(other.immediate & (1U << 5))) {
				result = other.rst1 >> other.immediate;
			}
			rpc += 4;
			break;
		}
		case _SRAI: {
			if (!(other.immediate & (1U << 5))) {
				result = sext(other.rst1 >> other.immediate,32-other.immediate);
			}
			rpc += 4;
			break;
		}
		case _ADD:result = other.rst1 + other.rst2;  rpc += 4; break;
		case _SUB:result = other.rst1 - other.rst2;  rpc += 4; break;
		case _SLL:result = other.rst1 << (other.rst2 & ((1U << 5) - 1U));  rpc += 4; break;
		case _SLT:result = ((int)other.rst1 < (int)other.rst2) ? 1 : 0; rpc += 4; break;
		case _SLTU:result = (other.rst1 < other.rst2) ? 1 : 0; rpc += 4; break;
		case _XOR:result = other.rst1 ^ other.rst2;  rpc += 4; break;
		case _OR:result = other.rst1 | other.rst2;  rpc += 4; break;
		case _SRL:result = other.rst1 >> (other.rst2 & ((1U << 5) - 1U)); rpc += 4; break;
		case _SRA:result = sext(other.rst1 >> (other.rst2 & ((1U << 5) - 1U)), 32U - (other.rst2 & ((1U << 5) - 1U)));  rpc += 4; break;
		case _AND:result = other.rst1 & other.rst2; rpc += 4; break;
		default: result = other.immediate; rpc += 4;
		}

	}
};
#endif