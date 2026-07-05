#ifndef _CHEAT_H_
#define _CHEAT_H_

#include "service/tools/common_def.h"

// GPIO 引脚定义 — 输出给另一个项目读取
#define CHEAT_PIN_B0  1   // bit 0 (LSB)
#define CHEAT_PIN_B1  2   // bit 1

exit_code_t cheat_init(void);
void cheat_set_state(uint8_t state);
const char *cheat_state_name(uint8_t state);

#endif
