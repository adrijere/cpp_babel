//
// ClientCore.cpp for babel in /home/loir_j/rendu/cpp_babel/server/inc
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:45 2015 Julien Loir
// Last update Mon Oct  26 00:15:45 2015 Julien Loir
//

#ifndef _MAINMUTEX_HPP_
# define _MAINMUTEX_HPP_

# include <mutex>

class MainMutex
{
public:
    static std::mutex &mutex()
    {
        static std::mutex instance;
        return instance;
    }
};

#endif