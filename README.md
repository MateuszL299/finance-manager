# Finance Manager

A simple personal finance manager written in C++.

## Current features

* Add transactions (income / expense)
* Transaction types using `enum class Type`
* Categories using `enum class Category` (food, fees, entertainment, other)
* Display balance, total income and total expenses (calculated from the transaction list)
* Display transaction history (amount, description, category, type)
* Generic input validation (`readValidation` template with a validation lambda)
* Input read line by line, so invalid input like `10abc` is rejected
* Comma accepted as a decimal separator (`10,50`)
* Amounts displayed with two decimal places
* Safe handling of end of input (Ctrl+Z / Ctrl+D)
* Transaction structure using `struct`
* Transaction storage using `vector`

## Technologies

* C++
* STL (`vector`, `string`, `functional`, `sstream`, `iomanip`)
* Git / GitHub

## Version

**v0.2**

Added transaction types, balance calculated from the transaction list, rewritten input validation (whole-line reading, comma support, end of input handling) and amount formatting.

## Status

🚧 Project in development.

## Planned features

* Dates
* Searching and filtering
* Saving data to files
* Statistics
* Further code refactoring
* Database support