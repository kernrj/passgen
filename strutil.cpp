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

#include "strutil.h"
#include <set>

using namespace std;

size_t maxCharRepeat(const string& srcChars){
    size_t maxRepeats = 0;
    char lastChar = 0;

    size_t currRepeats = 0;
    for(int i = 0; i < srcChars.size(); i++){
        if(srcChars[i] != lastChar)
            currRepeats = 0;
        else{
            currRepeats++;
            maxRepeats = max(currRepeats, maxRepeats);
        }

        lastChar = srcChars[i];
    }

    return maxRepeats;
}

bool hasAllClasses(const string& password, const vector<string>& classes){
    for(int i = 0; i < classes.size(); i++){
        const string& classStr = classes[i];

        if(!containsAny(password, classes[i]))
            return false;
    }

    return true;
}

bool containsAny(const string& str, const string& chars){
    for(int i = 0; i < chars.size(); i++){
        if(str.find(chars[i]))
            return true;
    }

    return false;
}

string mergeChars(const string& str1, const string& str2){
    set<char> chars;
    for(size_t i = 0; i < str1.size(); i++)
        chars.insert(str1[i]);

    for(size_t i = 0; i < str2.size(); i++)
        chars.insert(str2[i]);

    char* merged = new char[chars.size() + 1];

    size_t i = 0;
    for(char ch : chars){
        merged[i] = ch;
        i++;
    }

    merged[i] = 0;

    string mergedStr(merged);

    delete[] merged;

    return mergedStr;
}
