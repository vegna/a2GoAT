#ifndef __GConfigFile_h__
#define __GConfigFile_h__


#include <string>
#include <iostream>
#include <TROOT.h>

class  GConfigFile
{
private:
    std::string	globalConfigFile;
    std::vector<std::string> inputFileList;
    std::vector<std::string> outputFileList;

protected:

public:
    GConfigFile();
    GConfigFile(const Char_t* configFile);
    virtual ~GConfigFile();

    virtual Bool_t	Init(const char* configFile);
            Bool_t	Init() {Init(globalConfigFile.c_str());}
            void    SetConfigFile(const Char_t* configFile)	{globalConfigFile = configFile;}
    const   Char_t* GetConfigFile() const                       {}
            Bool_t  BaseConfig(const int argc, char* argv[], const std::string& defaultInputPrefix, const std::string& defaultOutputPrefix);
    const   Int_t   GetNFiles() {return inputFileList.size();}
    std::string GetInputFile(const int i) {return inputFileList.at(i);}
    std::string GetOutputFile(const int i) {return outputFileList.at(i);}

    std::string	ReadConfig(const std::string& key_in, const Int_t instance, const Char_t* configName);
    std::string	ReadConfig(const std::string& key_in, const Int_t instance)                             {return ReadConfig(key_in, instance, globalConfigFile.c_str());}
    std::string	ReadConfig(const std::string& key_in)                                                   {return ReadConfig(key_in, 0, globalConfigFile.c_str());}
};

#endif
