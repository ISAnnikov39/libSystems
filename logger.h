#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <QString>
#include <fstream>
#include <ctime>

class Logger
{
public:
    enum Level
    {
        INFO,
        WARNING,
        ERROR
    };

    explicit Logger(const QString& filename);
    ~Logger();

    void log(Level level, const QString& message);
    template <typename T>
    void log(Level level, const QString& message, const T& value);

private:
    std::ofstream logFile;

    QString levelToString(Level level) const;
    QString currentDateTime() const;
    void writeLogToConsole(const QString& timeStr, const QString& levelStr, const QString& message, Level level) const;
    void writeLogToFile(const QString& timeStr, const QString& levelStr, const QString& message);
    template <typename T>
    void formatMessage(std::stringstream& ss, const QString& message, const T& value);
};

extern Logger logger;

#endif // LOGGER_H
