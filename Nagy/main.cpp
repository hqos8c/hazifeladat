#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<variant>
#include<cmath>
#include<vector>

int main() {

   auto err = [](auto str){ std::cout << "Error in : " << str << "\n"; std::exit(-1); };

    std::ifstream input("data_2.txt");
    if(input.is_open())
    {
        std::string tmp;
        std::string y = "2018";
        std::string m = "2018 5 ";
        std::string d = "2018 5 30 ";

        float a = 0.0;
        float b = 0.0;
        float c = 0.0;
        int fer_div = 0;
        int vel_div = 0;
        int bal_div = 0;


        std::ofstream ofile("realdata.txt");

        for(std::string line;std::getline(input,tmp,';');)
        {
        std::size_t y_f = tmp.find(y);
        std::size_t m_f = tmp.find(m);
        std::size_t d_f = tmp.find(d);

        if(y_f != std::string::npos)
        {
            if(m_f != std::string::npos)
            {
                if(d_f == std::string::npos)
                {
                     a /= fer_div;
                     b /= vel_div;
                     c /= bal_div;
                    ofile<<d<<" Fertő-tó: "<<a<<"\n"<<d<<" Velencei-tó átlag: "<<b<<"\n"<<d<<"Balaon átlag: "<<c<<"\n";
                    a =0.0;
                    b =0.0;
                    c =0.0;
                    fer_div=0;
                    vel_div=0;
                    bal_div=0;
                    d.replace(d.begin(),d.end(),tmp.begin(),tmp.begin()+9);
                }
            }
            else{d.replace(d.begin(),d.end(),tmp.begin(),tmp.begin()+7);}
        }

        std::size_t Velence = tmp.find("Agard");
        std::size_t Ferto = tmp.find("Fertorakos");
        std::size_t Balaton_1 = tmp.find("Siofok");
        std::size_t Balaton_2 = tmp.find("Balatonakali");
        std::size_t Balaton_3 = tmp.find("Tihany");
        std::size_t Dat_zero = tmp.find(",0");
        std::size_t Dat_zero_1 = tmp.find(",0.");
        
            if(Ferto != std::string::npos)
            {
                if(Dat_zero != std::string::npos && Dat_zero_1 == std::string::npos)
                {
                tmp.replace(tmp.begin(),tmp.end(),tmp.end()-1,tmp.end());                    
                }
                else
                {
                    tmp.replace(tmp.begin(),tmp.end(),tmp.end()-4,tmp.end());
                    fer_div++;
                }
                a += std::stof(tmp);
            }
            if(Velence != std::string::npos)
            {
                if(Dat_zero != std::string::npos && Dat_zero_1 == std::string::npos)
                {
                tmp.replace(tmp.begin(),tmp.end(),tmp.end()-1,tmp.end());                    
                }
                else
                {
                    tmp.replace(tmp.begin(),tmp.end(),tmp.end()-4,tmp.end());    
                    vel_div++;
                }
                b += std::stof(tmp);
            }
            if(Balaton_1 != std::string::npos ||Balaton_2 != std::string::npos || Balaton_3 != std::string::npos)
            {
                if(Dat_zero != std::string::npos && Dat_zero_1 == std::string::npos)
                {
                tmp.replace(tmp.begin(),tmp.end(),tmp.end()-1,tmp.end());                    
                }
                else
                {
                tmp.replace(tmp.begin(),tmp.end(),tmp.end()-4,tmp.end());
                bal_div++;
                }
                c += std::stof(tmp);
            }            
        }
    }
    else{err("opening"); }
}