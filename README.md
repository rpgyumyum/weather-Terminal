# Terminal Applications

- This is a collection of small cli programms with different utilites. 
- None of the Applications are complex nor are they bug free.


## List of Applications
- **todo**
    - A simple cli todo list
    - Usage: 
    ```bash
    todo --> display list
    todo -add "do smth"
    todo -done 1
    todo -mod 1 "do smth and do smth different"
    ```
  - we read and write everything from "~/Documents/todo.txt"(just edit the sourcecode if you want to safe it somewhere else)

- **weather**
    - Display weather information with ASCII art gathered from an API 
    - Usage:
    ```bash
    weather
    ```
    - Dependencies:
        - curl
        - jsoncpp

## Installation

Compile The projects with make by doing ```make``` + ```<proect name>```.  
Dependencies should be listed above in the list of applications or the compiler is just gonna scream at you.   

After compiling just add the binary to $PATH

