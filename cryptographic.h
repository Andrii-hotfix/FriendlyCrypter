#ifndef CRYPTOGRAPHIC_H
#define CRYPTOGRAPHIC_H

#include <QCryptographicHash>
#include <QString>

// salt token length
#define SALT_LENGTH 8
// '!' ... 'z' - symbols to generate salt
#define ALPHABET_LENGTH 89
// '!' is the first symbol in alphabet
#define FIRST_ALPHA '!'

class CryptographicHash : public QCryptographicHash
{
public:
    CryptographicHash(Algorithm);

    QString generate_salt();
};

#endif // CRYPTOGRAPHIC_H
