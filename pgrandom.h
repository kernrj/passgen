/* 
 * Copyright 2020 Rick Kern <kernrj@gmail.com>
 *
 * Passgen is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __PG_RANDOM_H__
#define __PG_RANDOM_H__

#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

int pgrInit();

int pgrRand8(uint8_t min, uint8_t max, uint8_t* randNumOut);
int pgrRand32(int min, int max, int* randNumOut);

void pgrCleanup();

#ifdef __cplusplus
} //extern "C"
#endif

#endif // __PG_RANDOM_H__
