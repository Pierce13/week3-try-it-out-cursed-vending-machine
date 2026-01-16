#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    const double CHIPS_PRICE = 1.25;
    const double SODA_PRICE = 1.00;
    const double CANDY_PRICE = 0.75;

    int choice = 0;
    int sodaStreak = 0;
    bool sodaBroken = false;

    std::cout << std::fixed << std::setprecision(2);

    while (true)
    {
        std::cout << "\n--- VENDING MACHINE ---\n";
        std::cout << "1. Chips  ($1.25)\n";
        std::cout << "2. Soda   ($1.00)";
        if (sodaBroken)
            std::cout << "  [OUT OF ORDER]";
        std::cout << "\n";
        std::cout << "3. Candy  ($0.75)\n";
        std::cout << "4. Quit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        if (choice == 4)
        {
            std::cout << "Goodbye!\n";
            break;
        }

        double price = 0.0;

        if (choice == 1)
        {
            price = CHIPS_PRICE;
            sodaStreak = 0;
        }
        else if (choice == 2)
        {
            if (sodaBroken)
            {
                std::cout << "ERROR: Soda button is broken.\n";
                continue;
            }

            sodaStreak++;
            if (sodaStreak == 3)
            {
                sodaBroken = true;
                std::cout << "Soda button has broken from overuse!\n";
                continue;
            }

            price = SODA_PRICE;
        }
        else if (choice == 3)
        {
            price = CANDY_PRICE;
            sodaStreak = 0;
        }
        else
        {
            std::cout << "Invalid selection.\n";
            continue;
        }

        double totalInserted = 0.0;

        while (totalInserted < price)
        {
            double coin;
            std::cout << "Insert coin (0 to cancel): ";
            std::cin >> coin;

            if (coin == 0.0)
            {
                std::cout << "Transaction canceled. Refunding $" << totalInserted << std::endl;
                totalInserted = 0.0;
                break;
            }

            if (coin == 0.05 || coin == 0.10 || coin == 0.25 || coin == 1.00)
            {
                totalInserted += coin;
                std::cout << "Total inserted: $" << totalInserted << std::endl;
            }
            else
            {
                std::cout << "Invalid coin.\n";
            }
        }

        if (totalInserted == 0.0)
            continue;

        int cents = static_cast<int>(totalInserted * 100 + 0.5);
        if (cents % 100 == 30 || cents % 100 == 80)
        {
            std::cout << "Coin sensor error. Transaction canceled.\n";
            std::cout << "Refunding $" << totalInserted << std::endl;
            continue;
        }

        if (totalInserted == price)
        {
            int jam = rand() % 2;
            if (jam == 0)
            {
                std::cout << "Machine jammed! Money lost.\n";
                continue;
            }
        }

        if (totalInserted > price)
        {
            double change = totalInserted - price;
            std::cout << "Returning change: $" << change << std::endl;

            while (change >= 0.25 - 0.001)
            {
                std::cout << "Returning $0.25\n";
                change -= 0.25;
            }
            while (change >= 0.10 - 0.001)
            {
                std::cout << "Returning $0.10\n";
                change -= 0.10;
            }
            while (change >= 0.05 - 0.001)
            {
                std::cout << "Returning $0.05\n";
                change -= 0.05;
            }
        }

        std::cout << "Dispensing item. Enjoy!\n";
    }

    return 0;
}
