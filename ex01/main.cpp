#include "Serializer.h"
#include <iostream>

int main() {
    Data data;
    data.a = 'A';
    int value = 42;
    data.b = &value;

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized data to raw pointer: " << raw << std::endl;

    const Data *deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized data: a = " << deserializedData->a
            << ", b = " << (deserializedData->b ? *deserializedData->b : 0) << std::endl;
    delete deserializedData->b;
    delete deserializedData;
    return 0;
}
