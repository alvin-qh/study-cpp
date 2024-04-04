#include "numsys.h"

#include <cstddef>
#include <math.h>

/**
 * 将字符串进行反转
 *
 * Args:
 *  - `s` 字符串指针
 *  - `len` 字符串指针
 */
void _revert_str(char *s, size_t len) {
    char *ps = s;
    char *pe = s + len - 1;

    // 从字符串头尾两边开始交换
    while (ps < pe) {
        char c = *ps;
        *ps    = *pe;
        *pe    = c;

        ps++;
        pe--;
    }
}

int to_bin(int num, char *buf, size_t buflen) {
    if (--buflen < 1) { return ERR_BUF_NOT_ENOUGH; }

    bool ne = num >= 0;
    num     = abs(num);

    size_t pos = 0;
    while (num > 0 && pos < buflen) {
        int lo      = num % 2;
        buf[pos++]  = lo + '0';
        num        /= 2;
    }

    if (pos == buflen) { return ERR_BUF_NOT_ENOUGH; }

    if (pos == 0) { buf[pos++] = '0'; }

    if (!ne) {
        if (pos + 1 == buflen) { return ERR_BUF_NOT_ENOUGH; }
        buf[pos++] = '-';
    }

    _revert_str(buf, pos);
    buf[pos] = '\0';

    return 0;
}

char HEX_TAB[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
};

int to_hex(int num, char *buf, size_t buflen) {
    if (--buflen < 1) { return ERR_BUF_NOT_ENOUGH; }

    bool ne = num >= 0;
    num     = abs(num);

    size_t pos = 0;

    while (num > 0 && pos < buflen) {
        int lo      = num % 16;
        buf[pos++]  = HEX_TAB[lo];
        num        /= 16;
    }

    if (pos == buflen) { return ERR_BUF_NOT_ENOUGH; }

    if (pos == 0) { buf[pos++] = '0'; }

    if (!ne) {
        if (pos + 1 == buflen) { return ERR_BUF_NOT_ENOUGH; }
        buf[pos++] = '-';
    }

    _revert_str(buf, pos);
    buf[pos] = '\0';

    return 0;
}

int to_excel_column(int num, char *buf, size_t buflen) {
    if (num < 0) { return ERR_NUM_CANNOT_NEGATIVE; }

    num += 1;

    size_t pos = 0;

    while (num > 0 && pos < buflen) {
        int lo     = (num - 1) % 26;
        buf[pos++] = lo + 65;
        num        = (num - lo) / 26;
    }

    if (pos == buflen) { return ERR_BUF_NOT_ENOUGH; }

    _revert_str(buf, pos);
    buf[pos] = '\0';

    return 0;
}
