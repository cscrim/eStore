/*
  Name: eStore.c
  Author: Courtney Scrimshaw
  Function: a program that allows users to add, search, and remove products from an eStore
  Compilation: gcc -Wall -std=c99 -o eStore eStore.c 
  Execution: ./eStore
  Date: created February 2nd, 2024
*/

#include <stdio.h>
#define MAX_LENGTH 100


// Declare all functions before calling them (name and type)
// Specify void because there is no return value (and the compiler errors without it)
// Specify pointers to enable array synchronization by storing in memory
void addProduct(int id, int year, float price, int quantity, int *ids, int *years, float *prices, int *quantities, int *count);
void removeProduct(int id, int *ids, int *years, float *prices, int *quantities, int *count);
void searchProduct(int id, int startYear, int endYear, int *ids, int *years, float *prices, int *quantities, int count);


//Initialize arrays with MAX_LENGTH to keep track of the number of elements
// Float data type for prices array to maintain accuracy
int main() {
    int ids[MAX_LENGTH];
    int years[MAX_LENGTH];
    float prices[MAX_LENGTH];
    int quantities[MAX_LENGTH];
    int count = 0;

    //Do While loop for user choices 
    int choice;
    do {
        printf("\n1. Add Product\n");
        printf("2. Remove Product\n");
        printf("3. Search Product\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //User enters a switch statement based on their choice
        switch (choice) {

          // Case 1 - Add a new product
          case 1: {
              int id, year, quantity;
              float price;
              int i;

              //User enters product ID
              do {
                  printf("Enter product ID: ");
                  scanf("%d", &id);

                  // Check if the ID already exists by iterating through the ids array with a for loop
                  for (i = 0; i < count; i++) {

                      //If a match is found inform the user and have them update the year, price, and quantity 
                      if (ids[i] == id) {
                          printf("Product with ID %d already exists.\n", id);
                          printf("Enter new product year: ");
                          scanf("%d", &year);
                          printf("Enter new product price: ");
                          scanf("%f", &price);
                          printf("Enter new product quantity: ");
                          scanf("%d", &quantity);

                          // Assign the new values to the existing arrays
                          years[i] = year;
                          prices[i] = price;
                          quantities[i] = quantity;
                          printf("Product with ID %d updated successfully.\n", id);
                          break;
                      }
                  }

                  // If the ID does not exist then proceed to add the new product
                  if (i == count) {
                      printf("Enter product year: ");
                      scanf("%d", &year);

                      printf("Enter product price: ");
                      scanf("%f", &price);

                      printf("Enter product quantity: ");
                      scanf("%d", &quantity);

            // Store the information directly into the arrays
            ids[count] = id;
            years[count] = year;
            prices[count] = price;
            quantities[count] = quantity;
            count++;
            printf("Product added successfully\n");
        }

        // Ensure loop keeps executing until the user enters a unique product ID or updates an existing ID 
    } while (i == count); 
    break;
}

            // Case 2 - Remove a product 
            // Declare idToRemove to store the ID of the product the user wants to remove
            case 2: {
                int idToRemove;
                printf("Enter the ID of the product to remove: ");
                scanf("%d", &idToRemove);

                // Calls remove product function to modify the corresponding arrays of the ID being removed
                removeProduct(idToRemove, ids, years, prices, quantities, &count);
                break;
            }

            // Case 3 - Search for a product
            case 3: {
                //user can opt to search by product ID, year, or both. If one parameter is to be ignored the user can enter 0
                int idToSearch, startYear, endYear;
                printf("Enter product ID to search (or enter 0 to ignore): ");
                scanf("%d", &idToSearch);

                printf("Enter start year for time period (or enter 0 to ignore): ");
                scanf("%d", &startYear);

                printf("Enter end year for time period (or enter 0 to ignore): ");
                scanf("%d", &endYear);

                searchProduct(idToSearch, startYear, endYear, ids, years, prices, quantities, count);
                break;
            }

            case 0:
                printf("Exiting the program.. goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    // While loop so this continues as long as we choose not to exit the program
    } while (choice != 0);

    return 0;
}

// Separated remove and search functions from the switch statement for better readability

// Remove a product from the eStore
// Intialize index to -1 to act as a placeholder so when we search through the array we can determine if it does not exist 
void removeProduct(int id, int *ids, int *years, float *prices, int *quantities, int *count) {
    int index = -1;

    // Iterate through the ids array to find the index of the ID to be removed
    for (int i = 0; i < *count; i++) {
        if (ids[i] == id) {
            index = i;
            break;
        }
    }

  // if the ID was found in the array ask the user for the quantity to remove
  if (index != -1) {
    int quantityToRemove;
    printf("Enter the quantity to remove: ");
    scanf("%d", &quantityToRemove);

    // Check if the quantity to remove is valid
        if (quantityToRemove > 0 && quantityToRemove <= quantities[index]) {
            quantities[index] -= quantityToRemove;

            // Tell the user the units that have been removed and the remaining units of a given product ID
            printf("Removed %d units of product with ID %d.\n", quantityToRemove, id);
            printf("Remaining quantity for product with ID %d: %d\n", id, quantities[index]);

            // Checks if the quantity of the product becomes 0 
            if (quantities[index] == 0) {

                // Iterate over each array to shift the elements one position left by assigning the value of the "next" element to the current one
                for (int i = index; i < *count - 1; i++) {
                    ids[i] = ids[i + 1];
                    years[i] = years[i + 1];
                    prices[i] = prices[i + 1];
                    quantities[i] = quantities[i + 1];
                }
                // If all items of a product are removed the user is notified and the count is decremented 
                printf("Product with ID %d removed completely.\n", id);
                (*count)--;
            }
        } else {
            // Invalid quantity means <= 0 or more items than available
            printf("Invalid quantity to remove or exceeds available quantity.\n");
        }
    } else {
        printf("Product with ID %d not found.\n", id);
    }
}


// Function to search for a product in the eStore
void searchProduct(int id, int startYear, int endYear, int *ids, int *years, float *prices, int *quantities, int count) {

    // Iterate through each product in the store 
    // Allow users to search by product ID, year, or both
    printf("Search Results:\n");
    for (int i = 0; i < count; i++) {

        // Check if the ID matches (or allow the user to enter 0 to ignore this search parameter)
        if ((id == 0 || ids[i] == id) &&

            // Check if the year falls within the search range (or allow the user to enter 0 to ignore this search parameter)
            (startYear == 0 || years[i] >= startYear) &&
            (endYear == 0 || years[i] <= endYear)) {
            printf("ID: %d\nYear: %d\nPrice: %.2f\nQuantity: %d\n", ids[i], years[i], prices[i], quantities[i]);
        }
    }
}