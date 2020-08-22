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

#ifndef __PG_STR_UTIL_H__
#define __PG_STR_UTIL_H__

#include <string>
#include <vector>

size_t maxCharRepeat(const std::string& srcChars);
bool hasAllClasses(const std::string& searchInStr, const std::vector<std::string>& charClasses);
bool containsAny(const std::string& str, const std::string& chars);
std::string mergeChars(const std::string& str1, const std::string& str2);

#endif // __PG_STR_UTIL_H__
