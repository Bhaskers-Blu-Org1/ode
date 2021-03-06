/*
 * $Id: jikesapi.h,v 1.7 2000/05/05 02:24:43 lord Exp $
 */

#ifndef _JIKES_API_H_FLAG_
#define _JIKES_API_H_FLAG_

class JikesOption
{    
 public:
    
    char *classpath    ;
    char *directory    ;
    char *encoding     ;
    
    bool nowrite;
    bool deprecation;
    bool O;
    bool g;
    bool verbose;
    bool depend;
    bool nowarn;
    bool old_classpath_search_order;
    bool zero_defect;

    virtual ~JikesOption();

 protected:
    
    JikesOption();
};

class JikesError
{
 public:

    enum JikesErrorSeverity
    {
        JIKES_ERROR,
        JIKES_CAUTION,
        JIKES_WARNING
    } ;
        
    virtual JikesErrorSeverity getSeverity() = 0 ;
    virtual const char *getFileName() = 0 ;
    
    virtual int getLeftLineNo      () = 0 ;
    virtual int getLeftColumnNo    () = 0 ;
    virtual int getRightLineNo     () = 0 ;
    virtual int getRightColumnNo   () = 0 ;

    /**
     * Returns message describing error.
     */
    virtual const wchar_t *getErrorMessage() = 0;

    /**
     * Returns formatter error report. 
     */
    virtual const wchar_t *getErrorReport() = 0;

 protected:

    const char *getSeverityString();
};

/**
 * API to jikes compiler.
 */
class JikesAPI
{
 public:

    JikesAPI();
    
    virtual ~JikesAPI();
       
    /**
     * Returns instance of current compiler options.
     * returned pointer can be used to modify current
     * compiler options.
     */
    virtual JikesOption *getOptions();
    
    /**
     * Creates instance of compiler options,
     * corresponding to given command line parameters.
     *
     * @return list of java file names found on command line
     */
    virtual char ** parseOptions(int argc, char **argv) ;

    /**
     * Compile given list ofiles using current compiler options.
     */
    virtual int compile(char ** filenames);

    /**
     * Jikes API implements singelton pattern.
     * This is a way to get instance of it.
     */
    static JikesAPI * getInstance();

    /**
     * This method will be called for each error reported.
     */
    virtual void reportError(JikesError *error);
    
    
    /**
     * Define the virtual base class for all Readers.
     * A pointer to an object of this type is returned by JikesAPI::read()
     */
    class FileReader
        {
    public:
            virtual  ~FileReader()  {}
            
            virtual const char     *getBuffer()      = 0;	// If the file is unreadable an object should still be created but GetBuffer() should return NULL.
            virtual       size_t    getBufferSize()  = 0;	// If the file is unreadable GetBufferSize() is undefined.
        };

    /**
     * Define the virtual base class for all WriteObjects.
     * A pointer to an object of this type is returned by JikesAPI::write()
     */
    class FileWriter
        {
    public:
            FileWriter(size_t mS):   maxSize(mS) {} 
            virtual  ~FileWriter() {}
            
            size_t    write(const unsigned char *data, size_t size);
            virtual  bool      isValid()                         = 0;
            
    private:
            
            virtual  size_t    doWrite(const unsigned char *data, size_t size)   = 0;	// Garanteed not to be called with a combined total of more than maxSize bytes during the lifespan of the object.
            size_t   maxSize;
        };
        
    virtual int stat(const char *filename, struct stat *status);
    
    virtual FileReader  *read  (const char *filename              );
    virtual FileWriter  *write (const char *filename, size_t bytes);
    
 private:

    JikesOption *option;
    static JikesAPI *instance;
};

#endif // _JIKES_API_H_FLAG_
