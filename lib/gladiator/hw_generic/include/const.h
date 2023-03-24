#define MOTOR_ENABLE      10

//encoders pins
#define RIGHT_ENCODER_1   45
#define RIGHT_ENCODER_2   48
#define LEFT_ENCODER_1    21
#define LEFT_ENCODER_2    47
//motor pins
#define LEFT_MOTOR_DIR_1  12
#define LEFT_MOTOR_DIR_2  11
#define LEFT_MOTOR_SPEED  0

#define RIGHT_MOTOR_DIR_1  13
#define RIGHT_MOTOR_DIR_2  14
#define RIGHT_MOTOR_SPEED  0

#define RIGHT_WHEEL_TPR 350
#define LEFT_WHEEL_TPR  350

#define LED_RED      41
#define LED_BLUE     40
#define LED_GREEN    39

#define SERVO_AUTOKILL  38

#define WEAPON_M1 37
#define WEAPON_M2 36
#define WEAPON_M3 35

#define ADC_VBAT 1

#define SERVO_ISR
#ifdef SERVO_ISR
    #define MIN_MICROS      250  //544
    #define MAX_MICROS      1150
#endif

#define ROBOT_CENTER_X 0
#define ROBOT_CENTER_Y 0.045

#define MODULES_LEN 14
#define MAZE_WIDTH 3
#define MODULE_WIDTH 0.214285714
#define ROBOT_RADIUS 0.06
#define MAZE_HEIGHT 3


#define REG_LENGTH 30
#define Q_V 1.22e-05
#define Q_W 1.36e-04
#define R_X 0.70e-06
#define R_Y 0.70e-06
#define R_A 0.012

#define WHEEL_RADIUS 0.0325//m
//#define WHEEL_TPR 700 //350 210 70 700
#define WHEEL_MAX_TICKS_PER_DT 1000
#define WHEEL_SATMAX 0.08
#define WHEEL_SATMIN 0.08

#define WHEEL_SAT 1

#define EEPROM_SIZE 75
#define MAC_MEM_ADDR 0

#define INT0_ADDR 6
#define INT1_ADDR 10
#define INT2_ADDR 14
#define INT3_ADDR 15

#define BYTE0_ADDR 16
#define BYTE1_ADDR 17
#define BYTE2_ADDR 18
#define BYTE3_ADDR 19

#define SHORT0_ADDR 20
#define SHORT1_ADDR 22
#define SHORT2_ADDR 24
#define SHORT3_ADDR 26

#define FLOAT0_ADDR 28
#define FLOAT1_ADDR 32
#define FLOAT2_ADDR 36
#define FLOAT3_ADDR 40

#define CHAR0_ADDR 44
#define CHAR1_ADDR 45
#define CHAR2_ADDR 46
#define CHAR3_ADDR 47

#define STR0_ADDR 48
#define STR0_LEN 20

#define ID_ADDR 70
#define LOOP_TIME 8000


