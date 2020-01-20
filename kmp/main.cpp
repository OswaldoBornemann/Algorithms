//
// Created by Peter on 2020.1.20
//

#include <cstring>
#include <cstdio>

// 该函数用于存储模式串（Pattern String）中每个字符对应指针j重定向的位置
// （也就是存储模式串的数组下标）
// Next函数版本一
void Next_1(char *T, int *next) {
    next[1] = 0;
    int j = 0; // 指向前缀的末位
    int i = 1; // 指向后缀的末位
    while ( i < strlen(T) ) {
        if ( j == 0 || T[i - 1] == T[j - 1] ) {
            i++;
            j++;
            // next[i] = j 代表T[i]之前的模式串子串中，
            // 有长度为j的相同前缀和后缀
            // 那么在i位置失配后，会在位置j重新开始匹配
            next[i] = j;
        }  else {
            // 那么如果在之前的i-1和j-1的位置没有找到匹配
            // 这就意味着我们在寻求最长公共的前缀和后缀这一个目标失败了
            // 那么次目标就是要么寻找次短的公共前缀和后缀
            // 因此会在前缀字串中进行递归
            // 要么就是找不到公共前缀后缀，那么就意味着j要回到最初的位置
            j = next[j];
            // 然后再次进入到while循环的if条件判断
        }
    }
}

// 该函数用于存储模式串（Pattern String）中每个字符对应指针j重定向的位置
// （也就是存储模式串的数组下标）
// 优化后的Next函数版本二
void Next_2(char *T, int *next) {
    next[1] = 0;
    int j = 0; // 指向前缀的末位
    int i = 1; // 指向后缀的末位
    while ( i < strlen(T) ) {
        if ( j == 0 || T[i - 1] == T[j - 1] ) {
            i++;
            j++;
            // next[i] = j 代表T[i]之前的模式串子串中，
            // 有长度为j的相同前缀和后缀
            // 那么在i位置失配后，会在位置j重新开始匹配
            next[i] = j;
        } else {
            // 那么如果在之前的i-1和j-1的位置没有匹配
            // 那就意味着我们在寻求最长公共的前缀和后缀这一目标失败了
            // 那么次目标就是要么寻找次短的公共前缀和后缀
            // 例如模式串DABCDDABD, ABECCABED
            // 因此会在前缀字串中进行递归
            // 因此就是找不到公共前缀后缀，那么就意味着j要回到最初的位置
            // 要么就是找到了次短的公共前缀后缀了
            j = next[j];
            // 然后再次进入到while循环的if条件判断
        }
    }
}

// KMP的时间复杂度为O(S + T)
int KMP(char *S, char *T) {
    int next[10];
    Next_2(T, next); // 根据模式串T， 初始化next数组
    int i = 1;
    int j = 1;
    while ( i <= strlen(S) && j <= strlen(T)) {
        // j == 0 代表模式串的第一个字符就和当前测试的字符不相等
        // S[i - 1] == T[j - 1]对应位置字符相等
        // 这两种情况下，指向当前测试的两个指针下标i和j都要向后移
        if ( j == 0 || S[i - 1] == T[j - 1]) {
            i++;
            j++;
        } else {
            // 如果测试的两个字符都不相等
            // i不动，j变为指向模式串的next[j]位置
            j = next[j];
        }
    }

    // 如果条件为真，说明匹配成功
    if ( j > strlen(T) ) {
        return i - strlen(T);
    }

    return -1;
}

int main() {
    int i = KMP((char*)"ababcabcacbab", (char*)"abcac");
    printf("%d", i);
    return 0;
}
