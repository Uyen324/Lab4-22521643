//Name: Nguyễn Thị Thu Uyên
//Student's ID: 22521643
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

struct Product
{
    std::string name;
    double price;
    int rating;
    // Add other relevant attributes as needed
};

// Helper function to read CSV file and populate products
std::vector<Product> loadProductsFromCSV(const std::string &filename)
{
    std::vector<Product> products;
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return products;
    }

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name;
        double price;
        int rating;

        // Assuming CSV format: name, price, rating
        std::getline(ss, name, ',');
        ss >> price;
        ss.ignore(1, ',');
        ss >> rating;

        products.push_back({name, price, rating});
    }

    return products;
}

// Comparison functions for sorting
bool compareByName(const Product &a, const Product &b)
{
    return a.name < b.name;
}

bool compareByPrice(const Product &a, const Product &b)
{
    return a.price < b.price;
}

bool compareByRating(const Product &a, const Product &b)
{
    return a.rating > b.rating; // Higher rating comes first
}

// Sorting wrapper functions
void sortProducts(std::vector<Product> &products, const std::string &attribute)
{
    if (attribute == "name")
    {
        std::sort(products.begin(), products.end(), compareByName);
    }
    else if (attribute == "price")
    {
        std::sort(products.begin(), products.end(), compareByPrice);
    }
    else if (attribute == "rating")
    {
        std::sort(products.begin(), products.end(), compareByRating);
    }
    else
    {
        std::cerr << "Unknown sorting attribute: " << attribute << std::endl;
    }
}

// Function to analyze the performance of sorting algorithms
void analyzePerformance(std::vector<Product> products, const std::string &attribute)
{
    auto start = std::chrono::high_resolution_clock::now();
    sortProducts(products, attribute);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken to sort by " << attribute << ": " << elapsed.count() << " seconds" << std::endl;
}

int main()
{
    std::string filename = "D:/Lab4/Lab4.1/ElectronicsProductsPricingData.csv";
    std::vector<Product> products = loadProductsFromCSV(filename);

    if (products.empty())
    {
        std::cerr << "No products loaded from file." << std::endl;
        return 1;
    }

    // Analyze sorting by different attributes
    analyzePerformance(products, "name");
    analyzePerformance(products, "price");
    analyzePerformance(products, "rating");

    return 0;
}
