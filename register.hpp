#ifndef REGISTER_HPP
#define REGISTER_HPP
	unsigned sext(unsigned x, int n) {
		return (x & (1U << (n - 1))) ? (((0xffffffff >> n) << n)| x) : x;
	}
	enum command {
		_LUI, _AUIPC, _JAL, _JALR, _BEQ, _BNE, _BLT, _BGE, _BLTU, _BGEU,
		_LB, _LH, _LW, _LBU, _LHU, _SB, _SH, _SW, _ADDI, _SLTI, _SLTIU,
		_XORI, _ORI, _ANDI, _SLLI, _SRLI, _SRAI, _ADD, _SUB, _SLL, _SLT,
		_SLTU,_XOR, _SRL, _SRA, _OR, _AND,_OUT
	};
	enum types {
		_U, _I, _B, _S, _J, _R
	};
	unsigned x[33] = { 0 };
	const unsigned& zero = x[0];
	unsigned& ra = x[1], & sp = x[2], & gp = x[3], & tp = x[4], & t0 = x[5], & t1 = x[6], & t2 = x[7], & fp = x[8], & s0 = x[8], & s1 = x[9], & a0 = x[10], & a1 = x[11], & a2 = x[12], & a3 = x[13], & a4 = x[14], & a5 = x[15], & a6 = x[16];
	unsigned& a7 = x[17], & s2 = x[18], & s3 = x[19], & s4 = x[20], & s5 = x[21], & s6 = x[22], & s7 = x[23], & s8 = x[24], & s9 = x[25], & s10 = x[26], & s11 = x[27], & t3 = x[28], & t4 = x[29], & t5 = x[30], & t6 = x[31], & pc = x[32];
	void yout(command op) {
		switch (op) {
		case _LUI:std::cout << "LUI"; break;
		case _AUIPC:std::cout << "AUIPC"; break;
		case _JAL:std::cout << "JAL"; break;
		case _JALR:std::cout << "JALR"; break;
		case _BEQ:std::cout << "BEQ"; break;
		case _BNE:std::cout << "BNE"; break;
		case _BLT:std::cout << "BLT"; break;
		case _BGE:std::cout << "BGE"; break;
		case _BLTU:std::cout << "BLTU"; break;
		case _BGEU:std::cout << "BGEU"; break;
		case _LB:std::cout << "LB"; break;
		case _LH:std::cout << "LH"; break;
		case _LW:std::cout << "LW"; break;
		case _LBU:std::cout << "LBU"; break;
		case _LHU:std::cout << "LHU"; break;
		case _SB:std::cout << "SB"; break;
		case _SH:std::cout << "SH"; break;
		case _ADDI:std::cout << "ADDI"; break;
		case _SW:std::cout << "SW"; break;
		case _SLTI:std::cout << "SLTI"; break;
		case _SLTIU:std::cout << "SLTIU"; break;
		case _XORI:std::cout << "XORI"; break;
		case _ORI:std::cout << "ORI"; break;
		case _ANDI:std::cout << "ANDI"; break;
		case _SLLI:std::cout << "SLLI"; break;
		case _SRLI:std::cout << "SRLI"; break;
		case _SRAI:std::cout << "SRAI"; break;
		case _ADD:std::cout << "ADD"; break;
		case _SUB:std::cout << "SUB"; break;
		case _SLL:std::cout << "SLL"; break;
		case _SLT:std::cout << "SLT"; break;
		case _SLTU:std::cout << "SLTU"; break;
		case _XOR:std::cout << "XOR"; break;
		case _SRL:std::cout << "SRL"; break;
		case _SRA:std::cout << "SRA"; break;
		case _OR:std::cout << "OR"; break;
		case _AND:std::cout << "AND"; break;
		case _OUT:std::cout << "OUT"; break;
		}
		std::cout << std::endl;
	}
#endif 

