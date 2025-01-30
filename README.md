# DECIDE: Launch Interceptor Program with Modern Development Techniques
### Group 12's submission for Assignment 1 in DD2480 Software Engineering Fundamentals

C++ program that determines if countermeasures should be launched or not launched based on input information.

The specifications of the program are named in [decide.pdf](https://github.com/Teonord/DD2480-Group-12-DECIDE/blob/main/decide.pdf). In essence, the program takes an input containing parameters for launch choice, and a logic connector matrix. This, together with an amount of points (and the positions of named points) is put through 15 different tests, called Launch Intercept Conditions. The results of these are put through the logical connection matrix to get a preliminary unlocking matrix. This preliminary unlocking matrix is processed to become the final unlocking vector together with the preliminary unlocking vector which decides which rows of the preliminary unlocking matrix to keep track of. If entire final unlocking vector is true, then a launch can go ahead, otherwise it is stopped.  

## Structure
- **external**
    - Contains external code developed by other developers, namely the Catch2 framework for Unit Testing.
- **include**
    - Contains header files for our own developed code and program. 
- **src**
    - Contains the developed code, split into two files, one for atomic functions and one for the main function.
- **tests**
    - Contains the unit tests for all developed functions in the code. Uses the Catch2 framework from "external/"
- **Makefile**
	- Contains functions to easily compile and test the program, further usage explained below. 

## Changing Input
To change the input, being the parameters for the LICs, the LCM and the PUV, one can change the code of the `main` function in `src/main.cpp` before compiling. The methods set here decide whether the program will return YES or NO. 

## Running Code

This assumes you are running **Ubuntu** for your local computer. 

Clone the project

```bash
  git clone git@github.com:Teonord/DD2444-Project.git
```

Go to the project directory

```bash
  cd DD2444-Project
```

Install Dependencies

```bash
  sudo apt install make g++
```

Compile the files

```bash
  make 
```

Run the code

```bash
  ./build/decide
```

## Running Tests

Compile and run the tests

```bash
  make test
```

## Clean build folder 

Clean the compiled code build 

```bash
  make clean 
```

## Statement of Contributions

All members contributed with a good amount of work and a proactive response time - there have been no major problems within the group outside of the lack of one initial member. Even with the reduced workforce everyone has been efficient and fast to solve issues that have arrived, and have been effective at using the GitHub issue tracker to state and assign parts of development that has had to be done. We are proud of our creation, not only because the code works, but because the collaboration has been without major issues and each person has been allowed to build with their own strengths, while assisting others when things have gone awry. 

**All members** contributed with documentation and Pull Request checking/merging. 

**Rifat Kazi** - LIC's 0, 4, 9, 13, Essence document

**Teo Nordström** - LIC's 6, 8, 12, initial GitHub structure and Actions

**Linus Svensson** - LIC's 3, 7, 10, 11, 14, launch logic

**Syam Kumar Vemana** - LIC's 1, 2, 5, main function 

## Licenses

This project includes Catch2, which is licensed under the Boost Software License 1.0.
The full license text can be found in `external/Catch2_LICENSE.txt`.

The code developed in this project is licensed under the MIT License.
The full license text can be found in `LICENSE`.