#include "RC4.h"
using namespace std;
bool RC4Cipher(char*filename1,char*filename2,char*key){//RC4 - поточный шифр
    //алгоритм состоит из двух частей: формирование s-блока и генерация псевдослучайного байта на каждый байт текста
    ifstream file(filename1, ios::binary|ios::in);//файл-исходник
    ofstream cipherfile(filename2,ios::binary|ios::out);//файл с шифротекстом
    ifstream keyfile(key, ios::binary|ios::in);//файл с ключом
    if((!file.is_open())||(!cipherfile.is_open())||(!keyfile.is_open()))
        return false;
    long long keyLenght = getSizeFile(key);//узнаем размер исходного файла
    vector<short>s(256);//s-блок, который помогает шифровать исходные данные
    //инициализация s-блока
    for(int i=0; i<256;i++){
        s[i]=i;
    }
    int i, j=0;
    vector<short>keyarr(256);//массив с байтами ключа для удобства
    short keybyte;//очередной байт из ключевого файла
    int ind=0;
    while(keyfile.read((char *)&keybyte,sizeof(short))&&ind<256){
        keyarr[ind++]=keybyte;//переносим байты из ключевого файла в массив
    }
    for(i=0;i<256;i++)//"тасовка" s-блока как часть его дальнейшей инициализации
    {
    j=(j + s[i] + keyarr[i%(int)(keyLenght)]) % 256;//индекс байта для тасовки
        swap(s[i],s[j]);//меняем местами элементы с i-тым и j-тым индексом
    }
    i=j=0;
    //вторая часть алгоритма связана непосредственно с кодированием, на каждый байт текста генерируем псведослучайное слово (байт)
    short byte;
    while(file.read((char *)&byte,sizeof(short))){
        i = ( i + 1 ) % 256;//делим индексы на длину s-блока, чтобы не выходить за пределы массива
        j = ( j + s[i] ) % 256;
        swap(s[i],s[j]);//меняем местами (тасуем) элементы s-блока
        short t = ( s[i] + s[j] ) % 256;//получаем по алгоритму rc4 номер байта в s-блоке - псевдослучайное слово для кодировки текущего байта
        short k = s[t];
        short resbyte = (byte^k);//xor'им байт текста и взятый из s-блока байт
        cipherfile.write((char *)&resbyte, sizeof(short));//записываем результат в шифротекст
    }//на очередную итерацию массива проделываем тасовку s-блока снова, таким образом, уменьшаем возможность найти закономерности для криптоаналитика
    file.close();
    cipherfile.close();
    keyfile.close();
    return true;
}
long long getSizeFile(char*filename){//функция для выяснения размера в байтах
    ifstream file(filename, ios::binary);
    file.seekg(0,file.end);//перемещаем файловый указатель в конец файла
    long long res = file.tellg();//узнаем размер
    file.seekg(0,file.beg);//снова возвращаемся  в начало
    file.close();
    return res;
}
void printBinaryFile(char*filename){//печать бинарного файла в виде последовательности битов
    ifstream file(filename, ios::binary);
    short byte;
    while(file.read((char *)&byte,sizeof(short))){
        cout<<bitset<8>(byte)<<" ";
    }
    file.close();
}
void generateKey(char*filename, long long size){//генерация случайного набора байт ключа заданной длины
    ofstream keyfile(filename,ios::binary|ios::out);
    while(size>0){
        short byte = rand()%256;
        keyfile.write((char *)&byte, sizeof(short));
        size--;
    }
    keyfile.close();
}

