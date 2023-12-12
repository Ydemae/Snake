#include "../include/raylib.h"

class Fruit{
    private:
        Vector2 _position;
        Vector2 _size;
        Color _color;
    public:
        Fruit(Vector2 position = (Vector2){0,0}, Vector2 size = (Vector2){0,0}, Color color = BLUE){
            this->setPosition(position);
            this->setSize(size);
            this->setColor(color);
        }
        Vector2 getPosition(){
            return this->_position;
        }
        void setPosition(Vector2 val){
            this->_position = val;
        }
        Vector2 getSize(){
            return this->_size;
        }
        void setSize(Vector2 val){
            this->_size = val;
        }
        Color getColor(){
            return this->_color;
        }
        void setColor(Color val){
            this->_color = val;
        }
};
