#ifndef HEADERS_H_
#define HEADERS_H_

#define BIT(n) (0x01<<(n))

#define DELAY_US    20000

/* The following block of defines comes from slide 16 http://web.fe.up.pt/~pfs/aulas/lcom2014/at/5kbrd.pdf */
#define OBF BIT(0)
#define IBF BIT(1)
#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)


#define KBC_IRQ 1
#define OUT_BUF 0x60
#define IN_BUF 0x64

/* The following block of defines comes from slide 21 */
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64


#define ESC_BREAK_CODE 0x81
#define ESC_MAKE_CODE 0x01




#endif
