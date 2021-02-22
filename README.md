# clargs
A simple C++ command-line arguments parser
## Syntax for arguments:
```
  -<key> <value>     - This is used to pass in key-value pairs.
                     - <key> must start with an alphabet, and may be followed by alphanumeric characters of any length. 
                     - <key> may have underscores in it.
  --<name>           - This is used to pass in flags. 
                     - <name> must start with an alphabet, and may be followed by alphanumeric characters of any length.
  <value>            - this is used to pass in values that are not associated with any key
```
Below is an example of how to pass arguments from the command-line:
```
  ./program -somename somevalue --instant -somenumber 8 somenaked value "some other naked value" 3
```

## Accessing the arguments from a c++ program
Example:
```c++
  #include "clargs.cpp"
  #include <iostream>

  int main(int argc, char* const argv[]) {
      auto args = clargs::get_arguments(argc, argv);
      const auto& naked_values = args.get_naked_values();

      for (const auto& value : naked_values) {
          std::cout <<  "naked: " << value << "\n";
      }
      
      if (args.is_set("warnings_are_errors")) {
        // the flag is set
      }
      
      if (auto temp = args.get_value_of("some-key"); temp) {
        std::cout << "some-key = " << *temp << '\n';
      }
  }

```

## Note:
* Argument values are stored as std::string instances.
* This was tested with gcc version 10.0.1, using c++20. Efforts are being made to improve portability, especially with clang and previous versions of gcc.
