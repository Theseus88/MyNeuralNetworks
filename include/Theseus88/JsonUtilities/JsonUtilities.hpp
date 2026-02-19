// include/Theseus88/JsonUtilities/JsonUtilities.hpp
#ifndef THESEUS88_JSONUTILITIES_HPP
#define THESEUS88_JSONUTILITIES_HPP

// ADD COMMENT HERE LATER
#include <algorithm>    // std::string(count, char)
#include <charconv>     // std::to_chars, std::chars_format
#include <cstddef>      // std::size_t
//#include <cstdint>      // std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
#include <filesystem>   // std::filesystem
#include <fstream>      // std::fstream
//#include <iomanip>      // std::quoted, std::setprecision, std::fixed
#include <limits>       // std::numeric_limits
#include <ostream>      // std::ostream
#include <stack>        // std::stack
#include <stdexcept>    // std::invalid_argument, std::runtime_error
#include <string>       // std::string
#include <vector>       // std::vector

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // Shared Enums for Reader and Writer
    enum class JsonScopeType { Root, Object, Array };

    // JSON Reader Class
    class JsonReader {
    private:
        // Private Structs
        struct ScopeState { JsonScopeType type; std::size_t itemCount = 0; };

        // Private Member Variables
        std::istream& m_inputStream;
        std::size_t m_lineNumber;
        std::size_t m_characterPosition;
        std::stack<ScopeState> m_scopeStack;

        // Private Member Functions
        void verifyInputStream();
        char readCharacterAndTrackPosition();
        void skipWhitespace();
        char peekCharacter();
        void expectCharacter(const char expectedCharacter);
        std::string readQuotedString();
        void expectKey(const std::string& expectedKey);
        void prepareToReadKey();
        void prepareToReadValue();
        bool parseBoolean();
        void parseNull();
        template <typename T> T parseNumber();

    public:
        // Public Member Constructors
        JsonReader() = delete;
        JsonReader(std::istream& inputStream);

        // Public Member Destructor
        ~JsonReader();

        // Public Member Assignment Operators
        JsonReader& operator=(const JsonReader& other) = delete;
        JsonReader& operator=(JsonReader&& other) = delete;

        // Public Member General Functions
        bool hasNext();

        // Public Member JSON Array Functions
        void readArrayStart();
        void readArrayStart(const char* expectedKey);
        void readArrayStart(const std::string& expectedKey);
        void readArrayEnd();

        // Public Member JSON Object Functions
        void readObjectStart();
        void readObjectStart(const char* expectedKey);
        void readObjectStart(const std::string& expectedKey);
        void readObjectEnd();

        // Public Member JSON Boolean Functions
        bool readBoolean();
        bool readBoolean(const char* expectedKey);
        bool readBoolean(const std::string& expectedKey);

        // Public Member JSON Null Functionss
        void readNull();
        void readNull(const char* expectedKey);
        void readNull(const std::string& expectedKey);

        // Public Member JSON Number Functions
        template <typename T> T readNumber();
        template <typename T> T readNumber(const char* expectedKey);
        template <typename T> T readNumber(const std::string& expectedKey);

        // Public Member JSON String Functions
        std::string readString();
        std::string readString(const char* expectedKey);
        std::string readString(const std::string& expectedKey);
    };

    // JSON Writer Class
    class JsonWriter {
    private:
        // Private Structs
        struct ScopeState { JsonScopeType type; std::size_t itemCount = 0; };

        // Private Static Constants
        static constexpr std::size_t S_BUFFERSIZE = 128 * 1024;
        static constexpr std::size_t S_PRECALCULATEDCACHERESERVE = 20;

        // Private Member Variables
        std::ostream& m_outputStream;
        std::vector<char> m_buffer;
        std::size_t m_bufferPosition;
        std::vector<std::string> m_indentationCache;
        std::size_t m_currentIndentationIndex;
        std::stack<ScopeState> m_scopeStack;
        bool m_expectingValue;
        bool m_compactMode;

        // Private Member Functions
        void increaseIndentation();
        void decreaseIndentation();
        const std::string& getIndentation();
        void validateWrite(const bool isKey, const bool isValue, const bool isStartScope, const bool isEndScope, const JsonScopeType typeToCheck = JsonScopeType::Root);
        void handleCommaForArray();
        const std::string getQuotedString(const std::string& data);
        template <std::size_t N> void writeToBuffer(const char (&data)[N]);
        void writeToBuffer(const char* data, std::size_t size);
        void writeToBuffer(const std::string& data);
        void writeToBuffer(const char c);

    public:
        // Public Member Constructors
        JsonWriter() = delete;
        JsonWriter(std::ostream& outputStream, const bool compactMode = false);

        // Public Member Destructor
        ~JsonWriter();
 
        // Public Member Assignment Operators
        JsonWriter& operator=(const JsonWriter& other) = delete;
        JsonWriter& operator=(JsonWriter&& other) = delete;

        // Public Member General Functions
        void flush();
        void writeKeyOnly(const char* key, const bool needsIndentation = true);
        void writeKeyOnly(const std::string& key, const bool needsIndentation = true);
    
        // Public Member JSON Array Functions
        void writeArrayStart(const bool needsIndentation = true);
        void writeArrayStart(const char* key, const bool needsIndentation = true);
        void writeArrayStart(const std::string& key, const bool needsIndentation = true);
        void writeArrayEnd();

        // Public Member JSON Object Functions
        void writeObjectStart(const bool needsIndentation = true);
        void writeObjectStart(const char* key, const bool needsIndentation = true);
        void writeObjectStart(const std::string& key, const bool needsIndentation = true);
        void writeObjectEnd();

        // Public Member JSON Boolean Functions
        void writeBoolean(const bool value, const bool needsIndentation = true);
        void writeBoolean(const char* key, const bool value, const bool needsIndentation = true);
        void writeBoolean(const std::string& key, const bool value, const bool needsIndentation = true);

        // Public Member JSON Null Functions
        void writeNull(const bool needsIndentation = true);
        void writeNull(const char* key, const bool needsIndentation = true);
        void writeNull(const std::string& key, const bool needsIndentation = true);

        // Public Member JSON Number Functions
        template <typename T> void writeNumber(const T value, const bool needsIndentation = true);
        template <typename T> void writeNumber(const char* key, const T value, const bool needsIndentation = true);
        template <typename T> void writeNumber(const std::string& key, const T value, const bool needsIndentation = true);

        // Public Member JSON String Functions
        void writeString(const char* value, const bool needsIndentation = true);
        void writeString(const std::string& value, const bool needsIndentation = true);
        void writeString(const std::string_view value, const bool needsIndentation = true);
        void writeString(const char* key, const char* value, const bool needsIndentation = true);
        void writeString(const char* key, const std::string& value, const bool needsIndentation = true);
        void writeString(const char* key, const std::string_view value, const bool needsIndentation = true);
        void writeString(const std::string& key, const char* value, const bool needsIndentation = true);
        void writeString(const std::string& key, const std::string& value, const bool needsIndentation = true);
        void writeString(const std::string& key, const std::string_view value, const bool needsIndentation = true);
        void writeString(const std::string_view key, const char* value, const bool needsIndentation = true);
        void writeString(const std::string_view key, const std::string& value, const bool needsIndentation = true);
        void writeString(const std::string_view key, const std::string_view value, const bool needsIndentation = true);
    };
};

#endif // THESEUS88_JSONUTILITIES_HPP