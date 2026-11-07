# Bad-Apple
A simple project displaying 'Bad Apple' in either the original .mp4 format or in ASCII. This project was inspired by other similar projects that can be found in GitHub.

### Dependencies & Versions
This project was written on MacOS with Apple Clang version 21.0.0 (clang-2100.3.34.2). With the following libraries and their respective version used.

| Dependency | Version / Build |
| :--- | :--- |
| **SDL3** | `3.4.14` (Headers: `3.4.18`) |
| **libavcodec** | `63.1.102` |
| **libavformat** | `63.1.102` |
| **libswscale** | `10.1.102` |

## Note
The .mp4 and .mp3 were retreived from the following GitHub repo: [Bad-Apple](https://github.com/rkk-2s/bad-apple)

## How to run
First clone the repp

```zsh

git clone https://github.com/Kv1st3n/Bad-Apple.git

```

Then make sure that you are in 'Bad-Apple' folder / directory and run following commands:

```zsh

cmake -B build

cmake --build build 

./build/Bad_Apple

```

## General Info
When you start running, the program will display the regular .mp4 video, but you can switch to ASCII mode using the '2' key, and to change back click on the '1' key. The spacebar will pause the display and clicking 'S' will change the ASCII mode. The change in ASCII mode will either display the background with ASCII character(s) with characters using empty space or vice versa.