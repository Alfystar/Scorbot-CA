#ifndef CUSTOMCODEDEFINE_H
#define CUSTOMCODEDEFINE_H


// <== Code variant ==>
//#define DB_TERMINAL 1
//#define MOVE_CHECK 1            // At startup, move little bit all motors for test
#define MOTOR_LIMIT_ENABLE 1    // Enable the firmware motor limit

#define uartSpeed 115200 //921600

#ifdef DB_TERMINAL
#define Db Serial
#define DbVel uartSpeed
#define Cmd Serial1
#define CmdVel uartSpeed //921600

#else //Se non Voglio il debug Seriale, evito di definirla
#define Cmd Serial
#define CmdVel uartSpeed
#endif

// <== Debug #Define if "DB_TERMINAL" are enable ==>
#ifdef DB_TERMINAL
// <== HW lib Define ==>
//#define DB_PRINT_SENSOR 1 	        // Enable Terminal print of Sensor value
//#define EEPROM_DB 1               	// Enable EEPROM_DB
//#define MOTOR_DB 1                	// Enable MOTOR_DB
//#define ENCODER_DB 1              	// Enable ENCODER_DB
//#define ADC_DB 1              	  	// Enable ADC_DB

// <== Data Class Define ==>
//#define SERIAL_PACK_DB 1           	// Enable SERIAL_PACK_DB
//#define ALL_SENDOR_DB 1 			// Enable ALL_SENDOR_DB
//#define CURRENT_MOT_DB 1 			// Enable CURRENT_MOT_DB
//#define ENCODER_MOT_DB 1 			// Enable ENCODER_MOT_DB
//#define SETTING_CLASS_DB 1 			// Enable SETTING_CLASS_DB
//#define SPEED_MOT_DB 1				// Enable SPEED_MOT_DB

#ifdef ALL_SENDOR_DB
#define CURRENT_MOT_DB 1 			// MUST Enable CURRENT_MOT_DB
#define ENCODER_MOT_DB 1 			// MUST Enable ENCODER_MOT_DB
#endif

// <== Serial Beavour ==>
//#define DATA_SEND_DB 1				// Enable DATA_SEND_DB
#define HOME_DB	1				// Enable HOME_DB

#endif

#endif //CUSTOMCODEDEFINE_H
