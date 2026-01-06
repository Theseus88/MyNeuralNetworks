// src/Theseus88/JsonUtilities/JsonUtilities.cpp
#include "../../../include/Theseus88/JsonUtilities/JsonUtilities.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {
    // JsonReader Class Private Member Functions
    void JsonReader::verifyFileStream() {
        if (!m_fileStream.good()) throw std::invalid_argument("Error: The file stream passed to JsonReader is not in a 'good' state for reading.");
    };
    char JsonReader::readCharacterAndTrackPosition() {
        char c;
        if (!m_fileStream.get(c)) return '\0'; // Return null char on EOF
        if (c == '\n') {
            m_lineNumber++;
            m_characterPosition = 0; // Reset character position on newline
        } else if (c != '\r') { // Ignore carriage return for position count
            m_characterPosition++;
        };
        return c;
    };
    void JsonReader::skipWhitespace() {
        char c;
        while (m_fileStream.peek() != EOF) {
            c = m_fileStream.peek(); // Peek at the character, but don't consume it yet
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                readCharacterAndTrackPosition(); // If it is whitespace, consume it using the tracking function
            } else {
                return; // Non-whitespace character found, leave it in the stream
            };
        };
    };
    void JsonReader::expectCharacter(const char expectedChar) {
        skipWhitespace();
        std::size_t errorLine = m_lineNumber;
        std::size_t errorChar = m_characterPosition + 1;
        char actualChar = readCharacterAndTrackPosition();
        if (actualChar == '\0') throw std::runtime_error("Error: Unexpected end of file. Expected JSON character '" + std::string(1, expectedChar) + "' (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        if (actualChar != expectedChar) throw std::runtime_error("Error: Expected JSON character '" + std::string(1, expectedChar) + "', but found '" + std::string(1, actualChar) + "'(Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");

    };
    std::string JsonReader::readQuotedString() {
        expectCharacter('"');
        std::string value;
        char c;
        while (true) {
            c = readCharacterAndTrackPosition();
            if (c == '\0') throw std::runtime_error("Error: Unexpected end of file while reading string value (Line: " + std::to_string(m_lineNumber) + ", Char: " + std::to_string(m_characterPosition) + ").");
            if (c == '"') break;
            if (c == '\\') {
                // Handle escape sequence
                std::size_t escapeLine = m_lineNumber;
                std::size_t escapeChar = m_characterPosition + 1;
                c = readCharacterAndTrackPosition();
                if (c == '\0') throw std::runtime_error("Error: Unexpected end of file while reading escape sequence (Line: " + std::to_string(escapeLine) + ", Char: " + std::to_string(escapeChar) + ").");
                // Decode common JSON escapes
                if (c == 'n') value += '\n';
                else if (c == 't') value += '\t';
                else if (c == 'r') value += '\r';
                else if (c == 'f') value += '\f';
                else if (c == 'b') value += '\b';
                else if (c == '"' || c == '\\' || c == '/') value += c;
                // NOTE: 'uXXXX' (unicode) is complex and omitted here for simplicity
                else throw std::runtime_error("Error: Invalid escape sequence '\\" + std::string(1, c) + "' (Line: " + std::to_string(escapeLine) + ", Char: " + std::to_string(escapeChar) + ").");
            } else {
                value += c;
            };
        };
        return value;
    };
    void JsonReader::expectKey(const std::string& expectedKey) {
        const std::string actualKey = std::move(readQuotedString());
        if (actualKey != expectedKey) throw std::runtime_error("Error: Expected key '" + expectedKey + "', but found '" + actualKey + "'.");
        expectCharacter(':');
    };
    void JsonReader::consumeComma() {
        skipWhitespace();
        char c = m_fileStream.peek();
        if (c == ',') {
            readCharacterAndTrackPosition();
            m_commaPresent = true;
        } else {
            m_commaPresent = false;
        };
    };

    // JsonReader Class Public Member Constructors
    JsonReader::JsonReader(const std::filesystem::path& path) : m_fileStream(path, std::ios::in), m_lineNumber(1), m_characterPosition(0), m_commaPresent(false) {
        if (!m_fileStream.is_open()) throw std::runtime_error("Error: Could not open file for reading: " + path.string() + "\n");
        m_fileStream.imbue(std::locale::classic());
    };

    // JsonReader Class Public Member Destructor
    JsonReader::~JsonReader() {
        if (m_fileStream.is_open()) m_fileStream.close();
    };

    // JsonReader Class Public Member General Functions
    bool JsonReader::commaPresent() {
        return m_commaPresent;
    };

    // JsonReader Class Public Member JSON Array Functions
    void JsonReader::readArrayStart() {
        verifyFileStream();
        expectCharacter('[');
    };
    void JsonReader::readArrayStart(const char* expectedKey) {
        verifyFileStream();
        expectKey(std::string(expectedKey));
        expectCharacter('[');
    };
    void JsonReader::readArrayStart(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        expectCharacter('[');
    };
    void JsonReader::readArrayEnd() {
        verifyFileStream();
        expectCharacter(']');
        consumeComma();
    };

    // JsonReader Class Public Member JSON Object Functions
    void JsonReader::readObjectStart() {
        verifyFileStream();
        expectCharacter('{');
    };
    void JsonReader::readObjectStart(const char* expectedKey) {
        verifyFileStream();
        expectKey(std::string(expectedKey));
        expectCharacter('{');
    };
    void JsonReader::readObjectStart(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        expectCharacter('{');
    };
    void JsonReader::readObjectEnd() {
        verifyFileStream();
        expectCharacter('}');
        consumeComma();
    };

    // JsonReader Class Public Member JSON Boolean Functions
    bool JsonReader::readBoolean() {
        verifyFileStream();
        skipWhitespace();
        std::size_t errorLine = m_lineNumber;
        std::size_t errorChar = m_characterPosition + 1;
        bool value;
        char c = m_fileStream.peek();
        if (c == 't') {            
            char buffer[5] = {0};
            for (int i = 0; i < 4; ++i) buffer[i] = readCharacterAndTrackPosition(); // Read "true" (4 characters)
            (std::string(buffer) == "true") ? value = true : throw std::runtime_error("Error: Expected JSON boolean value ('true'), but found '" + std::string(buffer) + "' (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        } else if (c == 'f') {
            char buffer[6] = {0};
            for (int i = 0; i < 5; ++i) buffer[i] = readCharacterAndTrackPosition(); // Read "false" (5 characters)
            (std::string(buffer) == "false") ? value = false : throw std::runtime_error("Error: Expected JSON boolean value ('false'), but found '" + std::string(buffer) + "' (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        } else {
            std::string actual = (c == EOF || c == '\0') ? "end of file" : ("'" + std::string(1, c) + "'");
            throw std::runtime_error("Error: Expected JSON boolean value ('true' or 'false'), but found " + actual + " (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        };
        consumeComma();
        return value;
    };
    bool JsonReader::readBoolean(const char* expectedKey) {
        verifyFileStream();
        expectKey(std::string(expectedKey));
        return readBoolean();
    };
    bool JsonReader::readBoolean(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        return readBoolean();
    };

    // JsonReader Class Public Member JSON Null Functions
    void JsonReader::readNull() {
        verifyFileStream();
        skipWhitespace();
        std::size_t errorLine = m_lineNumber;
        std::size_t errorChar = m_characterPosition + 1;
        char c = m_fileStream.peek();
        if (c == 'n') {
            char buffer[5] = {0};
            for (int i = 0; i < 4; ++i) buffer[i] = readCharacterAndTrackPosition(); // Read "null" (4 characters)
            if (std::string(buffer) != "null") throw std::runtime_error("Error: Expected JSON null value ('null'), but found '" + std::string(buffer) + "' (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        } else {
            std::string actual = (c == EOF || c == '\0') ? "end of file" : ("'" + std::string(1, c) + "'");
            throw std::runtime_error("Error: Expected JSON null value ('null'), but found " + actual + " (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        };
        consumeComma();
    };
    void JsonReader::readNull(const char* expectedKey) {
        readNull(std::string(expectedKey));
    };
    void JsonReader::readNull(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        readNull();
    };

    // JsonReader Class Public Member JSON Number Functions
    template <typename T> T JsonReader::readNumber() {
        verifyFileStream();
        skipWhitespace();
        std::size_t errorLine = m_lineNumber;
        std::size_t errorChar = m_characterPosition + 1;
        bool hasDecimal = false;
        bool hasExponent = false;
        std::string numberStr;
        char c = m_fileStream.peek();        
        if (c == '-' || (c >= '0' && c <= '9')) { // A number must start with a digit or a minus sign
            while (m_fileStream.peek() != EOF) { // Start consuming characters that form the number
                c = m_fileStream.peek();
                // Check if the character is part of the number
                if (c == '-' || (c >= '0' && c <= '9')) {
                    numberStr += readCharacterAndTrackPosition();
                } else if (c == '.') {
                    if (hasDecimal || hasExponent) throw std::runtime_error("Error: Invalid number format. Multiple decimal points or decimal after exponent (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(m_characterPosition + 1) + ").");
                    hasDecimal = true;
                    numberStr += readCharacterAndTrackPosition();
                } else if (c == 'e' || c == 'E') {
                    if (hasExponent) throw std::runtime_error("Error: Invalid number format. Multiple exponents (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(m_characterPosition + 1) + ").");
                    hasExponent = true;
                    numberStr += readCharacterAndTrackPosition();
                    c = m_fileStream.peek(); // Check for optional sign after 'e'
                    if (c == '+' || c == '-') numberStr += readCharacterAndTrackPosition();
                } else { // Non-number character found (e.g., comma, brace, or whitespace)
                    break;
                };
            };
        };
        if (numberStr.empty() || numberStr == "-") { // If no characters were consumed or just a solitary '-'
            std::string actual = (c == EOF || c == '\0') ? "end of file" : ("'" + std::string(1, c) + "'");
            throw std::runtime_error("Error: Expected JSON number, but found " + actual + " (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        };
        try { // Convert the string to the template type T
            long double ldValue = std::stold(numberStr); // Use std::stold (string to long double) for highest precision, then cast to T
            T value = static_cast<T>(ldValue);
            consumeComma();
            return value;
        } catch (const std::out_of_range& oor) {
            throw std::runtime_error("Error: Number '" + numberStr + "' is out of range for type T (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        } catch (const std::invalid_argument& ia) {
            throw std::runtime_error("Error: Invalid number format '" + numberStr + "' (Line: " + std::to_string(errorLine) + ", Char: " + std::to_string(errorChar) + ").");
        };

    };
    template <typename T> T JsonReader::readNumber(const char* expectedKey) {
        return readNumber<T>(std::string(expectedKey));
    };
    template <typename T> T JsonReader::readNumber(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        return readNumber<T>();
    };

    // JsonReader Class Public Member JSON String Functions
    std::string JsonReader::readString() {
        verifyFileStream();
        std::string value = std::move(readQuotedString());
        consumeComma();
        return value;
    };
    std::string JsonReader::readString(const char* expectedKey) {
        return readString(std::string(expectedKey));
    };
    std::string JsonReader::readString(const std::string& expectedKey) {
        verifyFileStream();
        expectKey(expectedKey);
        return readString();
    };

    // JsonReader Class Public Explicit Template Instantiations For Supported Number Types
    #define INSTANTIATE_JSON_READER_NUMBER(T) \
        template T JsonReader::readNumber<T>(); \
        template T JsonReader::readNumber<T>(const char* expectedKey); \
        template T JsonReader::readNumber<T>(const std::string& expectedKey)

    INSTANTIATE_JSON_READER_NUMBER(signed char);
    INSTANTIATE_JSON_READER_NUMBER(char);
    INSTANTIATE_JSON_READER_NUMBER(short);
    INSTANTIATE_JSON_READER_NUMBER(int);
    INSTANTIATE_JSON_READER_NUMBER(long);
    INSTANTIATE_JSON_READER_NUMBER(long long);
    INSTANTIATE_JSON_READER_NUMBER(unsigned char);
    INSTANTIATE_JSON_READER_NUMBER(unsigned short);
    INSTANTIATE_JSON_READER_NUMBER(unsigned int);
    INSTANTIATE_JSON_READER_NUMBER(unsigned long);
    INSTANTIATE_JSON_READER_NUMBER(unsigned long long);
    INSTANTIATE_JSON_READER_NUMBER(float);
    INSTANTIATE_JSON_READER_NUMBER(double);
    INSTANTIATE_JSON_READER_NUMBER(long double);

    #undef INSTANTIATE_JSON_READER_NUMBER

    // JsonWriter Class Private Member Functions
    void JsonWriter::increaseIndentation() {
        m_currentIndentationIndex++;
        if (m_currentIndentationIndex >= m_indentationCache.size()) m_indentationCache.emplace_back(m_indentationCache.size(), '\t');
    };
    void JsonWriter::decreaseIndentation() {
        if (m_currentIndentationIndex > 0) m_currentIndentationIndex--;
    };
    const std::string& JsonWriter::getIndentation() {
        return m_indentationCache[m_currentIndentationIndex];
    };
    void JsonWriter::validateWrite(const bool isKey, const bool isValue, const bool isStartScope, const bool isEndScope, const ScopeType typeToCheck) {
        if (!m_outputStream.good()) throw std::invalid_argument("Error: The output stream passed to JsonWriter is not in a 'good' state for writing.");
        ScopeType currentScope = m_scopeStack.top().type;
        // 1. VALIDATE KEY WRITES
        if (isKey) {
            if (currentScope != ScopeType::Object) throw std::runtime_error("Error: Cannot write a 'Key' unless inside an 'Object'.");
            if (m_expectingValue) throw std::runtime_error("Error: Cannot write a 'Key'; expecting a 'Value' for the previous 'Key'.");
        };
        // 2. VALIDATE VALUE WRITES (Strings, Numbers, Bools, or Start of Arrays/Objects)
        if (isValue) {
            if (currentScope == ScopeType::Object && !m_expectingValue) throw std::runtime_error("Error: Cannot write a 'Value' inside an 'Object' without a preceding 'Key'.");
            if (currentScope == ScopeType::Array && m_expectingValue) throw std::runtime_error("Error: 'Arrays' cannot contain 'Keys'.");
            if (currentScope == ScopeType::Root && m_scopeStack.size() == 1 && !isStartScope) throw std::runtime_error("Error: 'Root' element must be 'Object' or 'Array'.");
        };
        // 3. VALIDATE SCOPE CLOSING (EndObject / EndArray)
        if (isEndScope) {
            if (m_expectingValue) throw std::runtime_error("Error: Cannot close scope; waiting for a 'Value' for the last 'Key'.");
            if (currentScope != typeToCheck) {
                std::string expected = (typeToCheck == ScopeType::Object) ? "Object" : "Array";
                std::string actual = (currentScope == ScopeType::Object) ? "Object" : (currentScope == ScopeType::Array ? "Array" : "Root");
                throw std::runtime_error("Error: Mismatched scope. Tried to close '" + expected + "' but currently in '" + actual + "'.");
            };
            if (currentScope == ScopeType::Root) throw std::runtime_error("Error: Cannot close 'Root' scope.");
        };
    };
    void JsonWriter::handleCommaForArray() {
        ScopeState& current = m_scopeStack.top();
        if (current.type == ScopeType::Array) {
            if (current.itemCount > 0) {
                m_compactMode ? writeToBuffer(',') : writeToBuffer(",\n", 2);
            } else if (!m_compactMode) {
                writeToBuffer('\n');
                increaseIndentation();
            };
            current.itemCount++;
        };
    };
    const std::string JsonWriter::getQuotedString(const std::string& data) {
        std::string result;
        result.reserve(data.size() + 2);
        result += '"';
        for (char c : data) {
            switch (c) {
                case '"': result += "\\\""; break;
                case '\\': result += "\\\\"; break;
                case '\b': result += "\\b"; break;
                case '\f': result += "\\f"; break;
                case '\n': result += "\\n"; break;
                case '\r': result += "\\r"; break;
                case '\t': result += "\\t"; break;
                default: result += c; break;
            };
        };
        result += '"';
        return result;
    };
    template <std::size_t N> void JsonWriter::writeToBuffer(const char (&data)[N]) {
        writeToBuffer(data, N - 1);
    };
    void JsonWriter::writeToBuffer(const char* data, std::size_t size) {
        if (size == 0) return;
        if (m_bufferPosition + size > S_BUFFERSIZE) {
            flush();;
            if (size > S_BUFFERSIZE) {
                m_outputStream.write(data, size);
                return;
            };
        };
        std::copy(data, data + size, m_buffer.data() + m_bufferPosition);
        m_bufferPosition += size;
    };
    void JsonWriter::writeToBuffer(const std::string& data) {
        writeToBuffer(data.data(), data.size());
    };
    void JsonWriter::writeToBuffer(const char c) {
        writeToBuffer(&c, 1);
    };

    // JsonWriter Class Public Member Constructors
    JsonWriter::JsonWriter(std::ostream& outputStream, const bool compactMode) :
        m_outputStream(outputStream), m_bufferPosition(0), m_currentIndentationIndex(0), m_expectingValue(false) , m_compactMode(compactMode) {
        m_outputStream.rdbuf()->pubsetbuf(nullptr, 0);
        m_scopeStack.push({ScopeType::Root, 0});
        m_buffer.reserve(S_BUFFERSIZE);
        if (!compactMode) {
            m_indentationCache.reserve(S_PRECALCULATEDCACHERESERVE);
            for (size_t i = 0; i < S_PRECALCULATEDCACHERESERVE; i++) m_indentationCache.emplace_back(i, '\t');
        };
    };

    // JsonWriter Class Public Member Destructor
    JsonWriter::~JsonWriter() {
        flush();
    };

    // JsonWriter Class Public Member General Functions
    void JsonWriter::flush() {
        if (m_bufferPosition > 0) {
            m_outputStream.write(m_buffer.data(), m_bufferPosition);
            m_bufferPosition = 0;
        };
        m_outputStream.flush();
    };
    void JsonWriter::writeKeyOnly(const char* key, const bool needsIndentation) {
        writeKeyOnly(std::string(key), needsIndentation);
    };
    void JsonWriter::writeKeyOnly(const std::string& key, const bool needsIndentation) {
        validateWrite(true, false, false, false);
        ScopeState& current = m_scopeStack.top();
        if (current.itemCount > 0) {
            m_compactMode ? writeToBuffer(',') : writeToBuffer(",\n", 2);
        } else if (!m_compactMode) {
            writeToBuffer('\n');
            increaseIndentation();
        };
        current.itemCount++;
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        writeToBuffer(getQuotedString(key));
        m_compactMode ? writeToBuffer(':') : writeToBuffer(": ", 2);
        m_expectingValue = true;
    };

    // JsonWriter Class Public Member JSON Array Functions
    void JsonWriter::writeArrayStart(const bool needsIndentation) {
        validateWrite(false, true, true, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        writeToBuffer('[');
        m_expectingValue = false;
        m_scopeStack.push({ScopeType::Array, 0});
    };
    void JsonWriter::writeArrayStart(const char* key, const bool needsIndentation) {
        writeArrayStart(std::string(key), needsIndentation);
    };
    void JsonWriter::writeArrayStart(const std::string& key, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeArrayStart(false);
    };
    void JsonWriter::writeArrayEnd() {
        validateWrite(false, false, false, true, ScopeType::Array);
        ScopeState& current = m_scopeStack.top();
        if (current.itemCount > 0 && !m_compactMode) {
            decreaseIndentation();
            writeToBuffer('\n');
            writeToBuffer(getIndentation());
        };
        writeToBuffer(']');
        m_scopeStack.pop();
    };

    // JsonWriter Class Public Member JSON Object Functions
    void JsonWriter::writeObjectStart(const bool needsIndentation) {
        validateWrite(false, true, true, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        writeToBuffer('{');
        m_expectingValue = false;
        m_scopeStack.push({ScopeType::Object, 0});
    };
    void JsonWriter::writeObjectStart(const char* key, const bool needsIndentation) {
        writeObjectStart(std::string(key), needsIndentation);
    };
    void JsonWriter::writeObjectStart(const std::string& key, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeObjectStart(false);
    };
    void JsonWriter::writeObjectEnd() {
        validateWrite(false, false, false, true, ScopeType::Object);
        ScopeState& current = m_scopeStack.top();
        if (current.itemCount > 0 && !m_compactMode) {
            decreaseIndentation();
            writeToBuffer('\n');
            writeToBuffer(getIndentation());
        };
        writeToBuffer('}');
        m_scopeStack.pop();
    };

    // JsonWriter Class Public Member JSON Boolean Functions
    void JsonWriter::writeBoolean(const bool value, const bool needsIndentation) {
        validateWrite(false, true, false, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        value ? writeToBuffer("true", 4) : writeToBuffer("false", 5);
        m_expectingValue = false;
    };
    void JsonWriter::writeBoolean(const char* key, const bool value, const bool needsIndentation) {
        writeBoolean(std::string(key), value, needsIndentation);
    };
    void JsonWriter::writeBoolean(const std::string& key, const bool value, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeBoolean(value, false);
    };

    // JsonWriter Class Public Member JSON Null Functions
    void JsonWriter::writeNull(const bool needsIndentation) {
        validateWrite(false, true, false, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        writeToBuffer("null", 4);
        m_expectingValue = false;
    };
    void JsonWriter::writeNull(const char* key, const bool needsIndentation) {
        writeNull(std::string(key), needsIndentation);
    };
    void JsonWriter::writeNull(const std::string& key, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeNull(false);
    };

    // JsonWriter Class Public Member JSON Number Functions
    template <typename T> void JsonWriter::writeNumber(const T value, const bool needsIndentation) {
        validateWrite(false, true, false, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        char buffer[128];
        std::to_chars_result result;
        if constexpr (std::is_floating_point_v<T>) {
            result = std::to_chars(buffer, buffer + sizeof(buffer), value, std::chars_format::general, std::numeric_limits<T>::max_digits10);
        } else {
            result = std::to_chars(buffer, buffer + sizeof(buffer), value);
        };
        if (result.ec != std::errc()) throw std::runtime_error("Error: Failed to convert number to string.");
        writeToBuffer(buffer, result.ptr - buffer);
        m_expectingValue = false;
    };
    template <typename T> void JsonWriter::writeNumber(const char* key, const T value, const bool needsIndentation) {
        writeNumber<T>(std::string(key), value, needsIndentation);
    };
    template <typename T> void JsonWriter::writeNumber(const std::string& key, const T value, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeNumber<T>(value, false);
    };

    // JsonWriter Class Public Member JSON String Functions
    void JsonWriter::writeString(const char* value, const bool needsIndentation) {
        writeString(std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const std::string& value, const bool needsIndentation) {
        validateWrite(false, true, false, false);
        handleCommaForArray();
        if (needsIndentation && !m_compactMode) writeToBuffer(getIndentation());
        writeToBuffer(getQuotedString(value));
        m_expectingValue = false;
    };
    void JsonWriter::writeString(const std::string_view value, const bool needsIndentation) {
        writeString(std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const char* key, const char* value, const bool needsIndentation) {
        writeString(std::string(key), std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const char* key, const std::string& value, const bool needsIndentation) {
        writeString(std::string(key), value, needsIndentation);
    };
    void JsonWriter::writeString(const char* key, const std::string_view value, const bool needsIndentation) {
        writeString(std::string(key), std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const std::string& key, const char* value, const bool needsIndentation) {
        writeString(key, std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const std::string& key, const std::string& value, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeString(value, false);
    };
    void JsonWriter::writeString(const std::string& key, const std::string_view value, const bool needsIndentation) {
        writeKeyOnly(key, needsIndentation);
        writeString(std::string(value), false);
    };
    void JsonWriter::writeString(const std::string_view key, const char* value, const bool needsIndentation) {
        writeString(std::string(key), std::string(value), needsIndentation);
    };
    void JsonWriter::writeString(const std::string_view key, const std::string& value, const bool needsIndentation) {
        writeKeyOnly(std::string(key), needsIndentation);
        writeString(value, false);
    };
    void JsonWriter::writeString(const std::string_view key, const std::string_view value, const bool needsIndentation) {
        writeKeyOnly(std::string(key), needsIndentation);
        writeString(std::string(value), false);
    };    

    // JsonWriter Class Public Explicit Template Instantiations For Supported Number Types
    #define INSTANTIATE_JSON_WRITER_NUMBER(T) \
        template void JsonWriter::writeNumber<T>(const T value, const bool needsIndentation); \
        template void JsonWriter::writeNumber<T>(const char* key, const T value, const bool needsIndentation); \
        template void JsonWriter::writeNumber<T>(const std::string& key, const T value, const bool needsIndentation)

    INSTANTIATE_JSON_WRITER_NUMBER(signed char);
    INSTANTIATE_JSON_WRITER_NUMBER(char);
    INSTANTIATE_JSON_WRITER_NUMBER(short);
    INSTANTIATE_JSON_WRITER_NUMBER(int);
    INSTANTIATE_JSON_WRITER_NUMBER(long);
    INSTANTIATE_JSON_WRITER_NUMBER(long long);
    INSTANTIATE_JSON_WRITER_NUMBER(unsigned char);
    INSTANTIATE_JSON_WRITER_NUMBER(unsigned short);
    INSTANTIATE_JSON_WRITER_NUMBER(unsigned int);
    INSTANTIATE_JSON_WRITER_NUMBER(unsigned long);
    INSTANTIATE_JSON_WRITER_NUMBER(unsigned long long);
    INSTANTIATE_JSON_WRITER_NUMBER(float);
    INSTANTIATE_JSON_WRITER_NUMBER(double);
    INSTANTIATE_JSON_WRITER_NUMBER(long double);

    #undef INSTANTIATE_JSON_WRITER_NUMBER
};