#ifndef RC4_h
#define RC4_h
#include <iostream>
#include <fstream>
#include <chrono>//замеры времени исполнения куска кода
#include <vector>
//прототипы используемых в программе функций
long long getSizeFile(char*filename);//получение размера файла (в байтах)
bool RC4Cipher(char*filename1,char*filename2,char*key);//само шифрование
void printBinaryFile(char*filename);//печать бинарного файла в виде нулей и единиц (поможет для отладки)
void generateKey(char*filename, long long size);//генерация случайного ключа заданной длины
#endif
