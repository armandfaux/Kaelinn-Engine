/*
** EPITECH PROJECT, 2024
** B-CPP-500-MPL-5-2-rtype-hugo.eschlimann
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <iostream>
#include <string>

namespace kln {
class Exception : public std::exception {
public:
  Exception(std::string const &message,
            std::string const &component = "Unknown") {}

  const char *what() const noexcept override { return _message.c_str(); }

  const std::string &getComponent() const noexcept { return _component; }

private:
  std::string _message;
  std::string _component;
};
} // namespace kln

#endif /* !EXCEPTION_HPP_ */
