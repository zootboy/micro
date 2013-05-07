/* nrf.h - nRF24L01 radio functions
 * 
 * Uses SPI for communications.
 */
#ifndef NRF_H
#define	NRF_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "VirtualSerial.h"

// Macro shortenings.
#define SPI_WRITE(data) SPDR = (data);delay_us(5);while(!(SPSR & (1<<SPIF))) delay_us(5)
#define SS_DOWN NRF_SS_PORT &= ~(1<<NRF_SS_PIN)
#define SS_UP   NRF_SS_PORT |= (1<<NRF_SS_PIN)
#define CE_UP   NRF_CE_PORT |= (1<<NRF_CE_PIN)
#define CE_DOWN NRF_CE_PORT &= ~(1<<NRF_CE_PIN)
#define GET_STATUS delay_us(1);SS_DOWN;SPI_WRITE(NOP); nrf_last_status = SPDR;SS_UP

// Pin defines for radio & SPI connections.
#define NRF_SS_DDR  DDRB
#define NRF_SS_PORT PORTB
#define NRF_SS_PIN  PB0
#define NRF_CE_DDR  DDRB
#define NRF_CE_PORT PORTB
#define NRF_CE_PIN  PB4
#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK  PB1

// Settings for SPI and nRF.
#define SPI_INTERRUPT    0 // Enable interrupt?
#define NRF_RATE         0 // [0]=1 Mbps or [1]=2 Mbps.
#define NRF_RX           0 // [0]=TX or [1]=RX.
#define NRF_POWER        3 // [0-3] TX power.
#define NRF_RXGAIN       1 // Enable high-gain RX?
#define NRF_INTERRUPTS   0b111 // RX_DR/TX_DS/MAX_RT mask [1]=don't fire IRQ.
#define NRF_CRCEN        1 // Enable CRC?
#define NRF_CRCTWO       0 // Two-byte CRC?
#define NRF_AUTOACK      1 // Enable auto-ack?
#define NRF_ADDRESS      0x11004422AA // 5-byte address.
#define NRF_CHANNEL      24 // [0-125] channel selection.
#define NRF_PAYLOADBYTES 2 // [0-32] bytes per packet.

// nRF commands.
#define R_REGISTER          0b00000000 // 5-bit register name as 5 LSBits.
#define W_REGISTER          0b00100000 // Ditto.
#define R_RX_PAYLOAD        0b01100001
#define W_TX_PAYLOAD        0b10100000
#define W_TX_PAYLOAD_NO_ACK 0b10110000 // Last 0 missing from datasheet. Check this?
#define FLUSH_TX            0b11100001
#define FLUSH_RX            0b11100010
#define REUSE_TX_PL         0b11100011
#define ACTIVATE            0b01010000
#define R_RX_PL_WID         0b01100000
#define W_ACK_PAYLOAD       0b10101000 // 3 LSBits are the ACK pipe number
#define NOP                 0b11111111 // No Operation _command_. Read ops do not need this as their data payload.

#define  NRG_CONFIG     0x00 // Config register.
#define MASK_RX_DR     6
#define MASK_TX_DS     5
#define MASK_MAX_RT    4
#define MASK_ALL       4
#define EN_CRC         3
#define CRCO           2
#define PWR_UP         1
#define PRIM_RX        0
#define  NRG_EN_AA      0x01 // Shockburst auto-ack register.
#define ENAA_P5        5
#define ENAA_P4        4
#define ENAA_P3        3
#define ENAA_P2        2
#define ENAA_P1        1
#define ENAA_P0        0
#define  NRG_EN_RXADDR  0x02 // Enabled RX addresses register.
#define ERX_P5         5
#define ERX_P4         4 
#define ERX_P3         3
#define ERX_P2         2
#define ERX_P1         1
#define ERX_P0         0
#define  NRG_SETUP_AW   0x03 // Set address widths register
#define AW1            1
#define AW0            0
#define AW             0
#define  NRG_SETUP_RETR 0x04 // Retransmission settings register.
#define ARD3           7
#define ARD2           6
#define ARD1           5
#define ARD0           4
#define ARD            4
#define ARC3           3
#define ARC2           2
#define ARC1           1
#define ARC0           0
#define ARC            0
#define  NRG_RF_CH      0x05 // RF channel register.
#define RF_CH6         6
#define RF_CH5         5
#define RF_CH4         4
#define RF_CH3         3
#define RF_CH2         2
#define RF_CH1         1
#define RF_CH0         0
#define RF_CH          0
#define  NRG_RF_SETUP   0x06 // RF setup register.
#define PLL_LOCK       4
#define RF_DR          3
#define RF_PWR1        2
#define RF_PWR0        1
#define RF_PWR         1
#define LNA_HCURR      0
#define  NRG_STATUS     0x07 // Status register. Spat out MISO during command byte input.
#define RX_DR          6
#define TX_DS          5
#define MAX_RT         4
#define RX_P_NO2       3
#define RX_P_NO1       2
#define RX_P_NO0       1
#define RX_P_NO        1
#define STATUS_TX_FULL        0
#define  NRG_OBSERVE_TX 0x08 // Transmit observe register.
#define PLOS_CNT3      7
#define PLOS_CNT2      6
#define PLOS_CNT1      5
#define PLOS_CNT0      4
#define PLOS_CNT       4
#define ARC_CNT3       3
#define ARC_CNT2       2
#define ARC_CNT1       1
#define ARC_CNT0       0
#define ARC_CNT        0
#define  NRG_CD         0x09 // Carrier detect register.
#define CD             0
#define  NRG_RX_ADDR_P0 0x0A // RX address registers.
#define  NRG_RX_ADDR_P1 0x0B
#define  NRG_RX_ADDR_P2 0x0C
#define  NRG_RX_ADDR_P3 0x0D
#define  NRG_RX_ADDR_P4 0x0E
#define  NRG_RX_ADDR_P5 0x0F
#define  NRG_TX_ADDR    0x10 // TX address register.
#define  NRG_RX_PW_P0   0x11 // RX payload pipe contents registers.
#define  NRG_RX_PW_P1   0x12
#define  NRG_RX_PW_P2   0x13
#define  NRG_RX_PW_P3   0x14
#define  NRG_RX_PW_P4   0x15
#define  NRG_RX_PW_P5   0x16
#define  NRG_FIFO_STATUS 0x17 // FIFO status register.
#define TX_REUSE       6
#define FIFO_TX_FULL   5
#define TX_EMPTY       4
#define RX_FULL        1
#define RX_EMPTY       0
#define  NRG_DYNPD      0x1C // Dynamic payload enable register.
#define DPL_P5         5
#define DPL_P4         4
#define DPL_P3         3
#define DPL_P2         2
#define DPL_P1         1
#define DPL_P0         0
#define  NRG_FEATURE    0x1D // Radio features enable register.
#define EN_DPL         2
#define EN_ACK_PAY     1
#define EN_DYN_ACK     0


// SPI settings required for proper operation.
#define NRF_SPCR (SPI_INTERRUPT<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<SPR0) // Interrupt, enable, LSB 1st, master mode, rising=sample, Fosc/16.

uint8_t spi_state;
uint8_t spi_command;
uint8_t spi_bytes_sent;
uint8_t nrf_last_status;

// Function prototypes.
void nrf_init(void);
void nrf_tx(uint16_t payload);
uint16_t nrf_rx(void);
void nrf_spillRegisters(void);

#endif	/* NRF_H */

