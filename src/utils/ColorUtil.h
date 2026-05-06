#ifndef COLORUTIL_H
#define COLORUTIL_H

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector3.hpp"
#include <algorithm>
#include <cmath>
namespace sk {
    struct ColorUtil{
        sf::Color hsvToRgb(float h, float s, float v){
            if(s <= 0.f){
                sf::Uint8 c = static_cast<sf::Uint8>(v * 255.f); // no saturation = colour is gray
                return sf::Color(c, c, c);
            }

            h = std::fmod(h, 360.f);
            if(h < 0.f) h += 360.f; // handle wraparound

            float hSec = h / 60.f; // split hue into 6 sectors
            int iSec = static_cast<int>(hSec); // get sector number
            float fSec = hSec - iSec; // get position in current sector

            float floor = v * (1.f - s); // min. value of any channel
            float rising = v * (1.f - s * (1.f - fSec));
            float falling = v * (1.f - s * fSec); 

            // colours are assigned differently depending on sector
            // one channel (r,g,b) holds peak value, one holds minimum value, one is rising/falling
            float r, g, b;
            switch(iSec){
                case 0: 
                    r = v;
                    g = rising;
                    b = floor;
                    break;
                case 1:
                    r = falling;
                    g = v;
                    b = floor;
                    break;
                case 2:
                    r = floor;
                    g = v;
                    b = rising;
                    break;
                case 3:
                    r = floor;
                    g = falling;
                    b = v;
                    break;
                case 4:
                    r = rising;
                    g = floor;
                    b = v;
                    break;
                default:
                    r = v;
                    g = floor;
                    b = falling;
                    break;            
            }
            // convert colours to 0-255 range
            r = static_cast<sf::Uint8>(r * 255.f);
            g = static_cast<sf::Uint8>(g * 255.f);
            b = static_cast<sf::Uint8>(b * 255.f);
            return sf::Color(r, g, b);

        }
        sf::Vector3f rgbToHsv(const sf::Color& color){
            float h,s,v;

            //convert to 0-1 floats
            float r = color.r / 255.f;
            float g = color.g / 255.f;
            float b = color.b / 255.f;

            float strongest = std::max({r, g, b}); // brightest channel = overall value
            float weakest = std::min({r, g, b});
            float spread = strongest - weakest; // larger spread = more saturation

            v = strongest;
            if(strongest > 0.f){
                s = spread / strongest; // saturation = size of spread relative to brightness
            } else{
                s = 0.f; // avoid dbz if colour is pure black (v=0)
            }

            if(spread < 1e-6f){
                h = 0.f; // all channels are equal = colour is gray (no hue needed)
                return {h,s,v};
            }

            if(strongest == r){
                h = 60.f * std::fmod((g - b) / spread, 6.f); // 0-360 wraparound
            } else if(strongest == g){
                h = 60.f * ((b - r) / spread + 2.f);
            } else{
                h = 60.f * ((r - g) / spread + 4.f);
            }

            if(h < 0.f) h += 360.f; //wraparound safeguard
            
            return {h,s,v};
        }
    };

}

#endif //!COLORUTIL_H
