#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <map>
#include <string>

const std::map<std::string, std::vector<uint8_t>> font8x8 = {
  {" ", {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}, // SPACE
  {"!", {0x00,0x00,0x00,0x00,0x5F,0x00,0x00,0x00}}, // !
  {"\"",{0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x00}}, // "
  {"#", {0x00,0x24,0x7E,0x24,0x24,0x7E,0x24,0x00}}, // #
  {"$", {0x00,0x2E,0x2A,0x7F,0x2A,0x3A,0x00,0x00}}, // $
  {"%", {0x00,0x46,0x26,0x10,0x08,0x64,0x62,0x00}}, // %
  {"&", {0x00,0x20,0x54,0x4A,0x54,0x20,0x50,0x00}}, // &
  {"\'",{0x00,0x00,0x00,0x04,0x02,0x00,0x00,0x00}}, // '
  {"(", {0x00,0x00,0x00,0x3C,0x42,0x00,0x00,0x00}}, // (
  {")", {0x00,0x00,0x00,0x42,0x3C,0x00,0x00,0x00}}, // )
  {"*", {0x00,0x10,0x54,0x38,0x54,0x10,0x00,0x00}}, // *
  {"+", {0x00,0x10,0x10,0x7C,0x10,0x10,0x00,0x00}}, // +
  {",", {0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00}}, // ,
  {"-", {0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x00}}, // -
  {".", {0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00}}, // .
  {"/", {0x00,0x40,0x20,0x10,0x08,0x04,0x00,0x00}}, // /

  {"0", {0x3C,0x62,0x52,0x4A,0x46,0x3C,0x00,0x00}}, // 0
  {"1", {0x44,0x42,0x7E,0x40,0x40,0x00,0x00,0x00}}, // 1
  {"2", {0x64,0x52,0x52,0x52,0x52,0x4C,0x00,0x00}}, // 2
  {"3", {0x24,0x42,0x42,0x4A,0x4A,0x34,0x00,0x00}}, // 3
  {"4", {0x30,0x28,0x24,0x7E,0x20,0x20,0x00,0x00}}, // 4
  {"5", {0x2E,0x4A,0x4A,0x4A,0x4A,0x32,0x00,0x00}}, // 5
  {"6", {0x3C,0x4A,0x4A,0x4A,0x4A,0x30,0x00,0x00}}, // 6
  {"7", {0x02,0x02,0x62,0x12,0x0A,0x06,0x00,0x00}}, // 7
  {"8", {0x34,0x4A,0x4A,0x4A,0x4A,0x34,0x00,0x00}}, // 8
  {"9", {0x0C,0x52,0x52,0x52,0x52,0x3C,0x00,0x00}}, // 9
  {":", {0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00}}, // :
  {";", {0x00,0x00,0x80,0x64,0x00,0x00,0x00,0x00}}, // ;
  {"<", {0x00,0x00,0x10,0x28,0x44,0x00,0x00,0x00}}, // <
  {"=", {0x00,0x28,0x28,0x28,0x28,0x28,0x00,0x00}}, // =
  {">", {0x00,0x00,0x44,0x28,0x10,0x00,0x00,0x00}}, // >
  {"?", {0x00,0x04,0x02,0x02,0x52,0x0A,0x04,0x00}}, // ?

  {"@", {0x00,0x3C,0x42,0x5A,0x56,0x5A,0x1C,0x00}}, // @
  {"A", {0x7C,0x12,0x12,0x12,0x12,0x7C,0x00,0x00}}, // A
  {"B", {0x7E,0x4A,0x4A,0x4A,0x4A,0x34,0x00,0x00}}, // B
  {"C", {0x3C,0x42,0x42,0x42,0x42,0x24,0x00,0x00}}, // C
  {"D", {0x7E,0x42,0x42,0x42,0x24,0x18,0x00,0x00}}, // D
  {"E", {0x7E,0x4A,0x4A,0x4A,0x4A,0x42,0x00,0x00}}, // E
  {"F", {0x7E,0x0A,0x0A,0x0A,0x0A,0x02,0x00,0x00}}, // F
  {"G", {0x3C,0x42,0x42,0x52,0x52,0x34,0x00,0x00}}, // G
  {"H", {0x7E,0x08,0x08,0x08,0x08,0x7E,0x00,0x00}}, // H
  {"I", {0x00,0x42,0x42,0x7E,0x42,0x42,0x00,0x00}}, // I
  {"J", {0x30,0x40,0x40,0x40,0x40,0x3E,0x00,0x00}}, // J
  {"K", {0x7E,0x08,0x08,0x14,0x22,0x40,0x00,0x00}}, // K
  {"L", {0x7E,0x40,0x40,0x40,0x40,0x40,0x00,0x00}}, // L
  {"M", {0x7E,0x04,0x08,0x08,0x04,0x7E,0x00,0x00}}, // M
  {"N", {0x7E,0x04,0x08,0x10,0x20,0x7E,0x00,0x00}}, // N
  {"O", {0x3C,0x42,0x42,0x42,0x42,0x3C,0x00,0x00}}, // O

  {"P", {0x7E,0x12,0x12,0x12,0x12,0x0C,0x00,0x00}}, // P
  {"Q", {0x3C,0x42,0x52,0x62,0x42,0x3C,0x00,0x00}}, // Q
  {"R", {0x7E,0x12,0x12,0x12,0x32,0x4C,0x00,0x00}}, // R
  {"S", {0x24,0x4A,0x4A,0x4A,0x4A,0x30,0x00,0x00}}, // S
  {"T", {0x02,0x02,0x02,0x7E,0x02,0x02,0x02,0x00}}, // T
  {"U", {0x3E,0x40,0x40,0x40,0x40,0x3E,0x00,0x00}}, // U
  {"V", {0x1E,0x20,0x40,0x40,0x20,0x1E,0x00,0x00}}, // V
  {"W", {0x3E,0x40,0x20,0x20,0x40,0x3E,0x00,0x00}}, // W
  {"X", {0x42,0x24,0x18,0x18,0x24,0x42,0x00,0x00}}, // X
  {"Y", {0x02,0x04,0x08,0x70,0x08,0x04,0x02,0x00}}, // Y
  {"Z", {0x42,0x62,0x52,0x4A,0x46,0x42,0x00,0x00}}, // Z
  {"[", {0x00,0x00,0x7E,0x42,0x42,0x00,0x00,0x00}}, // [
  {"\\",{0x00,0x04,0x08,0x10,0x20,0x40,0x00,0x00}}, // backslash
  {"]", {0x00,0x00,0x42,0x42,0x7E,0x00,0x00,0x00}}, // ]
  {"^", {0x00,0x08,0x04,0x7E,0x04,0x08,0x00,0x00}}, // ^
  {"_", {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00}}, // _

  {"`", {0x3C,0x42,0x99,0xA5,0xA5,0x81,0x42,0x3C}}, // `
  {"a", {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00}}, // a
  {"b", {0x00,0x7E,0x48,0x48,0x48,0x30,0x00,0x00}}, // b
  {"c", {0x00,0x00,0x38,0x44,0x44,0x44,0x00,0x00}}, // c
  {"d", {0x00,0x30,0x48,0x48,0x48,0x7E,0x00,0x00}}, // d
  {"e", {0x00,0x38,0x54,0x54,0x54,0x48,0x00,0x00}}, // e
  {"f", {0x00,0x00,0x00,0x7C,0x0A,0x02,0x00,0x00}}, // f
  {"g", {0x00,0x18,0xA4,0xA4,0xA4,0xA4,0x7C,0x00}}, // g
  {"h", {0x00,0x7E,0x08,0x08,0x08,0x70,0x00,0x00}}, // h
  {"i", {0x00,0x00,0x00,0x48,0x7A,0x40,0x00,0x00}}, // i
  {"j", {0x00,0x00,0x40,0x80,0x80,0x7A,0x00,0x00}}, // j
  {"k", {0x00,0x7E,0x18,0x24,0x40,0x00,0x00,0x00}}, // k
  {"l", {0x00,0x00,0x00,0x3E,0x40,0x40,0x00,0x00}}, // l
  {"m", {0x00,0x7C,0x04,0x78,0x04,0x78,0x00,0x00}}, // m
  {"n", {0x00,0x7C,0x04,0x04,0x04,0x78,0x00,0x00}}, // n
  {"o", {0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x00}}, // o

  {"p", {0x00,0xFC,0x24,0x24,0x24,0x18,0x00,0x00}}, // p
  {"q", {0x00,0x18,0x24,0x24,0x24,0xFC,0x80,0x00}}, // q
  {"r", {0x00,0x00,0x78,0x04,0x04,0x04,0x00,0x00}}, // r
  {"s", {0x00,0x48,0x54,0x54,0x54,0x20,0x00,0x00}}, // s
  {"t", {0x00,0x00,0x04,0x3E,0x44,0x40,0x00,0x00}}, // t
  {"u", {0x00,0x3C,0x40,0x40,0x40,0x3C,0x00,0x00}}, // u
  {"v", {0x00,0x0C,0x30,0x40,0x30,0x0C,0x00,0x00}}, // v
  {"w", {0x00,0x3C,0x40,0x38,0x40,0x3C,0x00,0x00}}, // w
  {"x", {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00}}, // x
  {"y", {0x00,0x1C,0xA0,0xA0,0xA0,0x7C,0x00,0x00}}, // y
  {"z", {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00}}, // z
  {"{", {0x00,0x08,0x08,0x76,0x42,0x42,0x00,0x00}}, // {
  {"|", {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}}, // |
  {"}", {0x00,0x42,0x42,0x76,0x08,0x08,0x00,0x00}}, // }
  {"~", {0x00,0x00,0x04,0x02,0x04,0x02,0x00,0x00}}, // ~
  {"°", {0x60,0x90,0x90,0x60,0x00,0x00,0x00,0x00}} // degree
};

#endif