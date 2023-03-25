//g++ ChatGPT3Client-curl.cc -lcurl

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string APIKey()
{
    std::string fileName = "APIKey.txt";
    std::ifstream file(fileName);

    if (file.is_open())
    {
        // Read contents of file into string variable
        std::string apiKey((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return apiKey;
    }
    else
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return "";
    }
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::cerr << "write_callback..." << std::endl;
    ((std::string*)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string generate_text(const std::string& prompt) {
    std::string response;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, "Content-Type: application/json");
        std::string apiTxt = "Authorization: Bearer " + APIKey();
        chunk = curl_slist_append(chunk, (apiTxt.c_str()));
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        json body = {
            {"prompt", prompt},
            {"temperature", 0.7},
            {"max_tokens", 60},
            {"stop", "\n"}
        };
        std::string body_str = body.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body_str.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/engines/davinci-codex/completions");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return response;
}

int main()
{
    // Prompt for user input
    std::string prompt;
    std::cout << "Enter a prompt for the OpenAI Chat GPT API: ";
    std::getline(std::cin, prompt);
    std::string response = generate_text(prompt);
    json result = json::parse(response);
    std::string generated_text = result["choices"][0]["text"];
    std::cout <<  generated_text << std::endl;
    return 0;
}
