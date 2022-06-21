#include "RC4.h"
using namespace std;

int main(){//демонстрация алгоритма RC4 c замерами времени
    srand(time(0));//инициализация рандомайзера
    long long sizeFile = getSizeFile((char*)"sample.pdf");//узнаем размер файла в байтах
    if(sizeFile==-1){
        cout<<"Error!"<<endl;
        return -1;
    }
    cout<<"Size of file: "<<sizeFile<<" bytes"<<endl;
    generateKey((char*)"key.bin", 256);//генерируем 256 байтный ключ
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    bool resOperation = RC4Cipher((char*)"sample.pdf", (char*)"res.pdf", (char*)"key.bin");//само шифрование
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    if(resOperation)
        cout << "Time of encryption: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
    else{
        cout<<"Error!"<<endl;
        return -1;
    }
    begin = chrono::steady_clock::now();
    resOperation=RC4Cipher((char*)"res.pdf", (char*)"deciph_sample.pdf", (char*)"key.bin");//дешифрование использует тот же алгоритм и ключ
    end = chrono::steady_clock::now();
    if(resOperation)
        cout << "Time of decryption: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
    else{
        cout<<"Error!"<<endl;
        return -1;
    }
    return 0;
}

