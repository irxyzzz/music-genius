#include "staffdao.h"

StaffDao::StaffDao()
{
}
int StaffDao::pitchDao(int pitch)
{
    if(pitch<19) {
        return -6;
    } else if(pitch>18 && pitch<48) {
        switch(pitch) {
        case 19: return -6;
        case 20: return -6;
        case 21: return -5;
        case 22: return -5;
        case 23: return -4;
        case 24: return -3;
        case 25: return -3;
        case 26: return -2;
        case 27: return -2;
        case 28: return -1;
        case 29: return 0;
        case 30: return 0;
        case 31: return 1;
        case 32: return 1;
        case 33: return 2;
        case 34: return 2;
        case 35: return 3;
        case 36: return 4;
        case 37: return 4;
        case 38: return 5;
        case 39: return 5;
        case 40: return 6;
        case 41: return 7;
        case 42: return 7;
        case 43: return 8;
        case 44: return 8;
        case 45: return 9;
        case 46: return 9;
        case 47: return 10;
        }
    } else if(pitch>47 && pitch<76) {
        switch(pitch) {
        case 48: return -1;
        case 49: return -1;
        case 50: return 0;
        case 51: return 0;
        case 52: return 1;
        case 53: return 2;
        case 54: return 2;
        case 55: return 3;
        case 56: return 3;
        case 57: return 4;
        case 58: return 4;
        case 59: return 5;
        case 60: return 6;
        case 61: return 6;
        case 62: return 7;
        case 63: return 7;
        case 64: return 8;
        case 65: return 9;
        case 66: return 9;
        case 67: return 10;
        case 68: return 10;
        case 69: return 11;
        case 70: return 11;
        case 71: return 12;
        case 72: return 13;
        case 73: return 13;
        case 74: return 14;
        case 75: return 14;
        }
    } else {
        return 14;
    }
}

int StaffDao::durationDao(int duration)
{
    switch(duration) {
    case 3:  return 32;
    case 6:  return 16;
    case 12: return 8;
    case 24: return 4;
    case 48: return 2;
    case 96: return 1;
    }
}

int StaffDao::keyDao(int key)
{
    switch(key) {
    case 0:
        return 0;
    case 1:
        return -5;
    case 2:
        return 2;
    case 3:
        return -3;
    case 4:
        return 4;
    case 5:
        return -1;
    case 6:
        return 6;
    case 7:
        return 1;
    case 8:
        return -4;
    case 9:
        return 3;
    case 10:
        return -2;
    case 11:
        return 5;
    }
}
