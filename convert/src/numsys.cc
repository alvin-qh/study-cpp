#include <cstddef>
#include <math.h>

#include "numsys.h"

namespace convert {

    /// @brief 交换两个变量
    ///
    /// @tparam T
    /// @param left 待交换的变量
    /// @param right 待交换的变量
    template<typename T>
    inline void __swap(T* left, T* right) {
        T temp = *left;
        *left = *right;
        *right = temp;
    }

    /// @brief 将字符串进行反转
    ///
    /// @param s 字符串指针
    /// @param len 字符串长度
    void __revert_str(char* s, size_t len) {
        char* ps = s;
        char* pe = s + len - 1;

        // 从字符串头尾两边开始交换
        while (ps < pe) {
            __swap(ps, pe);
            ps++;
            pe--;
        }
    }

    int to_bin(int num, char* buf, size_t buflen) {
        if (--buflen < 1) {
            return ERR_BUF_NOT_ENOUGH;
        }

        bool ne = num >= 0;
        num = abs(num);

        size_t pos = 0;
        while (num > 0 && pos < buflen) {
            int lo = num % 2;
            buf[pos++] = lo + '0';
            num /= 2;
        }

        if (pos == buflen) {
            return ERR_BUF_NOT_ENOUGH;
        }

        if (pos == 0) {
            buf[pos++] = '0';
        }

        if (!ne) {
            if (pos + 1 == buflen) {
                return ERR_BUF_NOT_ENOUGH;
            }
            buf[pos++] = '-';
        }

        __revert_str(buf, pos);
        buf[pos] = '\0';

        return 0;
    }

    const char HEX_TAB[] = {
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E',
        'F',
    };

    int to_hex(int num, char* buf, size_t buflen) {
        if (--buflen < 1) {
            return ERR_BUF_NOT_ENOUGH;
        }

        bool ne = num >= 0;
        num = abs(num);

        size_t pos = 0;

        while (num > 0 && pos < buflen) {
            int lo = num % 16;
            buf[pos++] = HEX_TAB[lo];
            num /= 16;
        }

        if (pos == buflen) {
            return ERR_BUF_NOT_ENOUGH;
        }

        if (pos == 0) {
            buf[pos++] = '0';
        }

        if (!ne) {
            if (pos + 1 == buflen) {
                return ERR_BUF_NOT_ENOUGH;
            }
            buf[pos++] = '-';
        }

        __revert_str(buf, pos);
        buf[pos] = '\0';

        return 0;
    }

    int to_excel_column(int num, char* buf, size_t buflen) {
        if (num < 0) {
            return ERR_NUM_CANNOT_NEGATIVE;
        }

        num += 1;
        size_t pos = 0;

        while (num > 0 && pos < buflen) {
            int lo = (num - 1) % 26;
            buf[pos++] = lo + 65;
            num = (num - lo) / 26;
        }

        if (pos == buflen) {
            return ERR_BUF_NOT_ENOUGH;
        }

        __revert_str(buf, pos);
        buf[pos] = '\0';

        return 0;
    }

} // namespace convert
