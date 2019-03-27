/*
 * L298N.h - Library for L298N motor driver
 Created by Yohendry Hurtado, 28 dec 2014
 Released into the public domain.

 Created on: 25 mar 2019
 *      Author: Yohendry Hurtado, ADAPTION FOR PROJECT BY ALFY
 */
#include "L298N.h"

L298N::L298N(byte ena, byte in1, byte in2) {
	pinMode(ena, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

	this->knowHome=false;

	this->in1 = in1;
	this->in2 = in2;
	this->pwm = ena;

	this->state = free_Mot;
	this->delay_time = 0;
	this->time = 0;
	this->speed = 0;
}

void L298N::updateMot() {
	//enum {moving, H_brake, S_brake, wait};
	switch (this->state) {
	case moving:
		//do notting
		break;
	case movingTiming:
		if (millis() > this->time + this->delay_time)
			this->hard_stop(100);
		break;
	case H_brake:
		if (millis() > this->time + this->delay_time)
			this->soft_stop(1000);
		break;
	case S_brake:
		if (millis() > this->time + this->delay_time)
			this->freeRun();
		break;
	case alwaisBrake:
		break;
	case free_Mot:
	default:
		break;
	}
}
/*
bool L298N::goHome(funcBool_t f )
{

}
*/


void L298N::drive_motor(int speed) {
	this->speed = speed;
	this->state = moving;
	if (speed < 0) {
		this->anticlockwise();
		analogWrite(this->pwm, -this->speed);
	} else {
		this->clockWise();
		analogWrite(this->pwm, this->speed);
	}
}

void L298N::drive_motor(int speed, unsigned int delay_time) {
	this->drive_motor(speed);

	this->delay_time = delay_time;
	this->time = millis();
	this->state = movingTiming;
}

void L298N::hard_stop(unsigned int delay_time) {
	this->delay_time = delay_time;
	this->time = millis();
	this->state = H_brake;

	this->setup_motor(HIGH, HIGH);
	digitalWrite(this->pwm, 1);
}

void L298N::soft_stop() {
	this->state = alwaisBrake;
	this->setup_motor(LOW, LOW);
	digitalWrite(this->pwm, 1);
}

void L298N::soft_stop(unsigned int delay_time) {
	this->soft_stop();
	this->delay_time = delay_time;
	this->time = millis();
	this->state = S_brake;

}

void L298N::freeRun() {
	this->state = free_Mot;
	this->setup_motor(LOW, LOW);
	digitalWrite(this->pwm, 0);
}

void L298N::setup_motor(int state1, int state2) {
	digitalWrite(this->in1, state1);
	digitalWrite(this->in2, state2);
}

void L298N::clockWise() {
	this->setup_motor(1, 0);
}

void L298N::anticlockwise() {
	this->setup_motor(0, 1);
}

/*per futuro upgrade a porte*/
void set_bits_func_correct(volatile uint8_t *port, uint8_t mask) {
	*port |= mask;
}

