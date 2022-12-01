//
// Created by Yotam on 29/11/2022.
//
#include <memory>
#include <iostream>

#ifndef WORLDCUP_EXCEPTION_H
#define WORLDCUP_EXCEPTION_H


class KeyAlreadyExists : public std::exception {
public:
    const char * what () const noexcept override {
        return "Key already exists";
    }
};

class KeyDoesNotExist : public std::exception {
public:
    const char * what () const noexcept override {
        return "Key does not exist";
    }
};

class EmptyList : public std::exception {
public:
    const char * what () const noexcept override {
        return "Empty List";
    }
};

class EmptyTree : public std::exception {
public:
    const char * what () const noexcept override {
        return "Empty Tree";
    }
};

#endif //WORLDCUP_EXCEPTION_H
