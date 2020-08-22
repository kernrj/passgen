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

#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include "pgrandom.h"
#include "strutil.h"

using namespace std;


static const char* lowerChars = "abcdefghijklmnopqrstuvwxyz";
static const char* upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char* numberChars = "0123456789";
static const char* allSpecialChars = "`~!@#$%^&*()_+-=[]\\{}|;':\",./<>?";

static const char* defaultChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*()_+-=[]\\{}|;':\",./<>?";

static void printUsage(const char* arg0){
    printf("Usage: %s [options]\n", arg0);
    printf("Specifying multiple options will add all character classes.\n");
    printf("Options:\n");
    printf("  --all            Use numbers, upper and lower case letters, and all special characters.\n");
    printf("  --length         Number of characters in the password.\n");
    printf("  --lower          Use lower-case ASCII letters.\n");
    printf("  --upper          Use upper-case ASCII letters.\n");
    printf("  --alpha          Use upper and lower-case ASCII letters.\n");
    printf("  --alphanumeric   Use numbers and both upper and lower-case ASCII letters.\n");
    printf("  --numeric        Use digits.\n");
    printf("  --special        Use special characters: %s\n", "`~!@#$%^&*()_+-=[]\\{}|;':\",./<>?");
    printf("  --extra CHARS    Uses the characters specified in CUSTOM_STRING\n");
    printf("  --max-repeat N   Maximum number of times a character that can repeat in the password. Default is -1 (No maximum).\n");
}

static void parseOpts(int argc,
                      char** argv,
                      vector<string>* useCharClassesOut,
                      uint64_t* passwdLenOut,
                      int* maxRepeatOut)
{
    uint64_t passwdLen = 25;
    vector<string> useCharClasses;
    int maxRepeat = -1;

    const char* extraChars = NULL;
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "--lower"))
            useCharClasses.push_back(lowerChars);
        else if(!strcmp(argv[i], "--length")){
            i++;
            if(i >= argc){
                fprintf(stderr, "Error: argument missing for --length\n");
                exit(1);
            }

            passwdLen = stoull(argv[i]);
        }
        else if(!strcmp(argv[i], "--max-repeat")){
            if(i == argc - 1){
                fprintf(stderr, "Error: argument missing for --max-repeat.\n");
                exit(1);
            }

            i++;
            size_t strIdx;
            string numStr = argv[i];
            maxRepeat = stoi(numStr, &strIdx, 0);
            if(strIdx != numStr.size()){
                fprintf(stderr, "Unable to parse --max-repeat argument '%s'.\n", numStr.c_str());
                exit(1);
            }

            if(maxRepeat <= 0)
                maxRepeat = -1;
        }
        else if(!strcmp(argv[i], "--upper"))
            useCharClasses.push_back(upperChars);
        else if(!strcmp(argv[i], "--numeric"))
            useCharClasses.push_back(numberChars);
        else if(!strcmp(argv[i], "--alpha")){
            useCharClasses.push_back(upperChars);
            useCharClasses.push_back(lowerChars);
        }
        else if(!strcmp(argv[i], "--alphanumeric")){
            useCharClasses.push_back(upperChars);
            useCharClasses.push_back(lowerChars);
            useCharClasses.push_back(numberChars);
        }
        else if(!strcmp(argv[i], "--all")){
            useCharClasses.push_back(upperChars);
            useCharClasses.push_back(lowerChars);
            useCharClasses.push_back(numberChars);
            useCharClasses.push_back(allSpecialChars);
        }
        else if(!strcmp(argv[i], "--extra")){
            if(i == argc - 1){
                fprintf(stderr, "Error: argument missing for --special.\n");
                exit(1);
            }

            i++;

            string newChars = argv[i];
            useCharClasses.push_back(newChars);
        }
        else{
            if(strcmp("--help", argv[i]) && strcmp("-h", argv[i]))
                fprintf(stderr, "Unrecognized option: \"%s\".\n", argv[i]);

            printUsage(argv[0]);

            exit(1);
        }
    }

    if(useCharClasses.size() == 0){
        useCharClasses.push_back(upperChars);
        useCharClasses.push_back(lowerChars);
        useCharClasses.push_back(numberChars);
        useCharClasses.push_back(allSpecialChars);
    }

    *useCharClassesOut = useCharClasses;
    *passwdLenOut = passwdLen;
    *maxRepeatOut = maxRepeat;
}

string randPass(const string& srcChars, size_t length, int maxRepeat){
    char* password = new char[length + 1];
    size_t useCharsLen = srcChars.size();
    size_t repeatCount = 1;
    char lastChar = 0;
    uint8_t idx;

    for(int i = 0; i < length; i++){
        pgrRand8(0, useCharsLen - 1, &idx);

        char ch = srcChars[idx];

        if(maxRepeat >= 0){
            if(ch == lastChar)
                repeatCount++;
            else
                repeatCount = 1;

            if(repeatCount > maxRepeat){
                repeatCount--;
                i--;
                continue;
            }

            lastChar = ch;
        }

        password[i] = ch;
    }

    password[length] = 0;
    string passStr = password;
    delete[] password;

    return passStr;
}

string makePassword(const vector<string>& charClasses,
                    size_t length,
                    int maxRepeat)
{
    string password;
    string useChars;

    for(int i = 0; i < charClasses.size(); i++)
        useChars = mergeChars(useChars, charClasses[i]);

    do{
        password = randPass(useChars, length, maxRepeat);
    }while(!hasAllClasses(password, charClasses));

    return password;
}

int main(int argc, char** argv){
    uint64_t length;
    vector<string> useCharClasses;
    int maxRepeat;
    parseOpts(argc, argv, &useCharClasses, &length, &maxRepeat);

    pgrInit();
    string password = makePassword(useCharClasses, length, maxRepeat);

    printf("%s\n", password.c_str());

    return 0;
}
