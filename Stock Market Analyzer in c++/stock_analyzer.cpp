#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

class StockAnalyzer
{
private:
    struct Stock
    {
        string symbol;
        vector<double> prices;
        int shares;

        double averagePrice() const
        {
            if (prices.empty())
                return 0.0;
            double sum = 0.0;
            for (double price : prices)
            {
                sum += price;
            }
            return sum / prices.size();
        }

        double currentValue(double currentPrice) const
        {
            return shares * currentPrice;
        }
    };

    map<string, Stock> portfolio;
    map<string, double> currentPrices;

public:
    void addStock(const string &symbol, int shares, const vector<double> &historicalPrices)
    {
        portfolio[symbol] = {symbol, historicalPrices, shares};
    }

    void updateCurrentPrice(const string &symbol, double price)
    {
        currentPrices[symbol] = price;
    }

    void displayPortfolio() const
    {
        cout << "\nPORTFOLIO OVERVIEW\n";
        cout << "----------------------------------------\n";
        cout << setw(6) << "SYMBOL" << setw(10) << "SHARES"
             << setw(12) << "AVG PRICE" << setw(12) << "CURRENT"
             << setw(12) << "VALUE" << setw(12) << "GAIN/LOSS\n";
        cout << "----------------------------------------\n";

        double totalValue = 0.0;
        double totalInvestment = 0.0;

        for (const auto &[symbol, stock] : portfolio)
        {
            if (currentPrices.find(symbol) == currentPrices.end())
                continue;

            double currentPrice = currentPrices.at(symbol);
            double avgPrice = stock.averagePrice();
            double value = stock.currentValue(currentPrice);
            double investment = stock.shares * avgPrice;
            double gainLoss = value - investment;

            cout << setw(6) << symbol
                 << setw(10) << stock.shares
                 << setw(12) << fixed << setprecision(2) << avgPrice
                 << setw(12) << currentPrice
                 << setw(12) << value
                 << setw(12) << gainLoss << "\n";

            totalValue += value;
            totalInvestment += investment;
        }

        cout << "----------------------------------------\n";
        cout << "TOTAL:" << setw(38) << fixed << setprecision(2) << totalValue
             << setw(12) << (totalValue - totalInvestment) << "\n\n";
    }

    void calculateRSI(const string &symbol, int periods = 14)
    {
        if (portfolio.find(symbol) == portfolio.end())
        {
            cout << "Stock not found in portfolio.\n";
            return;
        }

        const vector<double> &prices = portfolio[symbol].prices;
        if (prices.size() < periods + 1)
        {
            cout << "Not enough data for RSI calculation.\n";
            return;
        }

        vector<double> gains, losses;
        for (size_t i = 1; i <= periods; i++)
        {
            double change = prices[i] - prices[i - 1];
            if (change >= 0)
            {
                gains.push_back(change);
                losses.push_back(0.0);
            }
            else
            {
                gains.push_back(0.0);
                losses.push_back(abs(change));
            }
        }

        double avgGain = 0.0, avgLoss = 0.0;
        for (size_t i = 0; i < periods; i++)
        {
            avgGain += gains[i];
            avgLoss += losses[i];
        }
        avgGain /= periods;
        avgLoss /= periods;

        if (avgLoss == 0.0)
        {
            cout << "RSI for " << symbol << ": 100\n";
            return;
        }

        double rs = avgGain / avgLoss;
        double rsi = 100 - (100 / (1 + rs));

        cout << "RSI(" << periods << ") for " << symbol << ": " << fixed << setprecision(2) << rsi << "\n";
    }

    void simpleMovingAverage(const string &symbol, int window = 20)
    {
        if (portfolio.find(symbol) == portfolio.end())
        {
            cout << "Stock not found in portfolio.\n";
            return;
        }

        const vector<double> &prices = portfolio[symbol].prices;
        if (prices.size() < window)
        {
            cout << "Not enough data for SMA calculation.\n";
            return;
        }

        double sum = 0.0;
        for (size_t i = prices.size() - window; i < prices.size(); i++)
        {
            sum += prices[i];
        }

        double sma = sum / window;
        cout << "SMA(" << window << ") for " << symbol << ": " << fixed << setprecision(2) << sma << "\n";
    }
};

void displayMenu()
{
    cout << "\nSTOCK MARKET ANALYZER\n";
    cout << "1. Add Stock to Portfolio\n";
    cout << "2. Update Current Prices\n";
    cout << "3. View Portfolio\n";
    cout << "4. Calculate RSI\n";
    cout << "5. Calculate SMA\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
}

int main()
{
    StockAnalyzer analyzer;
    int choice;

    // Sample initialization
    analyzer.addStock("AAPL", 100, {148.50, 149.80, 152.30, 151.90, 153.20, 154.50, 153.90});
    analyzer.addStock("MSFT", 50, {302.10, 304.50, 305.30, 307.80, 306.40, 308.90, 310.20});
    analyzer.updateCurrentPrice("AAPL", 155.25);
    analyzer.updateCurrentPrice("MSFT", 312.75);

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string symbol;
            int shares;
            vector<double> prices;
            double price;
            int numPrices;

            cout << "Enter stock symbol: ";
            cin >> symbol;
            cout << "Enter number of shares: ";
            cin >> shares;
            cout << "How many historical prices? ";
            cin >> numPrices;

            cout << "Enter historical prices (oldest first):\n";
            for (int i = 0; i < numPrices; i++)
            {
                cin >> price;
                prices.push_back(price);
            }

            analyzer.addStock(symbol, shares, prices);
            break;
        }
        case 2:
        {
            string symbol;
            double price;

            cout << "Enter stock symbol: ";
            cin >> symbol;
            cout << "Enter current price: ";
            cin >> price;

            analyzer.updateCurrentPrice(symbol, price);
            break;
        }
        case 3:
            analyzer.displayPortfolio();
            break;
        case 4:
        {
            string symbol;
            cout << "Enter stock symbol: ";
            cin >> symbol;
            analyzer.calculateRSI(symbol);
            break;
        }
        case 5:
        {
            string symbol;
            int window;
            cout << "Enter stock symbol: ";
            cin >> symbol;
            cout << "Enter SMA window size: ";
            cin >> window;
            analyzer.simpleMovingAverage(symbol, window);
            break;
        }
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}