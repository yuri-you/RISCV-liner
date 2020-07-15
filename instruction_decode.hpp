#ifndef INSTRUCTION_DECODE_HPP
#define INSTRUCTION_DECODE_HPP
#include"register.hpp"
#include"instruction_fetch.hpp"
inline bool is_range_legal(unsigned x1) {
	return (x1 <= 31 && x1 >= 0);
}
struct ID {
	unsigned rd, rst1, rst2, immediate, rpc;//rd�ǵ�ַ,rst��ȡ����������
	command op;
	MEM* document;
private:
	unsigned I(unsigned data) {
		unsigned ans;
		ans = ((data & (((1U << 32) - 1U) & (~((1U << 20) - 1U)))) >> 20);//20-31 to 0-11
		return sext(ans, 12);
	}
	unsigned S(unsigned data) {
		unsigned ans;
		ans = ((data & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);//7-11 to 0-4
		ans |= ((data & (((1U << 32) - 1U) & (~((1U << 25) - 1U)))) >> 20);//25-31 to 5-11
		return sext(ans, 12);
	}
	unsigned B(unsigned data) {
		unsigned ans;
		ans = ((data & (((1U << 12) - 1U) & (~((1U << 8) - 1U)))) >> 7);//8-11 to 1-4
		ans |= ((data & (((1U << 31) - 1U) & (~((1U << 25) - 1U)))) >> 20);//25-30 to 5-11
		ans |= (data & (1U << 7)) << 4;//7 to 11
		ans |= (data & (1U << 31)) >> 19;//31 to 12
		return sext(ans, 13);
	}
	unsigned U(unsigned data) {
		unsigned ans;
		ans = (data & ((0xffffffff) & (~((1U << 12) - 1))));//12-31 to 12-31
		return ans;
	}
	unsigned J(unsigned data) {
		unsigned ans;
		ans = ((data & (((1U << 32) - 1U) & (~((1U << 21) - 1U)))) >> 20);//21-31 to 1-11
		ans |= (data & (1U << 20)) >> 9;//20 to 11
		ans |= (data & ((1U << 20) - 1U) & (~((1U << 12) - 1U)));//12-19 to 12-19;
		ans |= (data & (1U << 31)) >> 11;//31 to 20
		return sext(ans, 21);
	}
public:
	ID() {}
	ID(const IF& other) {
		if (other.op == _OUT) {
			op = other.op;
			immediate = a0 & 255U;
			return;
		}
		rd = other.rd;
		if (is_range_legal(other.rst1))rst1 = x[other.rst1];
		if (is_range_legal(other.rst2))rst2 = x[other.rst2];
		op = other.op;
		rpc = pc;
		document = other.document;
		switch (other.type) {
		case _B:immediate = B(other.memory); break;
		case _I:immediate = I(other.memory); break;
		case _J:immediate = J(other.memory); break;
		case _U:immediate = U(other.memory); break;
		case _S:immediate = S(other.memory); break;
		}
	}
};
#endif // !INSTRUCTION_DECODE

