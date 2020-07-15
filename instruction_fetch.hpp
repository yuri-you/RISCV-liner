#ifndef INSTRUCTION_FETCH_HPP
#define INSTRUCTION_FETCH_HPP
#include<iostream>
#include<cstring>
#include <iomanip>
#include"register.hpp"
//#include"execute.hpp"
unsigned count = 0;
class MEM;
struct IF {
	unsigned rd, rst1, rst2, memory;
	command op;
	types type;
	MEM* document;
	//IF(){}
	//IF(const IF& other) {
	//	rd = other.rd;
	//	rst1 = other.rst1;
	//	rst2 = other.rst2;
	//	memory = other.memory;
	//	op = other.op;
	//	type = other.type;
	//	document = other.document;
	//}
};
class MEM {
public:
	unsigned size, * memory;
	friend struct EX;
private:
	void read_data() {
		char get_in;
		get_in = getchar();
		while (~get_in) {
			if (get_in == '@') {
				unsigned position = 0;
				for (unsigned i = 0; i < 8; ++i) {
					position <<= 4;
					get_in = getchar();
					position += (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
				}
				pc = position;
				get_in = getchar();
				while ((~get_in) && (!isupper(get_in)) && (!isdigit(get_in))&&(get_in!='@')) {
					get_in = getchar();
				}
			}
			else {
				unsigned position = 0;
				for (int i = 0; i < 4; ++i) {
					unsigned tmp = 0;
					tmp = (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
					get_in = getchar();
					tmp <<= 4;
					tmp += (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
					position |= (tmp << (i<<3));
					get_in = getchar();
					while ((~get_in) && (!isupper(get_in)) && (!isdigit(get_in)) && (get_in != '@')) {
						get_in = getchar();
					}
				}
				memory[pc >> 2] = position;
				pc += 4;
			}

		}
	}
public:
	MEM() {
		size = 1 << 20;
		memory = new unsigned[size];
		memset(memory, 0, 4 * size);
		read_data();
		pc = 0;
	}
	~MEM() { delete[]memory;}
	//template<class T>
	//T fetch_data(uint place,T type_of_function){
	//	return *((T*)(&memory[place]));
	//}
	IF fetch();
};
IF MEM::fetch() {
	IF inf;
	unsigned mem = memory[pc >> 2];
	if (mem == 0x0ff00513U) {
		inf.op = _OUT;
		return inf;
	}
	inf.memory = mem;
	inf.document = this;
	switch (mem & ((1U << 7) - 1U)) {
	case 55: {//LUI
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
		inf.type = _U;
		inf.op = _LUI;
		break;
	}
	case 23: {//AUIPC
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1)))) >> 7);
		inf.type = _U;
		inf.op = _AUIPC;
		break;
	}
	case 111: {//JAL
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
		inf.type = _J;
		inf.op = _JAL;
		break;
	}
	case 103: {//JALR
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
		inf.rst1 = ((mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)))) >> 15);
		inf.type = _I;
		inf.op = _JALR;
		break;
	}
	case 99: {
		inf.rst1 = ((mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)))) >> 15);
		inf.rst2 = ((mem & (((1U << 25) - 1U) & (~((1U << 20) - 1U)))) >> 20);
		inf.type = _B;
		switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {

		case 0: {//BEQ
			inf.op = _BEQ;
			break;
		}
		case 1: {//BNE
			inf.op = _BNE;
			break;
		}
		case 4: {//BLT
			inf.op = _BLT;
			break;
		}
		case 5: {//BGE
			inf.op = _BGE;
			break;
		}
		case 6: {//BLTU
			inf.op = _BLTU;
			break;
		}
		case 7: {//BGEU
			inf.op = _BGEU;
			break;
		}
		}
		break;
	}
	case 3: {
		inf.rst1 = (mem & (((1U << 20) - 1) & (~((1U << 15) - 1U)))) >> 15;
		inf.rd = (mem & (((1U << 12) - 1) & (~((1U << 7) - 1U)))) >> 7;
		inf.type = _I;
		switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
		case 0: {//LB
			inf.op = _LB;
			break;
		}
		case 1: {//LH
			inf.op = _LH;
			break;
		}
		case 2: {//LW
			inf.op = _LW;
			break;
		}
		case 4: {//LBU
			inf.op = _LBU;
			break;
		}
		case 5: {//LHU
			inf.op = _LHU;
			break;
		}
		}
		break;
	}
	case 35: {//S��
		inf.rst1 = ((mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)))) >> 15);
		inf.rst2 = ((mem & (((1U << 25) - 1U) & (~((1U << 20) - 1U)))) >> 20);
		inf.type = _S;
		switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
		case 0:inf.op = _SB; break;
		case 1:inf.op = _SH; break;
		case 2:inf.op = _SW; break;
		}
		break;
	}
	case 19: {
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
		inf.rst1 = ((mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)))) >> 15);
		switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
		case 1:inf.op = _SLLI; inf.type = _I; break;
		case 5: {
			inf.type = _I;
			if (mem >> 30) {
				inf.op = _SRAI;
				inf.memory &= (~(1 << 30));
			}//�ѵ�30λ����
			else inf.op = _SRLI;
			break;
		}
		case 0:inf.type = _I; inf.op = _ADDI; break;
		case 2:inf.type = _I; inf.op = _SLTI; break;
		case 3:inf.type = _I; inf.op = _SLTIU; break;
		case 4:inf.type = _I; inf.op = _XORI; break;
		case 6:inf.type = _I; inf.op = _ORI; break;
		case 7:inf.type = _I; inf.op = _ANDI; break;
		}
		break;
	}
	case 51: {
		inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
		inf.rst1 = ((mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)))) >> 15);
		inf.rst2 = ((mem & (((1U << 25) - 1U) & (~((1U << 20) - 1U)))) >> 20);
		inf.type = _R;
		switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
		case 0: {
			if (mem >> 30) inf.op = _SUB;
			else inf.op = _ADD;
			break;
		}
		case 1:inf.op = _SLL; break;
		case 2:inf.op = _SLT; break;
		case 3:inf.op = _SLTU; break;
		case 4:inf.op = _XOR; break;
		case 5: {
			if (mem >> 30) inf.op = _SRA;
			else inf.op = _SRL;
			break;
		}
		case 6:inf.op = _OR; break;
		case 7:inf.op = _AND; break;
		}
	} 
	}
	//count++;
	//std::cout << std::dec << count << ' ' << std::hex << pc << ' ';
	//yout(inf.op);
	//for (int i = 0; i < 32; ++i)std::cout << std::dec << x[i] << ' ';
	//std::cout << std::endl;
	return inf;
}
#endif 