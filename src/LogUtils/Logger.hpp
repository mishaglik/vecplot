#ifndef LOGUTILS_LOGGER_HPP
#define LOGUTILS_LOGGER_HPP

#include <cstdint>
#include <cstdlib>

namespace mlg {
    
    class Logger
    {
        using manip_f = void(*)(Logger&);
    
    public:
        enum class LogLevel{
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

        enum class CoStyle{
        Reset       = 0,

        Bold        = 1,
        Underline   = 4,
        Inverse     = 7,

        UnBold      = 21,
        UnUnderline = 24,
        UnInverse   = 27,

        Black       = 30,
        Red         = 31,
        Green       = 32,
        Yellow      = 33,
        Blue        = 34,
        Mangenta    = 35,
        Cyan        = 36,
        White       = 37,

        BBlack      = 40,
        BRed        = 41,
        BGreen      = 42,
        BYellow     = 43,
        BBlue       = 44,
        BMangenta   = 45,
        BCyan       = 46,
        BWhite      = 47,
    };

    protected:

        uint64_t verbosity_ = 0;
        LogLevel logLevel_   = LogLevel::WARNING;
        LogLevel abortLevel_ = LogLevel::WARNING;
        LogLevel curLevel_   = LogLevel::DEBUG;
        uint64_t ident_ = 0;
        uint64_t identSize_ = 4;

        uint64_t outputFlags_ = 0;
        uint64_t widht_ = 0;

    public:
        enum FmtFlag : uint64_t
        {
            Dec = 0x0,
            Hex = 0x1,
            Oct = 0x2,
            Bin = 0x3,
            ShowBase = 0x4,
        };

        enum FmtMask : uint64_t
        {
            BaseMask     = 0x3,
            ShowBaseMask = 0x4,
        };
        


    
        /**
         * @brief Set ] FmtFlags
         * 
         * @param flag - new flags
         * @param mask - mask of flags
         */
        virtual void setFmtFlags(FmtFlag flag, FmtMask mask);

        /**
         * @brief Set width 
         * 
         * @param w - width
         */
        virtual void setWidth(uint64_t w);

        /**
         * @brief Set the Ident size 
         * 
         * @param identSize - new identSize
         */
        void setIdentSize(uint64_t identSize);

        /**
         * @brief Increase ident's count
         * 
         * @param idents - idents.
         */
        void addIdent(uint64_t idents = 1);
        
        /**
         * @brief Decrease number of ident's
         * 
         * @param idents - number idents to decrease
         */
        void remIdent(uint64_t idents = 1);

        /**
         * @brief Set the Log Level
         * 
         * @param logLevel - new LogLevel
         */
        void setLogLevel(LogLevel logLevel);

        /**
         * @brief Set the Abort Level object
         * 
         * @param abortLevel - new abort level
         */
        void setAbortLevel(LogLevel abortLevel);

        /**
         * @brief Set the verbosity
         * 
         * @param verbosity - new Verbosity 
         */
        void setVerbosity(uint64_t verbosity);

        /**
         * @brief Alter verbosity (bitwise or)
         * 
         * @param verbosity - mask to alter
         */
        void addVerbosity(uint64_t verbosity);

        /**
         * @brief Remove verbosity (bitwise nand)
         * 
         * @param verbosity - mask to remove
         */
        void remVerbosity(uint64_t verbosity);

        /**
         * @brief Destroy the Logger object
         * 
         */
        virtual ~Logger() = default;


        virtual Logger& operator<<(char x)     = 0;
        
        virtual Logger& operator<<(uint32_t x) = 0;
        virtual Logger& operator<<(int32_t  x) = 0;
        virtual Logger& operator<<(uint64_t x) = 0;
        virtual Logger& operator<<(int64_t  x) = 0;
        virtual Logger& operator<<(double  x)  = 0;

        virtual Logger& operator<<(const char* x) = 0;
        virtual Logger& operator<<(const void* x) = 0;

        /**
         * @brief Flush output.
         * 
         */
        virtual void flush()   = 0;
        
        /**
         * @brief Start new line
         * 
         */
        virtual void newline() = 0;

        class LogAborted{};
        /**
         * @brief Ends current phrase.
         * 
         */
        virtual void endline()
        {
            newline();
            if(curLevel_ > abortLevel_)
            {
                throw LogAborted{};
            }
        }

        virtual void printWelcome  () = 0;
        virtual void printFinish   () = 0;
        virtual void printLineStart() = 0;

        virtual Logger& operator<<(CoStyle newStyle) = 0;

        virtual Logger& operator<<(manip_f manip) { manip(*this); return *this;}

        Logger& debug();
        Logger& info();
        Logger& warning();
        Logger& error();
        Logger& fatal();

    };

    void endl(Logger& log);
    void newl(Logger& log);

    void hex(Logger& log);
    void dec(Logger& log);
    void oct(Logger& log);
    // void bin(Logger& log); //TODO: Implement binary output (bitset)

    template<uint64_t w>      //Take only const nums. Sorry :(; XXX: Later: Rework it to non const.
    void setWidth(Logger& log)
    {
        log.setWidth(w);
    }

}

#endif /* LOGUTILS_LOGGER_HPP */
