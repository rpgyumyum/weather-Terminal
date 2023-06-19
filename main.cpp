#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <json/json.h>
#include <curl/curl.h>
#include <cstdio>


//Callbackfunction to receive response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main(int argc, char const *argv[])
{
	
	CURL* curl;
	CURLcode res;

	//Initialize libcurl
	curl_global_init(CURL_GLOBAL_DEFAULT);

	//Create a curl handle
	curl = curl_easy_init();
	if (curl)
	{
		std::string response;

		//set the url to make the API request
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.weatherapi.com/v1/current.json?key=b3a0de69383b457cbd7134358231706&q=auto:ip");

		//set the callback function to receive response data 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		//perform the request
		res = curl_easy_perform(curl);

		//save the json file
		std::ofstream file("/home/Lukas/Projects/weather-api/RawWeather.json");
		file << response;
		file.close();

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	//reopen file
	std::ifstream file("/home/Lukas/Projects/weather-api/RawWeather.json");
	std::ifstream asciiArtRawFile("/home/Lukas/Projects/weather-api/asciiart.json");

	//place the file contents imt the json value "root"
	Json::Value root;
	file >> root;

	Json::Value asciiArt;
	asciiArtRawFile >> asciiArt;

	//get data of the raw data file 

	double TemperatureFloat = root["current"]["temp_c"].asDouble();
    std::string temperature = std::to_string(TemperatureFloat);
    temperature = temperature.substr(0, temperature.find('.') + 2) + " °C";

	double feelslikeC = root["current"]["feelslike_c"].asDouble();
    std::string feelTemperature = std::to_string(feelslikeC);
    feelTemperature = feelTemperature.substr(0, feelTemperature.find('.') + 2) + " °C";

	std::string currentCondition = root["current"]["condition"]["text"].asString();
	int uvIndex = root["current"]["uv"].asInt();
	std::string currentTimeDate = root["location"]["localtime"].asString();
	std::string currentCountry = root["location"]["country"].asString();



	std::cout << '\n';

	//write the first line
	std::cout << std::left << std::setw(20) << asciiArt[currentCondition]["line1"].asString() << 
		std::left << std::setw(36) <<  temperature << "feels like "<< feelTemperature << '\n';
	//write the second line
	std::cout << std::left << std::setw(20) << asciiArt[currentCondition]["line2"].asString() << 
		std::left << std::setw(35) << currentCondition;

	//check if u should wear sunscreen off of uv-index
	if(uvIndex <= 2)
	{
		std::cout << std::left << std::setw(30) << "you dont need to wear sunscreen";
	}
	else if (uvIndex <= 7)
	{
		std::cout << std::left << std::setw(30) << "you should wear sunscreen";
	}
	else
	{
		std::cout << std::left << std::setw(30) << "you must wear sunscreen";
	}
	std::cout << '\n';

	//remove the date from the localtime
	std::string currentTime = currentTimeDate.substr(currentTimeDate.length() - 5);

	//write line three
	std::cout << std::left << std::setw(20) << asciiArt[currentCondition]["line3"].asString() << 
		std::left << std::setw(35) << currentTime << currentCountry << '\n';

	std::cout << '\n';

	file.close();



	return 0;
}