// Copyright 2016 Pronina Maria
#include "include/RomanConverter.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
static const vector<int> kValues =
{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
static const vector<string> kSymbols =
{"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
static const int kMaxValue = 3999;

vector<string> RomanConverter::ParseRoman(const string& roman) {
    int state = 0;
    vector<string> result;
    for (size_t i = 0; i < roman.length(); ++i) {
        switch (state) {
        case 0: {
                if (i == roman.length() - 1) {
                    string tmp(1, roman[i]);
                    result.push_back(tmp);
                } else {
                    if (roman[i] == 'I') {
                        state = 1;
                    } else if (roman[i] == 'X') {
                        state = 2;
                    } else if (roman[i] == 'C') {
                        state = 3;
                    } else {
                        string tmp(1, roman[i]);
                        result.push_back(tmp);
                    }
                }
            }
            break;
        case 1: {
                if (roman[i] == 'V') {
                    result.push_back("IV");
                    state = 0;
                } else if (roman[i] == 'X') {
                    result.push_back("IX");
                    state = 0;
                } else {
                    result.push_back("I");
                    if (i != roman.length() - 1) {
                        if (roman[i] == 'I') {
                            state = 1;
                            continue;
                        }
                        if (roman[i] == 'C') {
                            state = 3;
                            continue;
                        }
                    }
                    string tmp(1, roman[i]);
                    result.push_back(tmp);
                    state = 0;
                }
            }
            break;
        case 2: {
                if (roman[i] == 'L') {
                    result.push_back("XL");
                    state = 0;
                } else if (roman[i] == 'C') {
                    result.push_back("XC");
                    state = 0;
                } else {
                    result.push_back("X");
                    if (i != roman.length() - 1) {
                        if (roman[i] == 'I') {
                            state = 1;
                            continue;
                        }
                        if (roman[i] == 'X') {
                            state = 2;
                            continue;
                        }
                    }
                    string tmp(1, roman[i]);
                    result.push_back(tmp);
                    state = 0;
                }
            }
            break;
        case 3: {
                if (roman[i] == 'D') {
                    result.push_back("CD");
                    state = 0;
                } else if (roman[i] == 'M') {
                    result.push_back("CM");
                    state = 0;
                } else {
                    result.push_back("C");
                    if (i != roman.length() - 1) {
                        if (roman[i] == 'I') {
                            state = 1;
                            continue;
                        }
                        if (roman[i] == 'X') {
                            state = 2;
                            continue;
                        }
                        if (roman[i] == 'C') {
                            state = 3;
                            continue;
                        }
                    }
                    string tmp(1, roman[i]);
                    result.push_back(tmp);
                    state = 0;
                }
            }
            break;
        }
    }
    return result;
}

bool RomanConverter::CheckNumeralsRepeats
                     (const vector<string>& parsed_roman) {
    auto repeated_symbol = parsed_roman.front();
    int repeat_count = 1;
    for (auto it = parsed_roman.begin() + 1; it != parsed_roman.end(); ++it) {
        if (*it == repeated_symbol) {
            repeat_count++;
        } else {
            repeated_symbol = *it;
            repeat_count = 1;
        }
        if (repeat_count > 3)
            return false;
    }
    return true;
}
bool RomanConverter::CheckForInvalidNumerals
                     (const vector<string>& parsed_roman) {
    auto prev = parsed_roman.front();
    int  index_of_cur_symbol;
    int index_of_prev_symbol = find(kSymbols.begin(), kSymbols.end(), prev)
        - kSymbols.begin();
    for (auto it = parsed_roman.begin()+1; it != parsed_roman.end(); ++it) {
        index_of_cur_symbol = find(kSymbols.begin(), kSymbols.end(), *it)
                              - kSymbols.begin();
        int sum = kValues[index_of_prev_symbol] + kValues[index_of_cur_symbol];
        auto val_it = kValues.begin();
        while ((*val_it <= sum) && (val_it != kValues.end()-1))
            ++val_it;
        if (sum == *val_it)
            return false;
        --val_it;
        if ((kValues[index_of_prev_symbol] < *val_it) &&
            (kValues[index_of_cur_symbol] < *val_it))
            return false;
        prev = *it;
        index_of_prev_symbol = index_of_cur_symbol;
    }
    return true;
}
bool RomanConverter::CheckNumeralsOrder
                     (const vector<string>& parsed_roman) {
    auto previous = parsed_roman.front();
    for (auto it = parsed_roman.begin() + 1; it != parsed_roman.end(); ++it) {
        auto previousPos = find(kSymbols.begin(), kSymbols.end(), previous);
        auto currentPos = find(kSymbols.begin(), kSymbols.end(), *it);
        if (currentPos > previousPos)
            return false;
        previous = *it;
    }
    return true;
}

bool RomanConverter::CheckForInvalidSymbols
                     (const vector<string>& parsed_roman) {
    for (auto it = parsed_roman.begin(); it != parsed_roman.end(); ++it) {
        auto position = find(kSymbols.begin(), kSymbols.end(), *it);
        if (position == kSymbols.end())
            return false;
    }
    return true;
}

bool RomanConverter::CheckArabicNumber(int arabic) {
    if ((arabic <= 0) || (arabic > kMaxValue))
        return false;
    return true;
}

bool RomanConverter::CheckRomanNumber(const string& roman) {
    if (roman.empty()) return false;
    vector<string> parsed_roman = ParseRoman(roman);
    if (!CheckForInvalidSymbols(parsed_roman)) return false;
    if (!CheckNumeralsRepeats(parsed_roman)) return false;
    if (!CheckNumeralsOrder(parsed_roman)) return false;
    if (!CheckForInvalidNumerals(parsed_roman)) return false;
    return true;
}

int RomanConverter::ConvertRomanToArabic(const string& roman) {
    if (!CheckRomanNumber(roman))
        throw std::invalid_argument
         ("Inputed string is not correct roman number");
    int result = 0;
    vector<string> parsedRoman = ParseRoman(roman);
    for (auto it = parsedRoman.begin(); it != parsedRoman.end(); ++it) {
        auto  index_of_symbol = find(kSymbols.begin(), kSymbols.end(), *it)
                                - kSymbols.begin();
        result += kValues[index_of_symbol];
    }
    return result;
}

string RomanConverter::ConvertArabicToRoman(int arabic) {
    if (!CheckArabicNumber(arabic))
        throw std::invalid_argument
        ("Inputed arabic number can not be converted");
    string result;
    for (size_t i = kValues.size(); i != 0; i--) {
        if (arabic <= 0) break;
        while (arabic >= kValues[i-1]) {
            result.append(kSymbols[i-1]);
            arabic -= kValues[i-1];
        }
    }

    return result;
}
