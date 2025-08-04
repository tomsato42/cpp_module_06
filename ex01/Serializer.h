#ifndef SERIALIZER_H
#define SERIALIZER_H

struct Data {
    char a;
    int *b;
};

typedef unsigned long uintptr_t;

class Serializer {
public:
    static uintptr_t serialize(Data *ptr);

    static Data *deserialize(uintptr_t raw);

private:
    Serializer();

    ~Serializer();

    Serializer(const Serializer &);

    Serializer &operator=(const Serializer &);
};

#endif // SERIALIZER_H
