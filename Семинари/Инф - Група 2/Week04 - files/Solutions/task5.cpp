#include <iostream>
#include <fstream>

struct Order 
{
    double netPrice;
    double vat;
    int customerID;
};

void writeOrders(const char* filename, const Order* orders, int size)
{
    std::ofstream out(filename, std::ios::binary);

    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(reinterpret_cast<const char*>(orders), size * sizeof(Order));
}

struct OrderInfo
{
    Order* orders;
    int size;
};

OrderInfo readOrders(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        return OrderInfo{nullptr, 0};

    int size;
    Order* orders;

    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    orders = new Order[size];
    in.read(reinterpret_cast<char*>(orders), size * sizeof(Order));

    OrderInfo result {orders, size};
    return result;

    // return OrderInfo{orders, size};
    // return {orders, size};
}


int main()
{
    /// ==================== Write to file ==================== 

    // Order orders[3] 
    // {
    //     {10,0.2,71},
    //     {20,0.2,72},
    //     {30,0.2,73},
    // };

    // writeOrders("storeOrders_task5.bin", orders, 3);

    
    /// ==================== Read from file ==================== 

    OrderInfo orders = readOrders("storeOrders_task5.bin");

    std::cout << orders.size << '\n';
    std::cout << orders.orders[0].customerID;

    delete[] orders.orders;
}