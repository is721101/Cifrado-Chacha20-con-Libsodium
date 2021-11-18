
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sodium.h>
#include <string>
#include <iostream>
#include <sstream> 



using namespace std;
string linea;
string texto;

int main()
{
//Abrir archivo
   ifstream archivo("Ruta del archivo");
    if (archivo.fail()) {
        cout << "Error al abrir este archivo" << endl;
        return -1;
    }
    //Guardamos el texto en un string
    while (getline(archivo, linea)) {
        texto = texto +linea;
    }

    archivo.close();

    //creamos el plain text
    const unsigned char* plaintext = reinterpret_cast<const unsigned char*> (texto.c_str());
    
        
    //Ciframos
    int plaintext_len = strlen((char*)plaintext);
    
    unsigned  char* ciphertext = new unsigned char[plaintext_len];
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    crypto_secretbox_keygen(key);
    randombytes_buf(nonce, sizeof nonce);
    int errocode= crypto_stream_chacha20_xor(ciphertext, plaintext,plaintext_len, nonce,key);

    //Guardar  cipher a  un stringstream
    std::stringstream buffer; 

    for (int i = 0; i < sizeof ciphertext; i++) {
            buffer << std::setfill('0') << std::setw(2) << std::hex << int(ciphertext[i]);	
    }

    //Escribir información en el archivo
    ofstream archivo2("Ruta del archivo");
    if (archivo2.fail()) {
        cout << "Error archivo no encontrado" << endl;
    }
     cout << "Archivo cifrado" << endl;
     archivo2 << buffer.str();
     archivo2.close();

     return 0;
}

