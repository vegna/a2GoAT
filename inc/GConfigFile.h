#ifndef __GConfigFile_h__
#define __GConfigFile_h__


#include <string>
#include <iostream>
#include <TROOT.h>

class  GConfigFile
{
private:
    std::string	global_config_file;
    std::vector<std::string> input_files;
    std::vector<std::string> output_files;

protected:

public:
    GConfigFile();
    GConfigFile(const Char_t* config_file);
    virtual ~GConfigFile();

    virtual Bool_t	Init(const char* configfile);
            Bool_t	Init()                          {Init(global_config_file.c_str());}
            void    SetConfigFile(const Char_t* config_file)	{global_config_file = config_file;}
    const   Char_t* GetConfigFile() const                       {}
            Bool_t  BaseConfig(const int argc, char* argv[], const std::string& def_pre_in, const std::string& def_pre_out);
    const   Int_t   GetNFiles() {return input_files.size();}
    std::string GetInputFile(const int i) {return input_files.at(i);}
    //std::vector GetInputFiles() {return input_files};
    std::string GetOutputFile(const int i) {return output_files.at(i);}
    //std::vector GetOutputFiles() {return output_files};

    std::string	ReadConfig(const std::string& key_in, const Int_t instance, const Char_t* configname);
    std::string	ReadConfig(const std::string& key_in, const Int_t instance)                             {return ReadConfig(key_in, instance, global_config_file.c_str());}
    std::string	ReadConfig(const std::string& key_in)                                                   {return ReadConfig(key_in, 0, global_config_file.c_str());}
};

#endif
