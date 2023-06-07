#include "URLParameter.h"
void URLParameter::setName(std::string name)
{
    Name = URLDecode(name);
}
void URLParameter::setValue(std::string value)
{
    Value = URLDecode(value);
}
std::string URLParameter::URLDecode(std::string value)
{
    std::string Hex = "0123456789ABCDEF";
    std::map<char, int> HextoDec;
    for (size_t i = 0; i < Hex.size(); i++)
    {
        HextoDec.insert_or_assign(Hex[i], i);
    }
    std::string response = "";
    for (size_t i = 0; i < value.size(); i++)
    {
        int isNull = value[i];
        if (isNull >= 0)
        {
            if (i >= 2 && value[i - 2] == '%')
            {
                std::string thisCharacter = "";
                int character = HextoDec[value[i - 1]];
                character = character << 4;
                character = character | HextoDec[value[i]];
                char thisChar = character;
                thisCharacter += thisChar;
                response.replace(response.size() - 2, 2, thisCharacter);
            }
            else
            {
                response += value[i];
            }
        }
        else
        {
            break;
        }
    }
    return response;
}