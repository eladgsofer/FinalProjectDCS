/*
 * PIT.h
 *
 *  Created on: Sep 13, 2021
 *      Author: katri
 */

#ifndef PIT_H_
#define PIT_H_

#define MODULO_REG_15HZ 0x00186A00


void InitPIT();
void set_PIT_max_val(int ms);
void PIT_enable(int start);

#endif /* PIT_H_ */
