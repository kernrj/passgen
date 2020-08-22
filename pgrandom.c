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

#include "pgrandom.h"
#include <errno.h>
#include <stdio.h>

FILE* urandomFile = NULL;

int pgrInit(){
    if(urandomFile)
        return 0;

    urandomFile = fopen("/dev/urandom", "rb");
    if(!urandomFile){
        fprintf(stderr, "Unable to open /dev/urandom\n");
        return errno;
    }
}

int pgrRand32(int min, int max, int* randNumOut){
    int span = max - min + 1;
    int excludeAbove = span == 0 ?
                           INT32_MAX :
                           INT32_MAX - (INT32_MAX % span);

    int out;
    do{
        size_t readBytes = fread(&out, sizeof(int), 1, urandomFile);
        if(readBytes != sizeof(int)){
            fprintf(stderr, "Error reading from /dev/urandom\n");
            return -1;
        }
    }while(out > excludeAbove);

    *randNumOut = out + min;
    return 0;
}

int pgrRand8(uint8_t min, uint8_t max, uint8_t* randNumOut){
    int span = (int)max - min + 1;
    int excludeAbove = span == 0 ?
                           UINT8_MAX :
                           UINT8_MAX - (UINT8_MAX % span);

    int out;
    do{
        out = getc(urandomFile);
        if(out < 0){
            fprintf(stderr, "Error reading from /dev/urandom\n");
            return -1;
        }
    }while(out > excludeAbove);

    out %= span;
    *randNumOut = (uint8_t)out + min;

    return 0;
}

void pgrCleanup(){
    if(urandomFile)
        fclose(urandomFile);

    urandomFile = NULL;
}
