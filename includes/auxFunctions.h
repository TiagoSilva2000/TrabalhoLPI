#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

    void clearScreen (void);
    void pauseScreen (void);
    void clearBuffer(void);
    void checkPointerIntegrity (void* pointer);
    void checkFileIntegrity (FILE* file);
    unsigned long getCurrentDate (void);

#endif // AUXFUNCTION_H