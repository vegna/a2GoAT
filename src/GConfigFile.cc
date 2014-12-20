#include "GConfigFile.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include <algorithm>
#include <fstream>
#include <iostream>


GConfigFile::GConfigFile()  :
    global_config_file()
{
}

GConfigFile::GConfigFile(const Char_t* config_file)  :
    global_config_file(config_file)
{
}

GConfigFile::~GConfigFile()
{

}

Bool_t	GConfigFile::Init(const char* configfile)
{
    std::cout << "No Init function specified for this class." << std::endl;
    return kTRUE;
}

Bool_t	GConfigFile::BaseConfig(const int argc, char* argv[], const std::string& def_pre_in, const std::string& def_pre_out)
{
    // Initialise strings
    std::string configfile = "";
    std::string serverfile = "";
    std::string dir_in = "";
    std::string dir_out = "";
    std::string file_in = "";
    std::string file_out = "";
    std::string pre_in = def_pre_in;
    std::string pre_out = def_pre_out;

    Int_t length;
    std::string flag;

    Bool_t overwrite = kTRUE;
    if(argc == 1)
    {
        system("man ./documents/goat.man");
        return kFALSE;
    }
    else if(argc == 2)
    {
        flag = argv[1];
        flag.erase(0,1);
        if(strcmp(flag.c_str(), "help") == 0) return kFALSE;
        else configfile= argv[1];
    }
    else
    {
        for(int i=1; i<argc; i++)
        {
            flag = argv[i];
            if(flag.find_first_of("-") == 0)
            {
                i++;
                flag.erase(0,1);
                if(strcmp(flag.c_str(), "s") == 0) serverfile = argv[i];
                else if(strcmp(flag.c_str(), "d") == 0) dir_in = argv[i];
                else if(strcmp(flag.c_str(), "D") == 0) dir_out = argv[i];
                else if(strcmp(flag.c_str(), "f") == 0) file_in = argv[i];
                else if(strcmp(flag.c_str(), "F") == 0) file_out = argv[i];
                else if(strcmp(flag.c_str(), "p") == 0) pre_in = argv[i];
                else if(strcmp(flag.c_str(), "P") == 0) pre_out = argv[i];
                else if(strcmp(flag.c_str(), "n") == 0)
                {
                        overwrite = kFALSE;
                    i--;
                }
                else
                {
                    std::cout << "Unknown flag " << flag << std::endl;
                    return kFALSE;
                }
            }
            else configfile = argv[i];
        }
    }

    // Check that config file exists:
    ifstream cfile(configfile.c_str());
    if(!cfile)
    {
        std::cout << "Config file '" << configfile << "' could not be found." << std::endl;
        return kFALSE;
    }
    SetConfigFile(configfile.c_str());

    // If server file is specified, check that it exists
    if(serverfile.length() > 0)
    {
        // Check that file exists:
        ifstream sfile(serverfile.c_str());
        if(!sfile)
        {
            std::cout << "Server file '" << serverfile << "' could not be found" << std::endl;
            return kFALSE;
        }
    }
    // If no server file is specified, allow for checking in the config file
    else serverfile = configfile;

    // If unset, scan server or config file for file settings
    if(dir_in.length() == 0)
    {
        flag = ReadConfig("Input-Directory",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) dir_in = flag;
    }

    if(dir_out.length() == 0)
    {
        flag = ReadConfig("Output-Directory",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) dir_out = flag;
    }

    if(file_in.length() == 0)
    {
        flag = ReadConfig("Input-File",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) file_in = flag;
    }

    if(file_out.length() == 0)
    {
        flag = ReadConfig("Output-File",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) file_out = flag;
    }

    if(pre_in.length() == 0)
    {
        flag = ReadConfig("Input-Prefix",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) pre_in = flag;
    }

    if(pre_out.length() == 0)
    {
        flag = ReadConfig("Output-Prefix",0,(Char_t*)serverfile.c_str());
        flag.erase(0,flag.find_first_not_of(" "));
        if(strcmp(flag.c_str(),"nokey") != 0) pre_out = flag;
    }
    // Finished scanning for file settings

    // Fix directories to include final slash if not there
    if(dir_in.find_last_of("/") != (dir_in.length()-1)) dir_in += "/";
    if(dir_out.find_last_of("/") != (dir_out.length()-1)) dir_out += "/";

    // Output user settings (Set to defaults if still unspecified)
    std::cout << std::endl << "User inputs" << std::endl;
    std::cout << "Config file:      '" << configfile << "' chosen" << std::endl;
    if(dir_in.length() != 0)  	std::cout << "Input directory:  '" << dir_in << "' chosen" << std::endl;
    if(dir_out.length() != 0)  	std::cout << "Output directory: '" << dir_out << "' chosen" << std::endl;
    if(file_in.length() != 0)  	std::cout << "Input file:       '" << file_in << "' chosen" << std::endl;
    if(file_out.length() != 0) 	std::cout << "Output file:      '" << file_out << "' chosen" << std::endl;
    if(pre_in.length() != 0)  	std::cout << "Input prefix:     '" << pre_in << "' chosen" << std::endl;
    if(pre_out.length() != 0)  	std::cout << "Output prefix:    '" << pre_out << "' chosen" << std::endl;
    std::cout << std::endl;

    std::string file;
    std::string prefix;
    std::string suffix;

    Int_t files_found = 0;
    // If input file is specified, use it
    if(file_in.length() > 0)
    {
        std::cout << "Searching for input file(s)" << std::endl;
        file = file_in;
        length = file.length();
        // File should at least have '.root' at the end
        if(length >= 5)
        {
            // Add input directory to it
            file_in = dir_in+file_in;
            std::cout << "Input file  '" << file_in << "' chosen" << std::endl;

            // If output file is specified, use it
            if(file_out.length() > 0) file_out = dir_out+file_out;
            // If output file is not specified, build it
            else
            {
                // If output directory is not specified, build it
                if(dir_out.length() == 0)
                {
                    prefix = file.substr(0,file.find_last_of("/")+1);
                    dir_out = dir_in+prefix;
                }
                // If input prefix doesn't match, simply prepend output prefix to the file name
                if(file.find(pre_in)>file.length()) suffix = ("_"+file.substr(file.find_last_of("/")+1,length-(file.find_last_of("/")+1)));
                // If input prefix does match, switch prefixes
                else suffix = file.substr(file.find_last_of("/")+1+pre_in.length(),length-(file.find_last_of("/")+1+pre_in.length()));
                // Build output file name
                file_out = dir_out+pre_out+suffix;
            }

            std::cout << "Output file '" << file_out << "' chosen" << std::endl << std::endl;
            input_files.push_back(file_in);
            output_files.push_back(file_out);
            files_found++;
        }
    }
    // Otherwise scan input directory for matching files
    else
    {
        std::cout << "Searching input directory for files matching input prefix" << std::endl;
        std::cout << "Input prefix  '" << pre_in << "' chosen" << std::endl;
        std::cout << "Output prefix '" << pre_out << "' chosen" << std::endl;

        // If output directory is not specified, use the input directory
        if(dir_in.length()  == 0) dir_in = "./";
        if(dir_out.length() == 0) dir_out = dir_in;

        // Create list of files in input directory
        TSystemFile *sys_file;
        TSystemDirectory *sys_dir = new TSystemDirectory("files",dir_in.c_str());
        TList *file_list = sys_dir->GetListOfFiles();
        file_list->Sort();
        TIter file_iter(file_list);

        // Iterate over files
        while((sys_file=(TSystemFile*)file_iter()))
        {
            file = sys_file->GetName();
            length = file.length();
            // File should at least have '.root' at the end
            if(length >= 5)
            {
                //Check that prefixes and suffixes match
                prefix = file.substr(0,pre_in.length());
                suffix = file.substr(length-5,5);
                if(((strcmp(prefix.c_str(),pre_in.c_str()) == 0)) && (strcmp(suffix.c_str(),".root") == 0))
                {
                    // Build input file name
                    file_in = dir_in+file;
                    // Build output file name
                    suffix = file.substr(pre_in.length(),length-pre_in.length());
                    file_out = dir_out+pre_out+suffix;

                    // Check for previously created output file
                    if((gSystem->IsFileInIncludePath(file_out.c_str())) && !overwrite) continue;

                    input_files.push_back(file_in);
                    output_files.push_back(file_out);
                    files_found++;
                }
            }
        }
    }
    if (files_found == 0)
    {
        std::cout << "ERROR: No AcquRoot files found!" << std::endl;
        return kFALSE;
    }

    return kTRUE;
}

std::string GConfigFile::ReadConfig(const std::string& key_in, const Int_t instance, const Char_t* configname)
{
    Int_t string_instance = 0;
    std::string key = key_in;
    std::transform(key.begin(), key.end(),key.begin(), ::toupper);

    std::string str;
    std::string values;

    ifstream configfile;

    configfile.open(configname);
    //std::cout << "config: " << configname << std::endl;

    if (configfile.is_open())
    {
        while ( getline (configfile,str) )
        {
            std::string::size_type begin = str.find_first_not_of(" \f\t\v");
            if(begin == std::string::npos) continue;
            if(std::string("#").find(str[begin]) != std::string::npos)	continue;
            if(std::string("//").find(str[begin]) != std::string::npos)	continue;

            std::string firstWord;

            try {
                firstWord = str.substr(0,str.find(":"));
            }
            catch(std::exception& e) {
                firstWord = str.erase(str.find_first_of(":"),str.find_first_of(":"));
            }
            std::transform(firstWord.begin(),firstWord.end(),firstWord.begin(), ::toupper);

            values = str.substr(str.find(":")+1,str.length());

            if (strcmp(firstWord.c_str(),key.c_str()) == 0)
            {
                if (string_instance == instance)
                {
                    configfile.close();
                    return values;
                }
                else string_instance++;
            }
        }
        configfile.close();
    }

    return "nokey";
}
