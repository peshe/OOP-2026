#include <iostream>
#include <fstream>
#include <cstring>

struct Customer
{
    char* name;
    int id;
    int age;
};

struct Order 
{
    double netPrice;
    double vat;
    Customer customer;
};

struct OrderInfo
{
    Order* orders;
    int size;
};

void writeOrders(const char* filename, const Order* orders, int size)
{
    std::ofstream out(filename, std::ios::binary);

    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (int i = 0; i < size; i++)
    {
        // order[i]
        /// .netPrice
        out.write(reinterpret_cast<const char*>(&orders[i].netPrice), sizeof(orders[i].netPrice));
        /// .vat
        out.write(reinterpret_cast<const char*>(&orders[i].vat), sizeof(orders[i].vat));

        // order[i].customer
        /// .name
        int nameLength = std::strlen(orders[i].customer.name);
        out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        out.write(orders[i].customer.name, nameLength * sizeof(char));

        /// .id
        out.write(reinterpret_cast<const char*>(&orders[i].customer.id), sizeof(orders[i].customer.id));
        
        /// .age
        out.write(reinterpret_cast<const char*>(&orders[i].customer.age), sizeof(orders[i].customer.age));
    }
}


OrderInfo readOrders(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        return OrderInfo{nullptr, 0};

    int size;
    Order* orders;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    orders = new Order[size];

    for (int i = 0; i < size; i++)
    {
        // order
        // .netPrice
        in.read(reinterpret_cast<char*>(&orders[i].netPrice), sizeof(orders[i].netPrice));
        // .vat
        in.read(reinterpret_cast<char*>(&orders[i].vat), sizeof(orders[i].vat));

        // order[i].customer
        // .name
        int nameLength;
        in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        orders[i].customer.name = new char[nameLength + 1] {};
        in.read(orders[i].customer.name, nameLength * sizeof(char));
        // if there's no {} on line 77, then ->
        // orders[i].customer.name[nameLength] = '\0';

        // .id
        in.read(reinterpret_cast<char*>(&orders[i].customer.id), sizeof(orders[i].customer.id));
        
        // .age
        in.read(reinterpret_cast<char*>(&orders[i].customer.age), sizeof(orders[i].customer.age));
    }

    OrderInfo result {orders, size};
    return result;

    // return {orders, size};
}

char* createString(const char* str)
{
    char* result = new char[std::strlen(str) + 1] {}; // {} to fill everything with 0
    std::strcpy(result, str);
    return result;

    // or we could use a trick,
    // since strcpy return a pointer to the destination, we can use it like that ->
    //
    // return std::strcpy(new char[std::strlen(str) + 1] {}, str);
}

int main()
{
    /// ==================== Write to file ==================== 

    // Order orders[3]
    // {
    //     Order{10, 0.2, Customer{createString("Ivan"), 888, 20}},
    //     Order{30, 0.2, Customer{createString("Dragan"), 889, 21}},
    //     Order{60, 0.2, Customer{createString("Petkan"), 890, 22}},
    // };

    // writeOrders("storeOrders_task6.bin", orders, 3);

    // // don't forget to free the memory :)
    // for (int i = 0; i < 3; i++)
    // {
    //     delete[] orders[i].customer.name; 
    // }


    /// ==================== Read from file ==================== 

    OrderInfo info = readOrders("storeOrders_task5.bin");
    std::cout << info.size << '\n';

    for (int i = 0; i < info.size; i++)
    {
        std::cout << info.orders[i].customer.name << " #" << info.orders[i].customer.id << ": "
                  << info.orders[i].netPrice << " + vat(" << info.orders[i].vat * 100 << "%)\n"; 
    }


    for (int i = 0; i < info.size; i++)
    {
        delete[] info.orders[i].customer.name;
    }

    return 0;

}
