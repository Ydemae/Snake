#include <iostream>
#include <string>
class Voiture
{
    public:
        Voiture(std::string immat, int maxspeed){
            this->setImmat(immat);
            this->setMaxSpeed(maxspeed);
        };
        std::string ToString(){
            std::string chaine = "Plaque d'immatriculation : " + this->getImmat() + "\nVitesse max : " + std::to_string(this->getMaxSpeed());
            return chaine;
        };
        std::string getImmat()
        {
            return this->_immat;
        };
        int getMaxSpeed()
        {
            return this->_maxspeed;
        };
        void setImmat(std::string immat)
        {
            this->_immat = immat;
        };
        void setMaxSpeed(int speed)
        {
            this->_maxspeed = speed;
        };

    private:
        std::string _immat;
        int _maxspeed;

};

int addition(int a, int b){
    int r = a + b;
    return r;
};


int main()
{
    Voiture audi80("AB412FG", 150);
    std::cout << audi80.ToString();
    return 0;
}