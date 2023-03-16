//g++ -fpermissive ChatGPT3Client-cpprest.cc -o ChatGPT-3-Client -lcpprest -pthread -lcrypto -lssl

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace web;
using namespace web::http;
using namespace web::http::client;

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

int main() {
  // Define the API endpoint URL and authorization key
  std::string url = "https://api.openai.com/v1/engines/davinci-codex/completions";
  std::string api_key = APIKey();

  // Prompt for user input
  std::string prompt;
  std::cout << "Enter a prompt for the OpenAI Chat GPT API: ";
  std::getline(std::cin, prompt);

  // Create a new HTTP client and request object
  http_client client(url);
  http_request request(methods::POST);

  // Set the request headers and body
  request.headers().add("Content-Type", "application/json");
  request.headers().add("Authorization", "Bearer " + api_key);
  
  json::value body;
  body["prompt"] = json::value::string(prompt);
  body["max_tokens"] = 100;
  body["temperature"] = 0.5;
  request.set_body(body);

  // Send the request and receive the response
  http_response response = client.request(request).get();

  // Check if the response status code indicates success
  if (response.status_code() == status_codes::OK)
  {
    // Parse the response body JSON and extract the generated text
    json::value response_body  = response.extract_json().get();
    std::string generated_text = response_body["choices"][0]["text"].as_string();

    // Print the generated text
    std::cout << "OpenAI Chat GPT API response: " << generated_text << std::endl;
  }
  else
  {
    // Print the error message if the request was not successful
    std::cout << "OpenAI Chat GPT API error: " << response.reason_phrase() << std::endl;
  }

  return 0;
}


