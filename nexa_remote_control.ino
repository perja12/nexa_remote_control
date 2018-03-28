#include <NexaCtrl.h>
#include <avr/power.h>
#include <avr/sleep.h>

#define TX_PIN 0 // Same as PB0
#define RX_PIN 2 // Not used.

#define CMD_NONE 0
#define CMD_1    1
#define CMD_2    2
#define CMD_3    3
#define CMD_4    4

// Send commands to Nexa controller with 433 MHz RF module and
// ATtiny85 with minimal power consumption.
//
// A change interrupt wakes the mcu and checks which button that was
// pressed. There is no hardware for debouncing the buttons since we
// only process the first interrupt (by temporarily disabling
// interrupts) and uses delay(100) before enabling interrupts again.

// Pinout for ATtiny85:
// RESET PB5 (5/A0) *o**** VCC
//       PB3 (3/A3) ****** PB2 (2/A1)
//       PB4 (4/A2) ****** PB1 (1)
//              GND ****** PB0 (0)

// 26 bit controller id assigned to each Nexa device.
const static unsigned long CONTROLLER_ID = 9610883;

// 4 bit device id.
const static unsigned int DEVICE_1 = 0;
const static unsigned int DEVICE_2 = 1;

NexaCtrl nexaCtrl(TX_PIN, RX_PIN);

volatile int cmd = CMD_NONE;

ISR(PCINT0_vect) {
    cli();

    if (!bit_is_set(PINB, PB1)) {
        cmd = CMD_1;
    }
    if (!bit_is_set(PINB, PB2)) {
        cmd = CMD_2;
    }
    if (!bit_is_set(PINB, PB3)) {
        cmd = CMD_3;
    }
    if (!bit_is_set(PINB, PB4)) {
        cmd = CMD_4;
    }
}

void setup() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // Turn off ADC to save power.
    ADCSRA &= ~ bit(ADEN);

    pinMode(PB1, INPUT_PULLUP);
    pinMode(PB2, INPUT_PULLUP);
    pinMode(PB3, INPUT_PULLUP);
    pinMode(PB4, INPUT_PULLUP);

    // Configure pin change interrupt.
    PCMSK  |= _BV (PCINT1);
    PCMSK  |= _BV (PCINT2);
    PCMSK  |= _BV (PCINT3);
    PCMSK  |= _BV (PCINT4);
    GIFR   |= bit (PCIF);    // clear any outstanding interrupts
    GIMSK  |= bit (PCIE);    // enable pin change interrupts
}

void loop() {
    // Set TX_PIN to INPUT in order to save power.
    pinMode(TX_PIN, INPUT);

    // Enable interrupts again, go to sleep and wait for intterrupt.
    sei();
    go_to_sleep();

    // Wakes up here.
    pinMode(TX_PIN, OUTPUT);

    switch (cmd) {
    case CMD_1:
        nexaCtrl.DeviceOn(CONTROLLER_ID, DEVICE_1);
        break;
    case CMD_2:
        nexaCtrl.DeviceOff(CONTROLLER_ID, DEVICE_1);
        break;
    case CMD_3:
        nexaCtrl.DeviceOn(CONTROLLER_ID, DEVICE_2);
        break;
    case CMD_4:
        nexaCtrl.DeviceOff(CONTROLLER_ID, DEVICE_2);
        break;
    }
    cmd = CMD_NONE;

    // Avoid getting a new interrupt because of button bounce.
    delay(100);
}

void go_to_sleep() {
    power_all_disable();  // power off ADC, Timer 0 and 1, serial interface
    sleep_enable();
    sleep_cpu();
    sleep_disable();
    power_all_enable();   // power everything back on
}
