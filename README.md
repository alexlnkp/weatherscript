[![C/C++ CI](https://github.com/alexlnkp/weatherscript/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/alexlnkp/weatherscript/actions/workflows/c-cpp.yml)
# WeatherScript - utility made for easy and fast yield of weather report for the area
It's using a fantastic website called [**wttr.in**](https://wttr.in) for the weather report itself

A [**JSON library**](https://github.com/nlohmann/json) is made by [@nlohmann](https://github.com/nlohmann)!

The program is based off a python script by [@SolDoesTech](https://github.com/SolDoesTech), [SolDoesTech/HyprV/waybar/scripts/waybar-wttr.py](https://github.com/SolDoesTech/HyprV4/blob/c81cf650443d680bf7a589de6128d01020dd1bc6/HyprV/waybar/scripts/waybar-wttr.py)


### Note
Website looks at your IP for the area you're located at. Using proxy or VPN will most likely yield incorrect results unless you specify location as an argument. For instruction look at the [**Usage**](https://github.com/alexlnkp/weatherscript/tree/master#usage) section.

## Dependencies
- Using your package manager install curl developer package.
   - Ubuntu: `sudo apt-get install libcurl4-openssl-dev`
   - Arch: `sudo pacman -S curl`

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
It yields the JSON table that includes a **TON** of information about the weather, including `FeelsLike[C|F]`, `visibility[Miles]`, `humidity`, and much more!
Therefore, you can very simply modify the code by adding or removing data you parse from the JSON.

For instance, here's how you yield the `visibility` in meters:

- `src/main.cpp`**:**
```cpp
std::string visibility = json_res["current_condition"][0]["visibility"];
```

Then, you can easily modify the `std::cout` by adding this information. For example:

- `src/main.cpp`**:**
```cpp
std::cout << weather_symbol << ' ' << temp << TEMP_SYMBOL << '(' << visibility << ')' << std::endl;
```

Will print out additionally the Visibility parameter for the temperature in the parenthesis.

You could also make code more versatile by looking at the top of the `main.cpp` and changing the fields to yield information from according to the system the app is built for.

So, you could add a new define at the top, like so:

- `src/main.cpp`**:**
```cpp
#ifdef IMPERIAL
	#define TEMP_SYMBOL "°F"
	#define TEMP_TYPE "temp_F"
  #define VISIBILITY "visibilityMiles" // Our new data
#else
	#define TEMP_SYMBOL "°C"
	#define TEMP_TYPE "temp_C"
  #define VISIBILITY "visibility" // Our new data
#endif
```

This way, the data to yield is decided at the compile time by the `SYSTEM` variable you pass to `make`.
If you make with `SYSTEM=imperial` - the information you yield will be in an imperial system.
In other words, you will yield `visibilityMiles` data instead of `visibility` (meters).
