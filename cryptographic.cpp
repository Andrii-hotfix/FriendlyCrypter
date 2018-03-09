#include "cryptographic.h"
#include <random>
#include <cstdlib>
#include <ctime>

CryptographicHash::CryptographicHash(Algorithm method) :
    QCryptographicHash(method) {}

QString CryptographicHash::generateSalt()
{
    srand(time(nullptr));
    QString salt = "";
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt += (rand() % ALPHABET_LENGTH) + FIRST_ALPHA;
    }
    return salt;
}
