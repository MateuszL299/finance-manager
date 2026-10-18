# Finance Manager

A simple personal finance manager written in C++.

## Current features

* Add income
* Add expenses
* Display balance
* Display total income and expenses
* Display transaction history
* Input validation
* Menu input validation
* Transaction structure using `struct`
* Transaction storage using `vector`
* Separate function for adding transactions
* Transaction categories (`enum class Category`) selected through a separate function
* Generic input validation function (`readValidation`) using a template and lambda expressions

## Technologies

* C++
* STL (`vector`, `string`, `functional`)
* Lambda expressions and function templates
* Git / GitHub

## Version

**v0.1.7**

Replaced repeated input validation loops with a generic `readValidation<T>` function. The validation condition is passed as a lambda expression, so each place in the code (menu, amount, category) defines only its own rule.

## Status

🚧 Project in development.

## Planned features

* Using transaction types (income / expense) in the `Transaction` struct
* Dates
* Searching and filtering
* Saving data to files
* Statistics
* Further code refactoring
* Database support