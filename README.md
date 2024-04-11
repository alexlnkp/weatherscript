# WeatherScript - utility made for easy and fast yield of weather report for the area
It's using a fantastic website called [**wttr.in**](https://wttr.in) for the weather report itself

A [**JSON library**](https://github.com/nlohmann/json) is made by [@nlohmann](https://github.com/nlohmann)!

### Note
Website looks at your IP for the area you're located at. Using proxy or VPN will most likely yield incorrect results.

## Building
1. Clone the repository using `git clone https://github.com/alexlnkp/weatherscript.git`
2. `cd` into the cloned repository'
3. Make
   - Run `make SYSTEM=imperial` for Imperial system (Fahrenheit)
     
     OR
     
   - Run `make SYSTEM=metric` or simply `make` for Metric system (Celcius)

## Usage
- To get a weather forecast for the area determined by your IP - simply run the program.
- To get a weather forecast for a specific area - run the program with an argument (e.g. `Paris` for weather in Paris)

## Modifying
The code relies on simply requesting the webpage's contents directly from https://wttr.in/?format=j1.
It yields the JSON table that includes a **TON** of information about the weather, including `FeelsLike[C|F]`, `visibility`, `humidity`, and much more!
Therefore, you can very simply modify the code by adding or removing data you parse from the JSON.

For instance, here's how you yield the `FeelsLikeC`:
```cpp
std::string feelslike = j["current_condition"][0]["FeelsLikeC"];
```

Then, you can easily modify the print statement by adding this information. For example:
```cpp
std::cout << weather_symbol << ' ' << temp << TEMP_SYMBOL << '(' << feelslike << ')' << std::endl;
```
Will print out additionally the FeelsLike parameter for the temperature in the parenthesis.
