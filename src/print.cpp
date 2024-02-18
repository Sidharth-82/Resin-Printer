#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



class Print{
    private:

        


        int currentPicture = 1;

        std::string pictureName;

        void parseGCodeCommand(std::string* command){
            std::vector<std::string> tokens;
            processTokens(command, &tokens);

            if((*command)[0] == ';'){
                std::cout << ";" << std::endl;
            }
            else if (tokens.at(0) == "G0"){
                float Z = extractValue(&(tokens.at(1)), 'Z');
                float F = extractValue(&(tokens.at(2)), 'F');
                std::cout << "G0 move Z: " << Z << " F: " << F << std::endl;
            }
            else if (tokens.at(0) == "G1"){
                float Z = extractValue(&(tokens.at(1)), 'Z');
                float F = extractValue(&(tokens.at(2)), 'F');
                std::cout << "G1 move Z: " << Z << " F: " << F << std::endl;
            }
            else if (tokens.at(0) == "G4"){
                float P = extractValue(&(tokens.at(1)), 'P');
                std::cout << "G4 time pause P: " << P << std::endl;
            }
            else if (tokens.at(0) == "G21;"){
                std::cout << "G21" << std::endl;
                //Set Units to millimeters
            }
            else if (tokens.at(0) == "G28"){
                float Z = extractValue(&(tokens.at(1)), 'Z');
                std::cout << "G28 move Z: " << Z << std::endl;
                //home z axis
            }
            else if (tokens.at(0) == "G90;"){
                std::cout << "G90"<< std::endl;
                //set absolute positioning
            }
            else if (tokens.at(0) == "M106"){
                float S = extractValue(&(tokens.at(1)), 'S');
                std::cout << "M106 Light Action S: " << S << std::endl;
            }
            else if (tokens.at(0) == "M6054"){
                pictureName = std::to_string(currentPicture) + ".png";

                std::cout << "M6054 picture set pictureName: " << pictureName << std::endl;

                currentPicture++;
            }
            else{
                std::cout << "ERROR" << std::endl;
            }
        }

        void processTokens(std::string* gCode, std::vector<std::string>* tokens){         
            std::istringstream iss(*gCode);

            std::string token;

            while (iss >> token){
                (*tokens).push_back(token);
            }
        }

        float extractValue(std::string* token, char parameter){
            if ((*token)[0] == parameter) {
                int colonLocation = (*token).find(";");
                return std::stof((*token).substr(1, colonLocation));
            }

            return 0.0f;
        }

        void move(float z, float f){
            
        }

        void wait(float p){

        }

        void home(float z){

        }

        void light(float s){

        }

        void displayPicture(std::string fileName){

        }





        

    public:
        Print(std::ifstream* gCodeFile){
            std::string command;
            while(std::getline(*gCodeFile, command)){
                if(command[0]){
                    parseGCodeCommand(&command);
                }
                //_getch();
            }
        }
        ~Print(){

        }

};



int main()
{
    std::ifstream gCodeFile("test/test/run.gcode");


    std::string command;
    std::getline(gCodeFile, command);

    std::cout << command << std::endl;

    Print currentPrint(&gCodeFile);



}
