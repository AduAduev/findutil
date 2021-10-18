#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace fs = std::filesystem;

int main()
{
    std::vector<std::string> sysfiles;
    std::vector<std::string> sysdirs;
    sysdirs.push_back(std::string("fill"));
    sysdirs.push_back(std::string("fill"));
    std::string directory_name = "fill";
    std::map<std::string,std::string> result;
    try{
        for(auto &dir: sysdirs){
            for (auto &p : fs::recursive_directory_iterator(dir))
            {
                if (!fs::is_regular_file(p.status()))
                    continue;
                sysfiles.push_back(std::string(p.path().filename()));
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
    
    try
    {
        for (auto &p : fs::recursive_directory_iterator(directory_name))
        {
            if (!fs::is_regular_file(p.status()))
                continue;

            std::string name(p.path().filename());
            for (auto &files:sysfiles){
                if (name == files){
                    std::string str(p.path());
                    str=str.substr(directory_name.size()+1,str.find("/",directory_name.size()+1)-directory_name.size()-1);
                    if (result[str].empty()) {
                        result[str]=name;
                    } else {
                        result[str]+="|";
                        result[str]+=name;
                    }
                }
            }
        }
        for (auto &kv:result){
            std::cout <<kv.first<<":  "<<kv.second<<std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
    return 0;
}