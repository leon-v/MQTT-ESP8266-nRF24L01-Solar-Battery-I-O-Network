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
	struct {
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

#define n_EN_AA			0x01
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned ENAA_P0	: 1;
		unsigned ENAA_P1	: 1;
		unsigned ENAA_P2	: 1;
		unsigned ENAA_P3	: 1;
		unsigned ENAA_P4	: 1;
		unsigned ENAA_P5	: 1;
		unsigned Reserved	: 2;

	};
	struct {
		unsigned bit0	: 1;
		unsigned bit1	: 1;
		unsigned bit2	: 1;
		unsigned bit3	: 1;
		unsigned bit4	: 1;
		unsigned bit5	: 1;
		unsigned bit6	: 1;
		unsigned bit7	: 1;
	};
} n_EN_AA_t;

#define n_EN_RXADDR		0x02
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned ERX_P0		: 1;
		unsigned ERX_P1		: 1;
		unsigned ERX_P2		: 1;
		unsigned ERX_P3		: 1;
		unsigned ERX_P4		: 1;
		unsigned ERX_P5		: 1;
		unsigned Reserved	: 2;

	};
	struct {
		unsigned bit0	: 1;
		unsigned bit1	: 1;
		unsigned bit2	: 1;
		unsigned bit3	: 1;
		unsigned bit4	: 1;
		unsigned bit5	: 1;
		unsigned bit6	: 1;
		unsigned bit7	: 1;
	};
} n_EN_RXADDR_t;

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
} n_STATUS_t;


#define n_RX_PW_P0		0x11
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned RX_PW_P0	: 6;
		unsigned Reserved	: 2;

	};
} n_RX_PW_P0_t;

#endif /* USER_CONFIG_H_ */