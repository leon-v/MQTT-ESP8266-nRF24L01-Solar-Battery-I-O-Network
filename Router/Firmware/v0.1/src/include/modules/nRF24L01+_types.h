#ifndef NRF24L01_TYPES_H_
#define NRF24L01_TYPES_H_

#define n_R_REGISTER	0b00000000
#define n_W_REGISTER	0b00100000


#define n_CONFIG 		0x00
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned PRIM_RX	: 1;
		unsigned PWR_UP		: 1;
		unsigned CRCO		: 1;
		unsigned EN_CRC		: 1;
		unsigned MASK_MAX_RT: 1;
		unsigned MASK_TX_DS	: 1;
		unsigned MASK_RX_DR	: 1;
		unsigned Reserved	: 1;

	};
	struct{
		unsigned bit0	: 1;
		unsigned bit1	: 1;
		unsigned bit2	: 1;
		unsigned bit3	: 1;
		unsigned bit4	: 1;
		unsigned bit5	: 1;
		unsigned bit6	: 1;
		unsigned bit7	: 1;
	};
} n_CONFIG_t;

#define n_STATUS		0x07
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned TX_FULL	: 1;
		unsigned RX_P_NO	: 3;
		unsigned MAX_RT		: 1;
		unsigned TX_DS		: 1;
		unsigned RX_DR		: 1;
		unsigned Reserved	: 1;

	};
	struct{
		unsigned bit0	: 1;
		unsigned bit4	: 1;
		unsigned bit5	: 1;
		unsigned bit6	: 1;
		unsigned bit7	: 1;
	};
} n_STATUS_t;


#endif /* USER_CONFIG_H_ */