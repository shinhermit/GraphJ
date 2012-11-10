#include "NamedColor.hpp"

std::map<NamedColor::ColorName, std::string> NamedColor::_toString = CreateMap<NamedColor::ColorName, std::string>(NamedColor::Red, "red")(NamedColor::Green, "green")(NamedColor::Bleu, "bleu")(NamedColor::Yellow,"yellow")(NamedColor::Brown,"brown")(NamedColor::Purple,"purple")(NamedColor::Black,"black")(NamedColor::White,"white")(NamedColor::Orange,"orange")(NamedColor::Gray,"gray")(NamedColor::Pink,"pink")(NamedColor::Bordeaux, "bordeaux");

std::map<NamedColor::ColorName, int> NamedColor::_toString = CreateMap<NamedColor::ColorName, int>(NamedColor::Red, 0xff0000)(NamedColor::Green, 0x00ff00)(NamedColor::Bleu, 0x0000ff)(NamedColor::Yellow, 0xfff000)(NamedColor::Brown, 0x683100)(NamedColor::Violet,0x68005d)(NamedColor::Black,0x000000)(NamedColor::White,0xffffff)(NamedColor::Orange,0xffa00b)(NamedColor::Gray,0x727272)(NamedColor::Pink,0xff82a5)(NamedColor::Bordeaux, 0x6d0701);

std::set<NamedColor::ColorName> NamedColor::allNames()
{  
  return createSet<ColorName>(Red)(Green)(Bleu)(Yellow)(Brown)(Violet)(Black)(White)(Orange)(Gray)(Pink)(Bordeaux);
}

NamedColor::NamedColor(NamedColor::ColorName col):_col(col){}

NamedColor & NamedColor::operator>>(std::ostream & out){
  out << _toString[_col];
  return *this;
}

std::ostream & operator<<(std::ostream & out, NamedColor & col){
  col >> out;
  return out;
}

std::string NamedColor::toString(){
  return _toString[_col];
}

int NamedColor::hexaValue(){
  return _hexaValue[_col];
}
