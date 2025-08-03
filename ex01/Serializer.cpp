#include "Serializer.h"
#include <cstddef>

uintptr_t Serializer::serialize(Data *ptr) {
    uintptr_t result = 0;
    if (ptr) {
        result = reinterpret_cast<uintptr_t>(ptr);
    }
    return result;
}

Data * Serializer::deserialize(uintptr_t raw) {
    Data * result = new Data();
    if (raw != 0) {
        const Data *tmp_result = reinterpret_cast<Data *>(raw);
        result->a = tmp_result->a;
        result->b = tmp_result->b ? new int(*tmp_result->b) : NULL;
    } else {
        result->a = 0;
        result->b = NULL;
    }
    return result;
}

Serializer::Serializer() {}

Serializer::~Serializer() {}

Serializer::Serializer(const Serializer& other) {
    (void)other;
}

Serializer& Serializer::operator=(const Serializer& other) {
    if (this != &other) {
    }
    return *this;
}
