# Theseus88::JsonWriter: A High-Performance C++ JSON Writer

The `Theseus88::JsonWriter` class is designed for <b>maximum serialization speed and minimal memory footprint</b>, making it ideal for high-volume data tasks, such as saving large machine learning models, simulation results, or complex configuration files. It is specifically optimized to circumvent the common performance bottlenecks found in standard C++ stream-based JSON libraries.

## Key Features and Design Philosophy

The efficiency of this writer is based on three core optimizations:

#### <b>1. Zero-Allocation Number Serialization (Extreme Speed)</b>

The writer avoids the slow, locale-aware, and state-heavy C++ stream operators (<<) for numbers.

- <b>Method:</b> Numbers are converted to strings using the high-performance `std::to_chars` (C++17) function, which is guaranteed to be locale-agnostic and non-allocating, writing the result directly to a stack buffer.

- <b>Benefit:</b> This is the <b>fastest possible</b> way to convert numerical data into text in C++, crucial for applications with millions or billions of numerical entries.

#### <b>2. Custom Buffered Stream I/O (Minimizing OS Calls)</b>

The biggest bottleneck in any file writing application is the system call overhead when interacting with the Operating System (OS) for I/O.

- <b>Method:</b> The class implements a <b>large, custom memory buffer</b> (e.g., 128 KB) using `std::vector<char>`. All output (data, commas, quotes, indentation) is written to this buffer first.

- <b>Benefit:</b> Data is written to the file system in large, infrequent chunks rather than many small, expensive write calls, drastically reducing I/O overhead.

#### <b>3. Pre-Calculated Structure and Strings</b>

All non-data elements are handled to ensure zero-overhead formatting.

- <b>Indentation Cache:</b> Indentation strings (e.g., `"\t\t\t"`) are pre-calculated and stored upon construction, ensuring they are retrieved in <b>O(1) (constant time)</b>, avoiding repeated string concatenation during runtime.

- <b>Manual String Handling:</b> JSON keys and string values are escaped and quoted using optimized, buffer-aware logic, avoiding the overhead of stream wrappers like `std::quoted()`.

## Usage and Public API

The `JsonWriter` follows a declarative, stack-based structure, requiring the user to explicitly manage the start and end of objects (`{}`) and arrays (`[]`).

#### <b>1. Initialization and Destruction</b>

The JsonWriter automatically handles file opening and the final output buffer flush upon destruction (when it leaves scope).

<div align="center">

|<b>Function</b>|<b>Description</b>|
|:-|:-|
|`JsonWriter(const std::filesystem::path& path)`|Constructs the writer, opens the file, and initializes caches.|
|`~JsonWriter()`|<b>Crucially</b>, calls `flush()` to write any remaining buffered data to the disk.|
|`void flush()`|Forces the current memory buffer to be written to the file stream immediately.|

</div>

#### <b>2. Structural Control</b>

You must correctly pair the start and end calls to maintain valid JSON structure.

<div align="center">

|<b>Function</b>|<b>Output</b>|<b>Stack Effect</b>|
|:-|:-:|-:|
|`writeObjectStart()`|`{`|Pushes an `Object` onto the scope stack.|
|`writeObjectStart(const std::string& key)`|`"key": {`|Writes a key, then pushes an `Object`.|
|`writeObjectEnd()`|`}`|Pops the current scope.|
|`writeArrayStart()`|`[`|Pushes an `Array` onto the scope stack.|
|`writeArrayStart(const std::string& key)`|`"key": [`|Writes a key, then pushes an `Array`.|
|`writeArrayEnd()`|`]`|Pops the current scope.|

</div>

#### <b>3. Data Writing Functions</b>

All key-value functions handle comma (,), newline (\n), and indentation automatically based on the current scope.

- <b>Values Only (Inside an Array):</b>

```c++
writer.writeNumber(3.14159); // Output: 3.14159 (or , 3.14159)
writer.writeString("Hello"); // Output: "Hello" (or , "Hello")
```

- <b>Key-Value Pairs (Inside an Object):</b>

```c++
writer.writeBoolean("is_active", true); // Output: "is_active": true (or , "is_active": true)
writer.writeNull("last_update");        // Output: "last_update": null (or , "last_update": null)
```

<div align="center">

|<b>Data Type</b>|<b>Key-Value Overloads</b>|<b>Value-Only Overloads</b>|<b>Key Optimizations</b>|
|:-|:-:|:-:|:-:|
|<b>Boolean</b>|`writeBoolean(key, bool value)`|`writeBoolean(bool value)`|All `const char*` and `const std::string&` key overloads are provided.|
|<b>Null</b>|`writeNull(key)`|`writeNull()`||
|<b>Number</b>|`template <T> writeNumber(key, T value)`|`template <T> writeNumber(T value)`|Uses `std::to_chars` for maximum performance.|
|<b>String</b>|`writeString(key, value)`|`writeString(value)`|Uses manual escaping/quoting with the buffer.|

</div>

## Advanced: Compact Mode (Maximum I/O Speed)

For applications where readability is secondary to raw performance and file size, enable <b>Compact Mode</b>.

- <b>Method:</b> Pass `true` to the constructor.

```c++
Theseus88::JsonWriter writer("path/data.json", true);
```

- <b>Effect:</b> This setting disables <b>all</b> non-essential whitespace, including newlines, indentation, and the space after the colon, resulting in the smallest possible file size and fastest possible write time.

<div align="center">

|<b>Compact Mode</b>|<b>Comma/Newline</b>|<b>Key-Value Separator</b>|<b>Example Output (Same Data)</b>|
|:-|:-:|:-:|:-:|
|<b>Disabled (Default)</b>|`,\n`|`: `|`{\n\t"key": "value"\n}`|
|<b>Enabled</b>|`,`|`:`|`{"key":"value"}`|

</div>

## Important Note on Error Handling

Since this writer is designed for speed, it relies on the user to call the structural functions correctly. Calling `writeObjectEnd()` when an array is expected, or vice-versa, will result in <b>malformed JSON</b>. Errors are handled via exceptions (`std::runtime_error`) for critical stream or file issues.