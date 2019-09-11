#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H
    
    #define START_YEAR 2000

    void clearScreen (void);
    void pauseScreen (void);
    void clearBuffer(void);
    void checkPointerIntegrity (void* pointer);
    void checkFileIntegrity (FILE* file);
    unsigned long getCurrentDate (void);
    unsigned long getUsersDate (void);
    
#endif // AUXFUNCTION_H