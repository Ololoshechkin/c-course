//
// Created by Vadim on 02.05.17.
//

#ifndef HUFFMAN_EXCEPTIONS_H
#define HUFFMAN_EXCEPTIONS_H

#include <exception>
#include <string>

struct argument_exeption  : public std::exception
{
protected:
	std::string message;
public:
	virtual const char* what() const throw();
};

struct illegal_argument_cnt_exception : public argument_exeption 
{
	illegal_argument_cnt_exception(int arg_cnt, int expected_arg_cnt);
};

struct illegal_arguments_exception : public argument_exeption
{ 
	explicit illegal_arguments_exception(int arg_number, std::string expected_arg);
};

struct bad_file_format_exception : public std::exception
{
	std::string message;
	bad_file_format_exception(std::string message = "bad decrypting file format");
public:
	virtual const char* what() const throw();
};


#endif //HUFFMAN_EXCEPTIONS_H
