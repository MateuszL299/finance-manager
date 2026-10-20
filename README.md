# Finance Manager

A simple personal finance manager written in C++ (console application).

## Current features

* Add transactions (income or expense) with amount, description and category
* Separate category sets for income and expenses
  * Expenses: food, fees, entertainment, other
  * Income: salary, gift, sale, other
* Display balance, total income and total expenses
* Display transaction history (amount, description, category, type)
* Input validation through a generic `readValidation<T>` template
  * accepts both `,` and `.` as the decimal separator
  * rejects trailing characters and out-of-range values
  * handles end of input with an exception
* Balance computed directly from the transaction list (single source of truth)
* Amounts displayed with fixed 2-decimal precision

## Technologies

* C++
* STL (`vector`, `string`, `function`, `sstream`, `iomanip`)
* Git / GitHub

## Version

**v0.2.1**

Split categories into separate sets for income and expenses. `addCategory` now picks the menu based on the transaction type.

## Status

🚧 Project in development.

## Planned features

* Dates
* Searching and filtering
* Saving data to files
* Statistics (e.g. spending per category)
* Deleting transactions
* Further code refactoring
* Database support