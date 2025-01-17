#include <iostream>
#include <vector>
#include <iomanip>

// thia is a source code for algorthim design assignment
// Function to predict stock prices using a weighted moving average
std::vector<double> predictStockPrices(const std::vector<double> &historicalPrices, int predictionDays)
{
    int n = historicalPrices.size();
    if (n == 0)
    {
        throw std::invalid_argument("Historical data is empty.");
    }

    // Weights for the moving average
    std::vector<double> weights = {0.1, 0.2, 0.3, 0.4}; // Adjustable
    int weightSize = weights.size();

    std::vector<double> predictedPrices;
    for (int day = 0; day < predictionDays; ++day)
    {
        double weightedSum = 0.0;
        double totalWeights = 0.0;

        // Use the most recent data to predict the next day
        for (int i = 0; i < weightSize; ++i)
        {
            if (n - 1 - i < 0)
                break; // Avoid out-of-bound access
            weightedSum += historicalPrices[n - 1 - i] * weights[weightSize - 1 - i];
            totalWeights += weights[weightSize - 1 - i];
        }

        // Predict the next price
        double nextPrice = (totalWeights > 0) ? (weightedSum / totalWeights) : historicalPrices.back();
        predictedPrices.push_back(nextPrice);

        // Append the predicted price to historical data for future predictions
        historicalPrices.push_back(nextPrice);
    }

    return predictedPrices;
}

int main()
{
    try
    {
        // Historical stock prices (example data)
        std::vector<double> historicalPrices = {100, 102, 105, 107, 110, 112, 115};

        // Number of days to predict
        int predictionDays = 5;

        // Predict stock prices
        std::vector<double> predictedPrices = predictStockPrices(historicalPrices, predictionDays);

        // Output results
        std::cout << "Historical Prices: ";
        for (double price : historicalPrices)
        {
            std::cout << price << " ";
        }
        std::cout << "\nPredicted Prices: ";
        for (double price : predictedPrices)
        {
            std::cout << std::fixed << std::setprecision(2) << price << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
