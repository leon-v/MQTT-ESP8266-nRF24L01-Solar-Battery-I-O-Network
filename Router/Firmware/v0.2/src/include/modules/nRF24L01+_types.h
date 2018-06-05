#ifndef NRF24L01_TYPES_H_
#define NRF24L01_TYPES_H_

#define n_R_REGISTER	0b00000000
#define n_W_REGISTER	0b00100000
#define n_R_RX_PAYLOAD  0b01100001
#define n_W_TX_PAYLOAD  0b10100000
#define n_FLUSH_TX      0b11100001
#define n_FLUSH_RX      0b11100010
#define n_R_RX_PL_WID	0b01100000


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

#define n_SETUP_AW		0x02
typedef union{
    struct {
		unsigned byte 		: 8;
	};
    struct {
        unsigned AW         : 2;
        unsigned Reserved	: 6;
    };
} n_SETUP_AW_t;


#define n_SETUP_RETR    0x04
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned ARC		: 4;
		unsigned ARD        : 4;

	};
} n_SETUP_RETR_t;

#define n_RF_CH         0x05
typedef union {
    struct {
		unsigned byte   : 8;
	};
    struct {
        unsigned RF_CH  : 7;
    };
} n_RF_CH_t;

#define n_RF_SETUP		0x06
typedef union {
    struct {
		unsigned byte       : 8;
	};
    struct {
        unsigned Obsolete   : 1;
        unsigned RF_PWR     : 2;
        unsigned RF_DR_HIGH : 1;
        unsigned PLL_LOCK   : 1;
        unsigned RF_DR_LOW  : 1;
        unsigned Reserved   : 1;
        unsigned CONT_WAVE  : 1;
    };
} n_RF_SETUP_t;


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

#define n_TX_ADDR       0x10

#define n_RX_PW_P0		0x11
#define n_RX_PW_P1		0x12
#define n_RX_PW_P2		0x13
#define n_RX_PW_P3		0x14
#define n_RX_PW_P4		0x15
#define n_RX_PW_P5		0x16
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned RX_PW		: 6;
		unsigned Reserved	: 2;

	};
} n_RX_PW_t;

#define n_RX_ADDR_P0		0x0A
#define n_RX_ADDR_P1		0x0B
#define n_RX_ADDR_P2		0x0C
#define n_RX_ADDR_P3		0x0D
#define n_RX_ADDR_P4		0x0E
#define n_RX_ADDR_P5		0x0F


#define n_DYNPD				0x1C
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned DPL_P0		: 1;
		unsigned DPL_P1		: 1;
		unsigned DPL_P2		: 1;
		unsigned DPL_P3		: 1;
		unsigned DPL_P4		: 1;
		unsigned DPL_P5		: 1;
		unsigned Reserved	: 2;

	};
} n_DYNPD_t;


#define n_FEATURE			0x1D
typedef union{
	struct {
		unsigned byte : 8;
	};
	struct {
		unsigned EN_DYN_ACK	: 1;
		unsigned EN_ACK_PAY	: 1;
		unsigned EN_DPL		: 1;
		unsigned Reserved	: 5;
	};
} n_FEATURE_t;

#endif /* USER_CONFIG_H_ */