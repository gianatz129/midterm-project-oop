#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

class InventoryBase // Base class for Inventory operations
{
public:
    virtual void addingItems() = 0;
    virtual void updatingItems() = 0;
    virtual void removingItems() = 0;
    virtual void displayingByCategory() = 0;
    virtual void displayingAllItems() = 0;
    virtual void searchingItem() = 0;
    virtual void sortingMenu() = 0;
    virtual void sortingItemsP() = 0;
    virtual void sortingItemsQ() = 0;
    virtual void displaysLowStockItems() = 0;
};

class Inventory : public InventoryBase // Sub class for InventoryBase
{
private:
    struct Item
    {
        string id;
        string name;
        float price;
        int quantity;
        int category;
    };

    static const int MAX_ITEMS = 100;
    Item items[MAX_ITEMS];
    int itemCount;

public:
    Inventory() : itemCount(0) {}
    void addingItems() override
    {
        if (itemCount >= MAX_ITEMS)
        {
            cout << "| Inventory is full. Cannot add more items.                              |" << endl;
            return;
        }

        Item newItem;
        char choice;

        do
        {
            system("pause");
            system("cls");

            cout << "|---------------------------| Input Category |---------------------------|" << endl;
            cout << "| Category 1: Clothing                                                   |" << endl;
            cout << "| Category 2: Electronics                                                |" << endl;
            cout << "| Category 3: Entertainment                                              |" << endl;
            cout << "|------------------------------------------------------------------------|" << endl;

            string categoryInput;
            cout << "| Enter category: ";
            getline(cin, categoryInput);

            // Loop and validations for category
            for (char &c : categoryInput)
                c = tolower(c);
            while (categoryInput != "clothing" && categoryInput != "electronics" && categoryInput != "entertainment")
            {
                cout << "| Invalid category. Please enter a valid category: ";
                getline(cin, categoryInput);
                for (char &c : categoryInput)
                    c = tolower(c);
            }

            if (categoryInput == "clothing")
                newItem.category = 1;
            else if (categoryInput == "electronics")
                newItem.category = 2;
            else if (categoryInput == "entertainment")
                newItem.category = 3;

            system("pause");
            system("cls");
            cout << "|------------------------------| Category |------------------------------|" << endl;

            switch (newItem.category)
            {
            case 1:
                cout << "| You have entered the Clothing category                                 |" << endl;
                break;
            case 2:
                cout << "| You have entered the Electronics category                              |" << endl;
                break;
            case 3:
                cout << "| You have entered the Entertainment category                            |" << endl;
                break;
            }

            cout << "|------------------------------------------------------------------------|" << endl;

            // Validation for Item ID, Checking for duplicates and empty ID
            bool validateItemID = false;
            while (!validateItemID)
            {
                cout << "| Enter ID: ";
                getline(cin, newItem.id);

                if (newItem.id.empty()) // Check for empty string input
                {
                    cout << "| Item ID cannot be empty!                                               |" << endl;
                }
                else // Ensure no duplicate Item IDs
                {
                    bool duplicateID = false;
                    for (int i = 0; i < itemCount; i++)
                    {
                        if (items[i].id == newItem.id)
                        {
                            cout << "| Item ID already exists! Please enter a new Item ID.                    |" << endl;
                            duplicateID = true;
                            break;
                        }
                    }
                    if (!duplicateID)
                    {
                        validateItemID = true;
                    }
                }
            }

            // Existing validation for item name
            cout << "| Enter name: ";
            getline(cin, newItem.name);
            while (newItem.name.empty()) // If there is no input or space
            {
                cout << "| Name cannot be empty. Please enter a valid name: ";
                getline(cin, newItem.name);
            }

            // Price validation (same as before)
            string priceInput;
            cout << "| Enter price: ";
            getline(cin, priceInput);

            // Validates, checks if the input has string: IT SHOULD ONLY ACCEPT POSITIVE NUMBERS WITH DECIMALS
            bool isValidPrice = !priceInput.empty() && (priceInput[0] != '-' && priceInput[0] != '+');
            int decimalCount = 0;

            for (char c : priceInput)
            {
                if (c == '.')
                {
                    decimalCount++;
                }
                else if (c < '0' || c > '9')
                {
                    isValidPrice = false;
                    break;
                }

                if (decimalCount > 1) // Ensures only one decimal point is allowed
                {
                    isValidPrice = false;
                    break;
                }
            }

            // Check if the price is 0 or 0.0 and reject it
            while (!isValidPrice || priceInput == "0" || priceInput == "0.0")
            {
                cout << "| Price cannot be zero. Please enter a valid no: ";
                getline(cin, priceInput);

                isValidPrice = !priceInput.empty() && (priceInput[0] != '-' && priceInput[0] != '+');
                decimalCount = 0;

                for (char c : priceInput)
                {
                    if (c == '.')
                    {
                        decimalCount++;
                    }
                    else if (c < '0' || c > '9')
                    {
                        isValidPrice = false;
                        break;
                    }

                    if (decimalCount > 1)
                    {
                        isValidPrice = false;
                        break;
                    }
                }
            }

            newItem.price = stof(priceInput); // Convert to float to accommodate decimal values

            // Quantity validation (same as before)
            string quantityInput;
            cout << "| Enter quantity: ";
            getline(cin, quantityInput);

            // Validates, checks if the input has string: IT SHOULD ONLY ACCEPT POSITIVE NUMBERS
            bool isValidQuantity = !quantityInput.empty() && (quantityInput[0] != '-' && quantityInput[0] != '+');
            for (char c : quantityInput)
            {
                if (c < '0' || c > '9')
                {
                    isValidQuantity = false;
                    break;
                }
            }
            while (!isValidQuantity || stoi(quantityInput) <= 0)
            {
                cout << "| Invalid quantity. Please enter a valid no: ";
                getline(cin, quantityInput);

                isValidQuantity = !quantityInput.empty() && (quantityInput[0] != '-' && quantityInput[0] != '+');
                for (char c : quantityInput)
                {
                    if (c < '0' || c > '9')
                    {
                        isValidQuantity = false;
                        break;
                    }
                }
            }

            newItem.quantity = stoi(quantityInput); // Convert to integer

            cout << "|------------------------------------------------------------------------|" << endl;
            cout << "| Item added successfully.                                               |" << endl;

            items[itemCount] = newItem;
            itemCount++;

            cout << "| Do you want to add another item? (Y/N): "; // Asks the user if they want to add more items
            string choiceInput;
            getline(cin, choiceInput);

            while (choiceInput.length() != 1 || (choiceInput[0] != 'y' && choiceInput[0] != 'Y' && choiceInput[0] != 'n' && choiceInput[0] != 'N'))
            {
                cout << "| Invalid input. Please enter (Y/N): ";
                getline(cin, choiceInput);
            }

            choice = choiceInput[0];
        } while ((choice == 'y' || choice == 'Y') && itemCount < MAX_ITEMS);
    }
    void updatingItems() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to update.                                   |" << endl;
            return;
        }

        char choice;
        do
        {
            string searchID;
            bool found = false;

            system("pause");
            system("cls");
            cout << "|---------------------------| Updating Items |---------------------------|" << endl;
            cout << "| Enter the ID of the item you want to update: ";
            getline(cin, searchID);

            for (int i = 0; i < itemCount; i++) // Search for the item by ID
            {
                if (items[i].id == searchID)
                {
                    found = true;
                    cout << "|-----------------------------| Item found |-----------------------------|" << endl;
                    cout << "| ID: " << items[i].id << endl;
                    cout << "| Name: " << items[i].name << endl;
                    cout << "| Price: " << items[i].price << endl;
                    cout << "| Quantity: " << items[i].quantity << endl;
                    cout << "|------------------------------------------------------------------------|" << endl;

                    int updateChoice = 0;

                    do
                    {
                        cout << "|--------------------------| Update Item By: |---------------------------|" << endl;
                        cout << "| 1 - Price                                                              " << endl;
                        cout << "| 2 - Quantity                                                           " << endl;
                        cout << "| Enter your choice: ";
                        cin >> updateChoice;
                        cin.ignore();

                        if (updateChoice == 1) // Update Price
                        {
                            string priceInput;
                            bool isValidPrice = false;
                            int decimalCount = 0;

                            cout << "| Enter new price: ";
                            while (!isValidPrice) // Validates and accepts decimals for price
                            {
                                getline(cin, priceInput);

                                // Check if the price input is valid: positive decimal number
                                isValidPrice = !priceInput.empty() && (priceInput[0] != '-' && priceInput[0] != '+');
                                decimalCount = 0;

                                for (char c : priceInput)
                                {
                                    if (c == '.')
                                    {
                                        decimalCount++;
                                    }
                                    else if (c < '0' || c > '9')
                                    {
                                        isValidPrice = false;
                                        break;
                                    }

                                    if (decimalCount > 1)
                                    {
                                        isValidPrice = false;
                                        break;
                                    }
                                }

                                // Check if the price is 0 or 0.0 and reject it
                                if (isValidPrice && (priceInput == "0" || priceInput == "0.0"))
                                {
                                    isValidPrice = false;
                                    cout << "| Price cannot be zero. Please enter a valid no: ";
                                }

                                if (isValidPrice)
                                {
                                    items[i].price = stof(priceInput); // Update the item price
                                }
                                else if (priceInput != "0" && priceInput != "0.0")
                                {
                                    cout << "| Invalid price. Please enter a valid no: ";
                                }
                            }

                            cout << "| Price updated successfully!                                            |" << endl;
                        }
                        else if (updateChoice == 2) // Update Quantity
                        {
                            string quantityInput;
                            bool isValidQuantity = false;
                            cout << "| Enter new quantity: ";
                            while (!isValidQuantity)
                            {
                                getline(cin, quantityInput);

                                // Check if the input is empty
                                if (quantityInput.empty())
                                {
                                    cout << "| Quantity cannot be empty. Please enter a valid no: ";
                                    continue;
                                }

                                isValidQuantity = true;
                                for (char c : quantityInput)
                                {
                                    if (!isdigit(c)) // Ensure all characters are digits
                                    {
                                        isValidQuantity = false;
                                        break;
                                    }
                                }

                                if (isValidQuantity)
                                {
                                    // Manually check if the input can be safely converted to an integer
                                    int newQuantity = 0;
                                    bool validConversion = true;

                                    for (char c : quantityInput)
                                    {
                                        if (isdigit(c))
                                        {
                                            newQuantity = newQuantity * 10 + (c - '0');
                                        }
                                        else
                                        {
                                            validConversion = false;
                                            break;
                                        }
                                    }

                                    if (validConversion && newQuantity > 0)
                                    {
                                        items[i].quantity = newQuantity; // Update the item's quantity
                                    }
                                    else
                                    {
                                        isValidQuantity = false;
                                    }
                                }

                                if (!isValidQuantity)
                                {
                                    cout << "| Invalid quantity. Please enter a valid no: ";
                                }
                            }
                            cout << "| Quantity updated successfully!                                          |" << endl;
                        }
                        else
                        {
                            cout << "| Invalid choice. Please select 1 or 2.                                   |" << endl;
                        }

                    } while (updateChoice < 1 || updateChoice > 2);

                    // After updating, ask if the user wants to update another item
                    cout << "| Do you want to update another item? (Y/N): ";
                    string choiceInput;
                    getline(cin, choiceInput);

                    while (choiceInput.length() != 1 || (choiceInput[0] != 'y' && choiceInput[0] != 'Y' && choiceInput[0] != 'n' && choiceInput[0] != 'N'))
                    {
                        cout << "| Invalid choice. Please enter (Y/N): ";
                        getline(cin, choiceInput);
                    }

                    choice = choiceInput[0];

                    break;
                }
            }

            if (!found)
            {
                cout << "| Item with ID '" << searchID << "' not found." << endl;
            }

        } while (choice == 'y' || choice == 'Y');
    }
    void removingItems() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to remove.                                   |" << endl;
            return;
        }

        char confirm;
        string searchID;
        bool found = false;
        char choice;

        do
        {
            system("pause");
            system("cls");
            cout << "|---------------------------| Removing Items |---------------------------|" << endl;
            cout << "| Enter the ID of the item you want to remove: ";
            getline(cin, searchID);

            for (int i = 0; i < itemCount; i++) // Search for the item by ID
            {
                if (items[i].id == searchID)
                {
                    found = true;
                    cout << "|-----------------------------| Item found |-----------------------------|" << endl;
                    cout << "| ID: " << items[i].id << endl;
                    cout << "| Name: " << items[i].name << endl;
                    cout << "| Price: " << items[i].price << endl;
                    cout << "| Quantity: " << items[i].quantity << endl;
                    cout << "|------------------------------------------------------------------------|" << endl;

                    cout << "| Do you want to remove this item? (y/n): ";
                    cin >> confirm;

                    if (confirm == 'y' || confirm == 'Y')
                    {
                        for (int j = i; j < itemCount - 1; j++)
                        {
                            items[j] = items[j + 1];
                        }
                        itemCount--;
                        cout << "| Item removed successfully!                                             |" << endl;
                    }
                    else
                    {
                        cout << "| Item not removed.                                                      |" << endl;
                    }
                    break;
                }
            }

            if (!found)
            {
                cout << "| Item with ID '" << searchID << "' not found. " << endl;
            }

            cout << "| Do you want to remove another item? (y/n): "; // Ask the user if they want to remove another item
            string choiceInput;
            cin.ignore();
            getline(cin, choiceInput);

            while (choiceInput.length() != 1 || (choiceInput[0] != 'y' && choiceInput[0] != 'Y' && choiceInput[0] != 'n' && choiceInput[0] != 'N'))
            {
                cout << "| Invalid choice. Please enter (Y/N): ";
                getline(cin, choiceInput);
            }

            choice = choiceInput[0];

        } while (choice == 'y' || choice == 'Y');
    }
    void displayingByCategory() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to display.                                  |" << endl;
            return;
        }

        string categoryInput;
        system("pause");
        system("cls");
        cout << "|---------------------------| Input Category |---------------------------|" << endl;
        cout << "| Category 1: Clothing                                                   |" << endl;
        cout << "| Category 2: Electronics                                                |" << endl;
        cout << "| Category 3: Entertainment                                              |" << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| Enter category: ";
        getline(cin, categoryInput);

        for (char &c : categoryInput)
            c = tolower(c);

        int categoryChoice = 0;

        bool validCategory = false;

        while (!validCategory)
        {
            if (categoryInput == "clothing")
            {
                categoryChoice = 1;
                validCategory = true;
            }
            else if (categoryInput == "electronics")
            {
                categoryChoice = 2;
                validCategory = true;
            }
            else if (categoryInput == "entertainment")
            {
                categoryChoice = 3;
                validCategory = true;
            }
            else
            {
                cout << "| Invalid category. Please enter a valid category: ";
                getline(cin, categoryInput);

                for (char &c : categoryInput) // Convert the input to lowercase again
                    c = tolower(c);
            }
        }

        system("pause");
        system("cls");
        bool categoryExists = false;

        cout << "|-----------------------------------------| Items in Category |-----------------------------------|" << endl;
        cout << left << setw(30) << "| ID" << setw(30) << "Name" << setw(30) << "Quantity" << setw(30) << "Price   |" << endl;
        cout << "|-------------------------------------------------------------------------------------------------|" << endl;

        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].category == categoryChoice)
            {
                categoryExists = true;
                cout << "| " << left << setw(28) << items[i].id
                     << left << setw(30) << items[i].name
                     << left << setw(30) << items[i].quantity
                     << left << setw(30) << items[i].price << endl;
            }
        }

        cout << "|-------------------------------------------------------------------------------------------------|" << endl;

        if (!categoryExists)
        {
            cout << "| No items found in the " << categoryInput << " category!" << endl;
        }
    }
    void displayingAllItems() override
    {
        if (itemCount == 0)
        {
            cout << "| No items to display.                                                   |" << endl;
            return;
        }

        system("pause");
        system("cls");
        cout << "|------------------------------------------------------| Items in Inventory |---------------------------------------------------------|" << endl;
        cout << left << setw(30) << "| ID" << setw(30) << "Name" << setw(30) << "Price" << setw(30) << "Quantity" << setw(30) << "Category      |" << endl;
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------|" << endl;

        for (int i = 0; i < itemCount; i++)
        {
            cout << "| " << left << setw(28) << items[i].id << setw(30) << items[i].name << setw(30) << items[i].price << setw(30) << items[i].quantity;

            string category;
            switch (items[i].category)
            {
            case 1:
                category = "Clothing";
                break;
            case 2:
                category = "Electronics";
                break;
            case 3:
                category = "Entertainment";
                break;
            default:
                category = "Unknown";
            }

            cout << setw(20) << category << endl;
        }
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------|" << endl;
    }
    void searchingItem() override
    {
        if (itemCount == 0)
        {
            cout << "| No items to search.                                                    |" << endl;
            return;
        }

        string searchID;
        bool found = false;

        system("pause");
        system("cls");
        cout << "|--------------------------| Searching Items |---------------------------|" << endl;
        cout << "| Enter the ID of the item you want to search: ";
        getline(cin, searchID);

        for (int i = 0; i < itemCount; i++) // Search for the item by ID
        {
            if (items[i].id == searchID)
            {
                found = true;
                cout << "|-----------------------------| Item found |-----------------------------|" << endl;
                cout << "| ID: " << items[i].id << endl;
                cout << "| Name: " << items[i].name << endl;
                cout << "| Price: " << items[i].price << endl;
                cout << "| Quantity: " << items[i].quantity << endl;
                cout << "|------------------------------------------------------------------------|" << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "| Item with ID '" << searchID << "' not found." << endl;
        }
    }
    void sortingMenu() override
    {
        if (itemCount == 0)
        {
            cout << "| No items to sort.                                                      |" << endl;
            return;
        }

        string choiceInput;
        int choice;

        system("pause");
        system("cls");
        cout << "|-----------------------------| Sort Items |-----------------------------|" << endl;
        cout << "| 1 - Price" << endl;
        cout << "| 2 - Quantity" << endl;
        cout << "| 3 - Return to main menu" << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| Enter your choice: ";
        getline(cin, choiceInput);

        while (choiceInput != "1" && choiceInput != "2" && choiceInput != "3")
        {
            cout << "| Invalid choice. Please enter a valid no: ";
            getline(cin, choiceInput);
        }

        choice = stoi(choiceInput); // Convert valid input to integer

        switch (choice)
        {
        case 1:
            sortingItemsP(); // Sort by price
            break;
        case 2:
            sortingItemsQ(); // Sort by quantity
            break;
        case 3:
            return; // Return to main menu
        default:
            cout << "| Invalid choice. Please try again.                                      |" << endl;
            return;
        }
    }
    void sortingItemsP() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to sort.                                     |" << endl;
            return;
        }

        string choiceInput;
        int choice;

        system("pause");
        system("cls");
        cout << "|------------------------| Sort Items by Price |-------------------------|" << endl;
        cout << "| 1 - Ascending                                                          " << endl;
        cout << "| 2 - Descending                                                         " << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| Enter your choice: ";
        getline(cin, choiceInput);

        while (choiceInput != "1" && choiceInput != "2")
        {
            cout << "| Invalid choice. Please enter a valid no: ";
            getline(cin, choiceInput);
        }

        choice = stoi(choiceInput); // Convert valid input to integer

        switch (choice)
        {
        case 1:
            // Ascending order sorting logic by price
            for (int i = 0; i < itemCount - 1; i++)
            {
                for (int j = 0; j < itemCount - i - 1; j++)
                {
                    if (items[j].price > items[j + 1].price)
                    {
                        Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
            cout << "| Items sorted in ascending order by price.                              |" << endl;
            break;

        case 2:
            // Descending order sorting logic by price
            for (int i = 0; i < itemCount - 1; i++)
            {
                for (int j = 0; j < itemCount - i - 1; j++)
                {
                    if (items[j].price < items[j + 1].price)
                    {
                        Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
            cout << "| Items sorted in descending order by price.                             |" << endl;
            break;
        }

        displayingAllItems(); // Display sorted items
    }
    void sortingItemsQ() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to sort.                                     |" << endl;
            return;
        }

        string choiceInput;
        int choice;

        system("pause");
        system("cls");
        cout << "|------------------------| Sort Items by Quantity |----------------------|" << endl;
        cout << "| 1 - Ascending                                                          " << endl;
        cout << "| 2 - Descending                                                         " << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| Enter your choice: ";
        getline(cin, choiceInput);

        while (choiceInput != "1" && choiceInput != "2")
        {
            cout << "| Invalid choice. Please enter a valid no: ";
            getline(cin, choiceInput);
        }

        choice = stoi(choiceInput); // Convert valid input to integer

        switch (choice)
        {
        case 1:
            // Ascending order sorting logic by quantity
            for (int i = 0; i < itemCount - 1; i++)
            {
                for (int j = 0; j < itemCount - i - 1; j++)
                {
                    if (items[j].quantity > items[j + 1].quantity)
                    {
                        Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
            cout << "| Items sorted in ascending order by quantity.                           |" << endl;
            break;

        case 2:
            // Descending order sorting logic by quantity
            for (int i = 0; i < itemCount - 1; i++)
            {
                for (int j = 0; j < itemCount - i - 1; j++)
                {
                    if (items[j].quantity < items[j + 1].quantity)
                    {
                        Item temp = items[j];
                        items[j] = items[j + 1];
                        items[j + 1] = temp;
                    }
                }
            }
            cout << "| Items sorted in descending order by quantity.                          |" << endl;
            break;
        }

        displayingAllItems(); // Display sorted items
    }
    void displaysLowStockItems() override
    {
        if (itemCount == 0)
        {
            cout << "| No items in the inventory to display.                                  |" << endl;
            return;
        }

        bool lowStockFound = false;

        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].quantity < 6) // Check if item is lower than 6 then display items with quantity of 5 and below
            {
                lowStockFound = true;
                break;
            }
        }

        if (!lowStockFound)
        {
            cout << "| No low stock items found.                                              |" << endl;
            return;
        }

        system("pause");
        system("cls");
        cout << "|------------------------------------------------------| Items in Inventory |---------------------------------------------------------|" << endl;
        cout << left << setw(30) << "| ID" << setw(30) << "Name" << setw(30) << "Price" << setw(30) << "Quantity" << setw(30) << "Category      |" << endl;
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------|" << endl;

        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].quantity < 6) // Only display items with quantity less than 6
            {
                cout << "| " << left << setw(28) << items[i].id << setw(30) << items[i].name << setw(30) << items[i].price << setw(30) << items[i].quantity;

                string category;
                switch (items[i].category)
                {
                case 1:
                    category = "Clothing";
                    break;
                case 2:
                    category = "Electronics";
                    break;
                case 3:
                    category = "Entertainment";
                    break;
                default:
                    category = "Unknown";
                }

                cout << setw(20) << category << endl;
            }
        }
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------|" << endl;
    }
};

int main()
{
    string choiceInput;
    int choice;
    Inventory inventory;

    do
    {
        system("pause");
        system("cls");
        cout << "|------------------------| INVENTORY MANAGEMENT |------------------------|" << endl;
        cout << "|--------------------------------| MENU |--------------------------------|" << endl;
        cout << "| 1. Add Item                                                            |" << endl;
        cout << "| 2. Update Item                                                         |" << endl;
        cout << "| 3. Remove Item                                                         |" << endl;
        cout << "| 4. Display all Items by Category                                       |" << endl;
        cout << "| 5. Display all Items                                                   |" << endl;
        cout << "| 6. Search Item                                                         |" << endl;
        cout << "| 7. Sort Item                                                           |" << endl;
        cout << "| 8. Display Low Stock Items                                             |" << endl;
        cout << "| 9. Exit                                                                |" << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| Enter your choice: ";
        getline(cin, choiceInput);

        if (choiceInput.length() == 1 && choiceInput[0] >= '1' && choiceInput[0] <= '9')
        {
            choice = choiceInput[0] - '0';
        }
        else
        {
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            inventory.addingItems();
            break;
        case 2:
            inventory.updatingItems();
            break;
        case 3:
            inventory.removingItems();
            break;
        case 4:
            inventory.displayingByCategory();
            break;
        case 5:
            inventory.displayingAllItems();
            break;
        case 6:
            inventory.searchingItem();
            break;
        case 7:
            inventory.sortingMenu();
            break;
        case 8:
            inventory.displaysLowStockItems();
            break;
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
