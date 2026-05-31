#ifndef MOTOR_H
#define MOTOR_H

#include "driver/ledc.h"
#include "service/tools/common_def.h"

#define MOTOR_PWM_FREQ_HZ      1000
#define MOTOR_PWM_RESOLUTION   LEDC_TIMER_10_BIT
#define MOTOR_PWM_MAX_DUTY     1023
#define MOTOR_LEDC_TIMER       LEDC_TIMER_0
#define MOTOR_LEDC_SPEED_MODE  LEDC_LOW_SPEED_MODE

typedef struct {
    int pwm_gpio;
    int dir_gpio;
    ledc_channel_t channel;
    bool dir_invert;
} motor_config_t;

exit_code_t motor_init(const motor_config_t *config);
exit_code_t motor_set_duty(ledc_channel_t channel, float duty);
float motor_get_duty(ledc_channel_t channel);
exit_code_t motor_stop(ledc_channel_t channel);

#endif
