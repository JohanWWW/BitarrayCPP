# Bitarray

Bitarray provides a memory efficient way of storing an arbitrarily sized set of individual bits. The data structure uses unsigned chars internally to store each bit which is more efficient than storing booleans in an array due to `bool` needing to allocate 8 bits and wasting 7.

## Example

### Allocation
```cpp
// Create an array of 8 bits
bitarray bits {0,0,0,0,0,0,0,0};
// or
bitarray bits {false,false,false,false,false,false,false,false};
// or
bitarray bits(8);
```

### Modify Bits
```cpp
// Get bit at index 3
bool b = bits[3];

// Set bit at index 7
bits[7] = 1;
// or
bits[7] = true;
```

### Iterate
```cpp
for (int i = 0; i < bits.length(); i++)
    std::cout << (int)bits[i];

// or

for (bitarray::iterator it = bits.begin(); i != bits.end(); i++)
    std::cout << (int)*it;

// or

for (bool bit : bits)
    std::cout << bit;
```