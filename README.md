![MetalHead](docs/assets/metalhead.png)

What is MetalHead and the short story behind the name

# System Block Diagram
![Block Diagram](docs/assets/block-diagram.png)

---

# Firmware
## Interface Board
To setup a development environment:
Download & install [PlatformIO](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html)
* Download and install [CLion](https://www.jetbrains.com/clion/)
  * Alternative: [Microsoft Visual Studio Code](https://apps.microsoft.com/detail/xp9khm4bk9fz7q?query=python&hl=en-US&gl=US)
* Install [PlatformIO CLion plugin](https://plugins.jetbrains.com/plugin/13922-platformio-for-clion)
  * Alternative: [Microsoft Visual Studio Code PlatformIO plugin](https://platformio.org/install/ide?install=vscode)
### Arduino API
To develop the Arduino API:
* Open MetalHead/firmware/interface-board in your preferred IDE (CLion / VSCode)
### Zephyr RTOS
* It's preferred to use CLion, 
* [Download](https://apps.microsoft.com/search?query=python&hl=en-US&gl=US) and install the latest version of python
* Verify python is accessible via cmd:
  * `python -V`
* Create python virtual environment
  * `cd MetalHead\firmware\interface-board-zephyr`
  * `python -m venv .\.venv`
* Enter python virtual environment
  * `.\.venv\Scripts\activate.bat`
* Update pip (optional)
  * `python.exe -m pip install --upgrade pip`
* Install west
  * `pip install west`
* Initiate the Zephyr-RTOS project
  * `west init`
* Pull the latest commits from Zephyr's github
  * `west update`
* Export a Zephyr CMake package. This allows CMake to automatically load boilerplate code required for building Zephyr applications.
  * `west zephyr-export`
  * > See: Computer\HKEY_CURRENT_USER\Software\Kitware\CMake\Packages
* Install additional packages need by west
  * `west packages pip --install`
* Install the Zephyr SDK
  * `west sdk install`
* Create a folder for bossac: C:\Program Files (x86)\BOSSA
* Copy bossac.exe to C:\Program Files (x86)\BOSSA
* Add C:\Program Files (x86)\BOSSA to PATH environment (use `sysdm.cpl`)
  * Make sure you can access bossac.exe. Open a new terminal and run: `bossac --help`
* Start CLion
* Open our project: MetalHead\firmware\interface-board-zephyr\application
* You will more than likely need to adjust the COM port for bossac to upload the firmware. In CLion, this is achieved by editing the West configuration under 'Flash options'

To build a pristine copy of the firmware binary:

  * `cd MetalHead\firmware\interface-board-zephyr`
  * `rmdir /q /s application\build`
  * Go back to CLion and reload West
  * Build, flash, etc

We are using [ArduinoJson](https://arduinojson.org/) to serialize and deserialize json objects between the Interface
Board and HMI. All JSON objects will have `ObjectType` to identify the type of message being transferred or received.
This will make it easy to deserialize a JSON object into one of our own objects.
### Recipe
The following JSON object is used inside of `PresetRecipes`
```json
{
  "ObjectType": "Recipe",
  "Lines": [[0,0,0,0,0], [], [], [], [], ...],
  "rebarSize": 0,
  "name": "12x12 Square",
  "desc": "A basic 1 x 1' square stirrup",
  "note": "Add some compensation for #5 or #6",
  "date": 1739089653
}
```
### PresetRecipes
The following JSON object is transferred to the HMI from the Interface Board via UART.
This object holds all preset recipes saved in the EEPROM.
> We could also implement this into the HMI application 
```json
{
  "ObjectType": "PresetRecipes",
  "NumofRecipes": 16,
  "Recipes": [Recipe{}, Recipe{}, ...]
}
```
### PresetRecipe
The following JSON object is transferred to the Interface Board from the HMI UART.
This object holds a recipe that the operator wishes to save.
```json
{
  "ObjectType": "PresetRecipe",
  "Recipe": {}
}
```
### ManualRecipe
The following JSON object is transferred to the Interface Board from the HMI via UART.
This object instructs the interface to make the following recipe.
```json
{
  "ObjectType": "ManualRecipe",
  "Recipe": {}
}
```
### StopEvent
The following JSON object is transferred to the HMI from the Interface Board via UART.
This object instructs the HMI to display a message. There are currently two types of events.
```json
{
  "ObjectType": "StopEvent",
  "Event": "EStop"
}
```
```json
{
  "ObjectType": "StopEvent",
  "Event": "Fuse"
}
```
---
## Keypad
Similarly to the Interface Board, we are using [ArduinoJson](https://arduinojson.org/) to serialize and deserialize
json objects between the Keypad and HMI
### KeypadEvent - Structure
KeypadEvent is sent to the Interface Board via UART when the operator hits a key. Multiple KeypadEvent[s] will be sent
to the Interface Board if the operator depresses a key for longer than a typical keystroke. Below are a few examples of
what a KeypadEvent structure sent via UART to the Interface Board would look like. Since the Keypad communicates to the
HMI uni-directionally on its own separate UART channel, we will not include `ObjectType` in the JSON object.

```json
{
  "Key": "DISPLAY"
}
```
```json
{
  "Key": "COMP"
}
```
```json
{
  "Key": "UPARROW"
}
```
### Key Mapping
Because we are going to be using two 16 bit I2C GPIO expanders, we are going to map each key to a specific bit on a I2C 
address.

| I2C Read<br/>Address | Bit | Key          |
|----------------------|:---:|--------------|
| 0x41                 |  0  | Display      |
| 0x41                 |  1  | Comp         |
| 0x41                 |  3  | Infeed       |
| 0x41                 |  4  | Head Pos     |
| 0x41                 |  5  | Form Tool In |
| 0x41                 |  6  | Shear        |
| 0x41                 |  7  | Pause        |
| 0x41                 |  8  | Run          |
| 0x41                 |  9  | Up           |
| 0x41                 | 10  | Enter        |
| 0x41                 | 11  | 1            |
| 0x41                 | 12  | 2            |
| 0x41                 | 13  | 3            |
| 0x41                 | 14  | Plus         |
| 0x41                 | 15  | Left         |
| 0x43                 |  0  | Menu         |
| 0x43                 |  1  | Right        |
| 0x43                 |  3  | 4            |
| 0x43                 |  4  | 5            |
| 0x43                 |  5  | 6            |
| 0x43                 |  6  | Minus        |
| 0x43                 |  7  | Memory       |
| 0x43                 |  8  | Down         |
| 0x43                 |  9  | Decimal      |
| 0x43                 | 10  | 7            |
| 0x43                 | 11  | 8            |
| 0x43                 | 12  | 9            |
| 0x43                 | 13  | 0            |

---

# Software
## HMI
### KeypadEvent
When the HMI receives a `KeypadEvent` from the keypad, the object is forwarded to the Interface Board for processing.
The following is an example of how a `KeypadEvent` looks like when the HMI sends it to the Interface Board.
```json
{
  "ObjectType": "KeypadEvent",
  "Event": "SHEAR"
}
```
```json
{
  "ObjectType": "KeypadEvent",
  "Event": "PAUSE"
}
```
The following keys are forwarded to the Interface Board from the HMI:
* FORM TOOL IN
* SHEAR
* PAUSE
* RUN

---

# Hardware
## Interface Board
A brief explanation of what this does and how it achieves it. Mention the added SBC for the GUI.
## Keypad
A brief explanation of what this does and how it achieves it. 
## SBC