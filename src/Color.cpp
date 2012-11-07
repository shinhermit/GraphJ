#include "Color.hpp"

std::map<Color::ColorName, std::string> Color::_toString = CreateMap<Color::ColorName, std::string>(Red, "red")(Green, "green")(Bleu, "bleu")(Yellow,"yellow")(Brown,"brown")(Violet,"violet")(Black,"black")(White,"white")(Orange,"orange")(Gray,"gray")(Purlple,"purple")(Pink,"pink");

Color::Color(Color::ColorName col):_col(col){}

std::string Color::toString(){
  return _toString[_col];
}


Color & Color::operator>>(std::ostream & out){
  out << _toString[_col];
  return *this;
}

std::ostream & operator<<(std::ostream & out, Color & col){
  col >> out;
  return out;
}
