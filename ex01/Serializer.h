#ifndef SERIALIZER_H
#define SERIALIZER_H

struct Data {
    char a;
    int *b;
};

#if defined(__x86_64__) || defined(_M_X64)
typedef unsigned long long uintptr_t;
#else
typedef unsigned long uintptr_t;
#endif

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
