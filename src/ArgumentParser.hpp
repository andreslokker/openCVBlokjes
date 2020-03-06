#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <string>
/**
 * @brief Enum Mode
 * Different types of modes the application can run in.
 * Interactive: custom input while application is running
 * Batch: input from batch file
 */
enum Mode {
    NONE,
    INTERACTIVE,
    BATCH
};


class ArgumentParser {
    public:
        /**
        * @brief Construct a new Argument Parser object
        * 
        */
        ArgumentParser();

        /**
         * @brief Destroy the Argument Parser object
         * 
         */
        virtual ~ArgumentParser();

        /**
         * @brief Parse arguments given when application is launched
         * 
         * @param argc 
         * @param argv 
         */
        void parseArguments(int argc, char** argv);

         /**
         * @brief Get the Mode object
         * 
         * @return Mode 
         */
        const Mode& getMode() const;

        /**
         * @brief Get the Location object
         * 
         * @return const std::string& 
         */
        const std::string& getLocation() const;
    private:
        std::string location;
        Mode mode;
};

#endif
