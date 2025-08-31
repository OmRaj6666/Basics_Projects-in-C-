#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

// Callback function to write API response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *output)
{
    size_t total_size = size * nmemb;
    output->append((char *)contents, total_size);
    return total_size;
}

// Extract value from JSON string
string extractValue(const string &json, const string &key)
{
    size_t key_pos = json.find("\"" + key + "\":");
    if (key_pos == string::npos)
        return "N/A";

    size_t start = json.find_first_of(":", key_pos) + 1;
    size_t end = json.find_first_of(",}", start);

    string value = json.substr(start, end - start);
    value.erase(remove(value.begin(), value.end(), '"'), value.end());
    value.erase(remove(value.begin(), value.end(), ' '), value.end());

    return value;
}

void displayWeather(const string &city, const string &response)
{
    string temp = extractValue(response, "temp");
    string feels_like = extractValue(response, "feels_like");
    string humidity = extractValue(response, "humidity");
    string description = extractValue(response, "description");

    cout << "\nWeather in " << city << ":\n";
    cout << "Temperature: " << temp << "°C\n";
    cout << "Feels like: " << feels_like << "°C\n";
    cout << "Humidity: " << humidity << "%\n";
    cout << "Conditions: " << description << "\n";
}

int main()
{
    CURL *curl;
    CURLcode res;
    string response;
    string apiKey = "bd5e378503939ddaee76f12ad7a97608"; // Replace with your OpenWeatherMap API key
        string city;

    cout << "Enter city name: ";
    getline(cin, city);

    if (city.empty())
    {
        city = "London";
    }

    curl = curl_easy_init();
    if (curl)
    {
        string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city +
                     "&appid=" + apiKey + "&units=metric";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
            return 1;
        }

        curl_easy_cleanup(curl);

        displayWeather(city, response);
    }

    return 0;
}