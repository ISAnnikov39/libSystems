#include "logger.h"

Logger::Logger(const QString& filename)
{
    logFile.open(filename.toStdString(), std::ios::app);
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void Logger::log(Level level, const QString& message)
{
    QString levelStr = levelToString(level);
    QString timeStr = currentDateTime();
    writeLogToConsole(timeStr, levelStr, message, level);
    writeLogToFile(timeStr, levelStr, message);
}

template <typename T>
void Logger::log(Level level, const QString& message, const T& value)
{
    std::stringstream ss;
    formatMessage(ss, message, value);
    log(level, ss.str().c_str());
}

QString Logger::levelToString(Level level) const
{
    switch (level)
    {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

QString Logger::currentDateTime() const
{
    time_t now = time(0);
    char buffer[80];
    struct tm tstruct;
    tstruct = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &tstruct);
    return buffer;
}

void Logger::writeLogToConsole(const QString& timeStr, const QString& levelStr, const QString& message, Level level) const
{
    std::string colorCode;

    switch (level)
    {
        case INFO: colorCode = "\033[32m"; // Зеленый
            break;
        case WARNING: colorCode = "\033[33m"; // Желтый
            break;
        case ERROR: colorCode = "\033[31m"; // Красный
            break;
    }

    std::cout << colorCode << timeStr.toStdString() << " [" << levelStr.toStdString() << "] " << message.toStdString() << "\033[0m" << std::endl;
}

void Logger::writeLogToFile(const QString& timeStr, const QString& levelStr, const QString& message)
{
    if (logFile.is_open())
    {
        logFile << timeStr.toStdString() << " [" << levelStr.toStdString() << "] " << message.toStdString() << std::endl;
    }
}

template <typename T>
void Logger::formatMessage(std::stringstream& ss, const QString& message, const T& value)
{
    if constexpr (std::is_same_v<T, QString>)
    {
        ss << message.toStdString() << " Value: " << value.toStdString();
    }
    else
    {
        ss << message.toStdString() << " Value: " << value;
    }
}


template void Logger::log<QString>(Level level, const QString& message, const QString& value);
template void Logger::formatMessage<QString>(std::stringstream& ss, const QString& message, const QString& value);
