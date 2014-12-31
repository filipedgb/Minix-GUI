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
#define IO_BUF_PORT 0x60


/* The following block of defines comes from slide 21 */
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64

/* SERIAL PORT */

#define SERIAL1_IRQ 4
#define SERIAL2_IRQ 3

#define COM1_ADDR 0x3f8
#define COM2_ADDR 0x2f8


#define SP_RECEIVER_BUF 0
#define SP_TRANSMITTER 0
#define SP_INTERRUPT_ENABLE 1
#define SP_INTERRUPT_ID 2
#define SP_FIFO_CONTROL 2
#define SP_LINE_CONTROL 3
#define SP_LINE_STATUS 5
#define SP_DLL 0
#define SP_DLM 1
#define SER_TX_RDY BIT(5)
#define SER_RCV_RDY BIT(0)

#define BIT_RATE 115200

/* LAB4 */

#define MOUSE_IRQ 12
#define KBC_WRITE_COMMAND 0xD4
#define ENABLE_STREAM_MODE 0xEA
#define ENABLE_DATA_PACKETS 0xF4
#define STATUS_REQUEST 0xE9

/* RTC */

#define RTC_IRQ 8

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define SECONDS_ADDR 0
#define MINUTES_ADDR 2
#define HOURS_ADDR 4
#define DAY_ADDR 7
#define MONTH_ADDR 8
#define YEAR_ADDR 9

#define REG_B_PIE 6
#define REG_B_AIE 5
#define REG_B_UIE 4

#define REG_A_UIP 7

#define RTC_REG_A 10
#define RTC_REG_B 11
#define RTC_REG_C 12
#define RTC_REG_D 13

/*keyboard */

#define ESC_BREAK_CODE 0x81
#define ESC_MAKE_CODE 0x01
#define DELETE_MAKE_CODE 0x53

#define LEFT_ARROW_BREAK_CODE 0xCB
#define RIGHT_ARROW_BREAK_CODE 0xCD
#define UP_ARROW_BREAK_CODE 0xC8
#define DOWN_ARROW_BREAK_CODE 0xD0
#define ENTER_MAKE_CODE 0x1C
#define BACKSPACE_MAKE_CODE 0x0E

/* LAB 5 DEFINES */

#define VBE_GET_MODE 0x4F01


#endif
